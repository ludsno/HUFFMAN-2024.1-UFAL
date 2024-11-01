#include "fila.h"
#include "codificacao.h"

long int tamArquivo(FILE *f)
{
    long int tam;

    fseek(f, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    tam = ftell(f);        // Obtém a posição atual do ponteiro, que é o tamanho do arquivo
    rewind(f);             // Volta o ponteiro do arquivo para o início

    return tam;
}



void obterCaminhoArquivo(char *caminhoArquivo)
{
    printf("Insira o caminho do arquivo que deseja compactar: ");
    fgets(caminhoArquivo, 1000, stdin);
    caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o caractere de nova linha
}

FILE *abrirArquivo(const char *caminhoArquivo)
{
    FILE *f = fopen(caminhoArquivo, "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
    }
    return f;
}

void calcularFrequencia(FILE *f, long int tam_arquivo, unsigned char *listaBytes, int *frequencia)
{
    // Variável para armazenar o byte lido do arquivo
    int byte;
    
    // Variável para contar a posição no array listaBytes
    long int i = 0;
    
    // Loop para ler cada byte do arquivo até o final (EOF)
    while ((byte = fgetc(f)) != EOF)
    {
        // Incrementa a frequência do byte lido
        frequencia[byte]++;
        
        // Armazena o byte lido na lista de bytes
        listaBytes[i] = byte;
        
        // Incrementa o índice para a próxima posição na lista de bytes
        i++;
    }
    
    // Marca o final da lista de bytes com o caractere nulo
    listaBytes[i] = '\0';
}

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

void criarNomeArquivoCompactado(const char *caminhoArquivo, char *nomeArquivo)
{
    // Obtém o índice do último caractere da string caminhoArquivo
    int j = strlen(caminhoArquivo) - 1;
    
    // Inicializa o índice para nomeArquivo
    int k = 0;
    
    // Loop para percorrer caminhoArquivo de trás para frente
    for (int i = j; i >= 0; i--)
    {
        // Se o caractere não for uma barra invertida, adiciona ao nomeArquivo
        if (caminhoArquivo[i] != '\\')
        {
            nomeArquivo[k] = caminhoArquivo[i];
            k++;
        }
        // Se encontrar uma barra invertida, interrompe o loop
        else if (caminhoArquivo[i] == '\\')
        {
            break;
        }
    }
    
    // Adiciona o caractere nulo ao final de nomeArquivo para finalizar a string
    nomeArquivo[k] = '\0';
    
    // Inverte a string nomeArquivo para obter o nome correto do arquivo
    int len = strlen(nomeArquivo);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = nomeArquivo[i];
        nomeArquivo[i] = nomeArquivo[len - i - 1];
        nomeArquivo[len - i - 1] = temp;
    }
}


int compactarArquivo()
{
    // Cria uma fila para armazenar os nós da árvore de Huffman
    Queue *fila = createQueue();
    FILE *f; // Ponteiro para o arquivo a ser compactado
    char **tabela; // Tabela de códigos de Huffman
    char *arquivoCodificado; // String que armazenará o arquivo codificado
    char caminhoArquivo[1000]; // Caminho do arquivo a ser compactado

    // Obtém o caminho do arquivo a ser compactado
    obterCaminhoArquivo(caminhoArquivo);
    // Abre o arquivo no caminho especificado
    f = abrirArquivo(caminhoArquivo);
    if (f == NULL)
        return 1;

    // Obtém o tamanho do arquivo
    long int tam_arquivo = tamArquivo(f);
    // Aloca memória para armazenar os bytes do arquivo
    unsigned char *listaBytes = malloc(tam_arquivo * sizeof(unsigned char) + 1);
    // Vetor para armazenar a frequência de cada byte no arquivo
    int frequencia[256] = {0};

    // Calcula a frequência de cada byte no arquivo
    calcularFrequencia(f, tam_arquivo, listaBytes, frequencia);
    // Enfileira os bytes na fila com base na frequência
    enfileirarBytes(fila, frequencia);

    // Cria a árvore de Huffman a partir da fila
    Node *arvore = criarArvoreHuffman(fila->head);
    // // Imprime a árvore de Huffman em pré-ordem
    // imprimirArvoreHuffmanPO(arvore);

    // Calcula o número de colunas da tabela de códigos de Huffman
    int colunas = height(arvore) + 1;
    int nos = 0; // Contador de nós da árvore
    int tamArvore = 0; // Tamanho da árvore em bytes
    int k = 0; // Índice auxiliar

    // Aloca memória para a tabela de códigos de Huffman
    tabela = alocarMapa(colunas);
    // Cria a tabela de códigos de Huffman
    criarMapa(tabela, arvore, "", colunas, &nos);

    // Vetor para armazenar a árvore de Huffman em pré-ordem
    unsigned char bytesArvore[2 * nos];
    // Salva a árvore de Huffman em pré-ordem no vetor bytesArvore
    salvarArvorePreOrdem(arvore, bytesArvore, &k, &tamArvore);

    long int tamCodificado; // Tamanho do arquivo codificado
    // Codifica o arquivo usando a tabela de códigos de Huffman
    arquivoCodificado = codificarArquivo(tabela, listaBytes, tam_arquivo, &tamCodificado);

    char nomeArquivo[1000]; // Nome do arquivo compactado
    // Cria o nome do arquivo compactado
    criarNomeArquivoCompactado(caminhoArquivo, nomeArquivo);

    // Salva o arquivo compactado
    int saida = salvarCompactado(tamCodificado, bytesArvore, arquivoCodificado, tamArvore, nomeArquivo);

    // Libera a memória alocada
    free(listaBytes);
    free(arquivoCodificado);
    free(fila);
    free(arvore);
    free(tabela);

    if (saida == 1)
        return 1;

    // Reposiciona o ponteiro do arquivo para o início
    rewind(f);
    // Fecha o arquivo
    fclose(f);
    return 0;
}

