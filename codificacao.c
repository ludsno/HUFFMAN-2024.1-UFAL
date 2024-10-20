#include "fila.h"
#include "codificacao.h"
/*

O código fornecido menciona várias funções que ainda precisam ser implementadas. Aqui está uma lista das funções que faltam:

1. **`height(Node *arvore)`**: Esta função deve calcular a altura da árvore de Huffman.
2. **`alocarMapa(int colunas)`**: Esta função deve alocar memória para a tabela de mapeamento dos códigos de Huffman.
3. **`criarMapa(char **tabela, Node *arvore, char *codigo, int colunas, int *nos)`**: Esta função deve criar o mapeamento dos caracteres para os códigos de Huffman.
4. **`salvarArvorePreOrdem(Node *arvore, unsigned char *bytesArvore, int *k, int *tamArvore)`**: Esta função deve salvar a árvore de Huffman em pré-ordem.
5. **`codificarArquivo(char **tabela, unsigned char *listaBytes, long int tamanho, long int *tamCodificado)`**: Esta função deve codificar o arquivo usando a tabela de códigos de Huffman.
6. **`salvarCompactado(long int tamCodificado, unsigned char *bytesArvore, char *arquivoCodificado, int tamArvore, char *nomeArquivo)`**: Esta função deve salvar o arquivo compactado.

Você precisará implementar essas funções para completar o processo de compactação do arquivo usando o algoritmo de Huffman.
*/

long int tamArquivo(FILE *f)
{
    long int tam;

    fseek(f, 0, SEEK_END);
    tam = ftell(f);
    rewind(f);

    return tam;
}

int compactarArquivo()
{
    Queue *fila = createHuffmanQueue();
    FILE *f;

    char **tabela;
    char *arquivoCodificado;

    printf("Insira o caminho do arquivo: ");

    char caminhoArquivo[1000];
    fgets(caminhoArquivo, sizeof(caminhoArquivo), stdin);
    caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0';

    f = fopen(caminhoArquivo, "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    long int tam_arquivo = tamArquivo(f);
    unsigned char *listaBytes = malloc(tam_arquivo * sizeof(unsigned char) + 1);
    int frequencia[256] = {0};
    int byte;
    long int i = 0;

    while ((byte = fgetc(f)) != EOF)
    {
        frequencia[byte]++;
        listaBytes[i++] = byte;
    }
    listaBytes[i] = '\0';

    for (int j = 0; j < 256; j++)
        if (frequencia[j] != 0)
            enqueue(fila, j, frequencia[j]);

    Node *arvore = createHuffmanTree(fila->head);

    // Falta ser implementada height()
    int colunas = height(arvore);
    int nos = 0;
    int tamArvore = 0;
    int k = 0;

    // Faltam ser implementada as funções de mapeamento
    tabela = alocarMapa(colunas);
    criarMapa(tabela, arvore, "", colunas, &nos);
    unsigned char bytesArvore[2 * nos];
    salvarArvorePreOrdem(arvore, bytesArvore, &k, &tamArvore);

    long int tamCodificado;
    arquivoCodificado = codificarArquivo(tabela, listaBytes, i, &tamCodificado);

    char nomeArquivo[1000];

    int j = strlen(caminhoArquivo) - 1;
    for(i = j; i >= 0; i--)
    {
        if(caminhoArquivo[i] == '\\')
            nomeArquivo[j--] = caminhoArquivo[i]; 
        else if (caminhoArquivo[i] == '\\')
            break;
    }

    nomeArquivo[strlen(caminhoArquivo)] = '\0';

    // Falta ser implementada a função salvarCompactado()
    int saida = salvarCompactado(tamCodificado, bytesArvore, arquivoCodificado, tamArvore, nomeArquivo);

    free(listaBytes);
    free(arquivoCodificado);
    freeQueue(fila);
    freeTree(arvore);

    if (saida == 1)
        return 1;

    rewind(f);
    fclose(f);
    return 0;
}