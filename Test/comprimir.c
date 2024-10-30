#include "fila.h"
#include "comprimir.h"
#include "descomprimir.h"

// Função para obter o tamanho do arquivo
long int tamArquivo(FILE *f)
{
  long int tam;

  fseek(f, 0, SEEK_END); // Move o ponteiro do arquivo para o final
  tam = ftell(f);        // Obtém a posição atual do ponteiro, que é o tamanho do arquivo
  rewind(f);             // Volta o ponteiro do arquivo para o início

  return tam;
}

// Função para compactar o arquivo

// Função para obter o caminho do arquivo a ser compactado
void obterCaminhoArquivo(char *caminhoArquivo)
{
  printf("Insira o caminho do arquivo que deseja compactar: ");
  fgets(caminhoArquivo, 1000, stdin);
  caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o caractere de nova linha
}

// Função para abrir o arquivo e verificar erros
FILE *abrirArquivo(const char *caminhoArquivo)
{
  FILE *f = fopen(caminhoArquivo, "rb");
  if (f == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
  }
  return f;
}

// Função para calcular a frequência dos bytes no arquivo
void calcularFrequencia(FILE *f, long int tam_arquivo, unsigned char *listaBytes, int *frequencia)
{
  int byte;
  long int i = 0;
  while ((byte = fgetc(f)) != EOF)
  {
    frequencia[byte]++;
    listaBytes[i] = byte;
    i++;
  }
  listaBytes[i] = '\0';
}

// Função para enfileirar os bytes com suas respectivas frequências
void enfileirarBytes(Queue *fila, int *frequencia)
{
  for (int j = 0; j < 256; j++)
  {
    if (frequencia[j] != 0)
    {
      enqueue(fila, j, frequencia[j]);
    }
  }
}

// Função para criar o nome do arquivo compactado
void criarNomeArquivoCompactado(const char *caminhoArquivo, char *nomeArquivo)
{
  int j = strlen(caminhoArquivo) - 1;
  int k = 0;
  for (int i = j; i >= 0; i--)
  {
    if (caminhoArquivo[i] != '\\')
    {
      nomeArquivo[k] = caminhoArquivo[i];
      k++;
    }
    else if (caminhoArquivo[i] == '\\')
    {
      break;
    }
  }
  nomeArquivo[k] = '\0';
  // Inverte a string para obter o nome correto
  int len = strlen(nomeArquivo);
  for (int i = 0; i < len / 2; i++)
  {
    char temp = nomeArquivo[i];
    nomeArquivo[i] = nomeArquivo[len - i - 1];
    nomeArquivo[len - i - 1] = temp;
  }
}

// Função principal para compactar o arquivo
int compactarArquivo()
{
  Queue *fila = createQueue();
  FILE *f;
  char **tabela;
  char *arquivoCodificado;
  char caminhoArquivo[1000];

  obterCaminhoArquivo(caminhoArquivo);
  f = abrirArquivo(caminhoArquivo);
  if (f == NULL)
    return 1;

  long int tam_arquivo = tamArquivo(f);
  unsigned char *listaBytes = malloc(tam_arquivo * sizeof(unsigned char) + 1);
  int frequencia[256] = {0};

  calcularFrequencia(f, tam_arquivo, listaBytes, frequencia);
  enfileirarBytes(fila, frequencia);

  Node *arvore = criarArvoreHuffman(fila->head);
  // imprimirArvoreHuffmanPO(arvore);

  int colunas = height(arvore);
  int nos = 0;
  int tamArvore = 0;
  int k = 0;

  tabela = alocarMapa(colunas);
  criarMapa(tabela, arvore, "", colunas, &nos);

  unsigned char bytesArvore[2 * nos];
  salvarArvorePreOrdem(arvore, bytesArvore, &k, &tamArvore);

  long int tamCodificado;
  arquivoCodificado = codificarArquivo(tabela, listaBytes, tam_arquivo, &tamCodificado);

  char nomeArquivo[1000];
  criarNomeArquivoCompactado(caminhoArquivo, nomeArquivo);

  int saida = salvarCompactado(tamCodificado, bytesArvore, arquivoCodificado, tamArvore, nomeArquivo);

  free(listaBytes);
  free(arquivoCodificado);
  free(fila);
  free(arvore);
  free(tabela);

  if (saida == 1)
    return 1;

  rewind(f);
  fclose(f);
  return 0;
}