#include "fila.h"
#include "descomprimir.h"
#include <string.h>
#include "arvoreHuffman.h"
#include "comprimir.h"

void lerCaminhoArquivo(char *caminhoArquivo)
{
  printf("Insira o caminho do arquivo que deseja descompactar: ");
  fgets(caminhoArquivo, 1000, stdin);
  caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o '\n'
}

unsigned short lerCabecalho(FILE *f, unsigned short *lixo, unsigned short *tamArvore)
{
  unsigned short cabecalho;
  fread(&cabecalho, sizeof(unsigned short), 1, f);

  int j = 2;
  for (int i = 15; i >= 13; i--)
  {
    if (isHeaderSet(cabecalho, i))
      *lixo = setHeader(*lixo, j);
    j--;
  }

  for (int i = 12; i >= 0; i--)
  {
    if (isHeaderSet(cabecalho, i))
      *tamArvore = setHeader(*tamArvore, i);
  }
  return cabecalho;
}

/*
A função lerArvore é projetada para ler um conjunto de dados binários que representam uma árvore
e armazená-los no array arvore. Ela usa fread, que lê blocos de dados de tamanho unsigned char (1 byte)
diretamente do arquivo f e os armazena em arvore.O número de bytes a serem lidos é definido pelo parâmetro tamArvore.*/
void lerArvore(FILE *f, unsigned char *arvore, unsigned short tamArvore)
{
  fread(arvore, sizeof(unsigned char), tamArvore, f);
}

void criarNomeArquivoDescompactado(char *caminhoArquivo, char *nomeArquivo)
{
  for (int i = strlen(caminhoArquivo) - 1; i >= 0; i--)
  {
    if (caminhoArquivo[i] == '.')
    {
      caminhoArquivo[i] = '\0';
      break;
    }
  }
  strcpy(nomeArquivo, "descompactado");
  strcat(nomeArquivo, caminhoArquivo);
}

void descompactarDados(FILE *f, FILE *arquivoDescompactado, Node *arvoreHuffman, long tam_arquivo, int lixo)
{
  unsigned char byte;
  int nBitsLidos = 0;
  Node *aux = arvoreHuffman;

  while (fread(&byte, sizeof(unsigned char), 1, f) != EOF)
  {
    long posicaoArquivo = ftell(f);

    for (int i = 7; i >= 0; i--)
    {
      aux = isBitSet(byte, i) ? aux->right : aux->left;
      nBitsLidos++;

      if (!aux->left && !aux->right)
      {
        fwrite(aux->item, sizeof(unsigned char), 1, arquivoDescompactado);
        aux = arvoreHuffman;
      }

      if (posicaoArquivo == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
        return;
    }
  }
}

int descompactarArquivo()
{
  FILE *f;
  char caminhoArquivo[1000], nomeArquivo[1000];
  unsigned short cabecalho, lixo = 0, tamArvore = 0;
  int h = 0;

  lerCaminhoArquivo(caminhoArquivo);
  f = fopen(caminhoArquivo, "rb");

  long tam_arquivo = tamArquivo(f);
  cabecalho = lerCabecalho(f, &lixo, &tamArvore);

  unsigned char arvore[tamArvore];
  lerArvore(f, arvore, tamArvore);

  Node *arvoreHuffman = refazerArvore(arvore, tamArvore, &h, NULL);

  criarNomeArquivoDescompactado(caminhoArquivo, nomeArquivo);
  FILE *arquivoDescompactado = fopen(nomeArquivo, "wb");

  descompactarDados(f, arquivoDescompactado, arvoreHuffman, tam_arquivo, lixo);

  fclose(f);
  fclose(arquivoDescompactado);
  return 0;
}