int descompactarArquivo()
{
    FILE *f; // Ponteiro para o arquivo a ser descompactado
    char caminhoArquivo[1000]; // Caminho do arquivo a ser descompactado
    unsigned short cabecalho; // Cabeçalho do arquivo compactado
    unsigned short lixo = 0; // Quantidade de bits de lixo no final do arquivo
    unsigned short tamArvore = 0; // Tamanho da árvore de Huffman em bytes

    // Índice auxiliar
    int h = 0;

    // Solicita o caminho do arquivo a ser descompactado
    printf("Insira o caminho do arquivo que deseja descompactar: ");
    fgets(caminhoArquivo, sizeof(caminhoArquivo), stdin); // Lê o caminho do arquivo
    caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o caractere de nova linha

    // Abre o arquivo em modo binário
    f = fopen(caminhoArquivo, "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Obtém o tamanho do arquivo
    long int tam_arquivo = tamArquivo(f);

    // Lê o cabeçalho do arquivo
    fread(&cabecalho, sizeof(unsigned short), 1, f);

    // Extrai a quantidade de bits de lixo do cabeçalho
    int j = 2;
    for (int i = 15; i >= 13; i--)
    {
        if (isHeaderSet(cabecalho, i))
            lixo = setHeader(lixo, j);
        j--;
    }

    // Extrai o tamanho da árvore de Huffman do cabeçalho
    for (int i = 12; i >= 0; i--)
    {
        if (isHeaderSet(cabecalho, i))
            tamArvore = setHeader(tamArvore, i);
    }

    // Vetor para armazenar a árvore de Huffman
    unsigned char arvore[tamArvore];

    // Lê a árvore de Huffman do arquivo
    for (int i = 0; i < tamArvore; i++)
        fread(&arvore[i], sizeof(unsigned char), 1, f);

    printf("\n");

    // // Imprime a árvore de Huffman
    // for (int k = 0; k < tamArvore; k++)
    //     printf("%c", arvore[k]);

    printf("\n");

    // Reconstrói a árvore de Huffman
    Node *arvoreHuffman = refazerArvore(arvore, tamArvore, &h, NULL);
    Node *aux = arvoreHuffman;

    // // Imprime a árvore de Huffman em pré-ordem
    // imprimirArvoreHuffmanPO(arvoreHuffman);

    // Remove a extensão do caminho do arquivo
    for (int i = strlen(caminhoArquivo) - 1; i >= 0; i--)
    {
        if (caminhoArquivo[i] == '.')
        {
            caminhoArquivo[i] = '\0';
            break;
        }
    }

    // Cria o nome do arquivo descompactado
    char nomeArquivo[1000];
    strcpy(nomeArquivo, "descompactado");
    strcat(nomeArquivo, caminhoArquivo);

    // Cria o arquivo descompactado
    FILE *arquivoDescompactado = fopen(nomeArquivo, "wb");
    if (arquivoDescompactado == NULL)
    {
        printf("Erro ao criar o arquivo descompactado.\n");
        return 1;
    }

    unsigned char byte; // Byte lido do arquivo compactado
    int i; // Índice auxiliar
    int nBitsLidos = 0; // Número de bits lidos

    // Lê o arquivo compactado e escreve o conteúdo descompactado no novo arquivo
    while (fread(&byte, sizeof(unsigned char), 1, f) != EOF)
    {
        long int posicaoArquivo = ftell(f);

        for (i = 7; i >= 0; i--)
        {
            if (isBitSet(byte, i))
                aux = aux->right;
            else
                aux = aux->left;

            nBitsLidos++;

            if (aux->left == NULL && aux->right == NULL)
            {
                unsigned char *item = (unsigned char *)malloc(sizeof(unsigned char));
                item = (unsigned char *)aux->item;
                unsigned char c = *item;
                fwrite(item, sizeof(unsigned char), 1, arquivoDescompactado);
                aux = arvoreHuffman;
            }

            if (posicaoArquivo == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
                break;
        }
        if (posicaoArquivo == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
            break;
    }
    // Fecha os arquivos
    fclose(f);
    fclose(arquivoDescompactado);
    return 0;
}