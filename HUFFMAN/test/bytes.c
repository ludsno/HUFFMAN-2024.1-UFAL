#include "bytes.h"

// Verifica se o bit na posição i está setado no byte c
int isBitSet(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

// Seta o bit na posição i no byte c
unsigned char setBit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

// Verifica se o bit na posição i está setado no short c
int isHeaderSet(unsigned short c, int i)
{
    unsigned short mask = 1 << i;
    return mask & c;
}

// Seta o bit na posição i no short c
unsigned short setHeader(unsigned short c, int i)
{
    unsigned short mask = 1 << i;
    return mask | c;
}

// Aloca uma tabela de 256 ponteiros para strings, cada string com tamanho colunas
char **alocarMapa(int colunas)
{
    char **tabela;
    tabela = malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++)
        tabela[i] = calloc(colunas, sizeof(char));// t[]
    return tabela;
}

// Cria um mapa de codificação a partir da árvore de Huffman
void criarMapa(char **tabela, Node *raiz, char *caminho, int colunas, int *nos)
{
    char esquerda[colunas], direita[colunas];

    (*nos)++;

    if (isEmptyList(raiz->left) && isEmptyList(raiz->right))
    {
        unsigned char c = *(unsigned char *)raiz->item;
        strcpy(tabela[c], caminho);
    }
    else
    {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        criarMapa(tabela, raiz->left, esquerda, colunas, nos);
        criarMapa(tabela, raiz->right, direita, colunas, nos);
    }
}

// Calcula o tamanho total do arquivo codificado
unsigned long long int tamCodificado(char **tabela, unsigned char *listaBytes, long int tamListaBytes)
{
    unsigned long long int tam_codificado = 0;
    for (int i = 0; i != tamListaBytes; i++)
        tam_codificado += strlen(tabela[listaBytes[i]]);// 3+2
    return tam_codificado + 1;
}

// Codifica o arquivo usando a tabela de codificação
char *codificarArquivo(char **tabela, unsigned char *listaBytes, long int tamListaBytes, long int *tamSaida)
{
    unsigned long long int tam_codificado = tamCodificado(tabela, listaBytes, tamListaBytes);
    *tamSaida = tam_codificado - 1;

    char *arquivoCodificado = calloc(tam_codificado, sizeof(char));
    char *aux = arquivoCodificado;

    for (int i = 0; i < tamListaBytes; i++)
    {
        strcpy(aux, tabela[listaBytes[i]]);
        aux += strlen(tabela[listaBytes[i]]);
    }

    return arquivoCodificado;
}

// Salva o arquivo compactado no formato .huff
int salvarCompactado(long int tamCodificado, unsigned char bytesArvore[], char *arquivoCodificado, int tamArvore, char nomeArquivo[])
{
    char str[1000];
    strcpy(str, nomeArquivo);
    strcat(str, ".huff");

    FILE *f = fopen(str, "wb");
    if (f == NULL)
    {
        printf("Erro ao criar o arquivo compactado.\n");
        return 1;
    }

    int tamTotal = (tamCodificado - (tamCodificado % 8)) + 8;
    int lixo = tamTotal - tamCodificado;
    int nBytes = tamTotal / 8;
    unsigned short cabecalho = 0;

    // Configura os bits do cabeçalho para o tamanho da árvore
    for (int i = 12; i >= 0; i--)
        if(isHeaderSet(tamArvore, i))
            cabecalho = setHeader(cabecalho, i);

    int j = 2;

    // Configura os bits do cabeçalho para o lixo
    for (int i = 15; i >= 13; i--)
    {
        if(isHeaderSet(lixo, j))
            cabecalho = setHeader(cabecalho, i);
        j--;
    }

    // Escreve o cabeçalho no arquivo
    fwrite(&cabecalho, sizeof(unsigned short), 1, f);

    // Escreve os bytes da árvore no arquivo
    for (int i = 0; i < tamArvore; i++)
        fwrite(&bytesArvore[i], sizeof(unsigned char), 1, f);

    unsigned char byte = 0;
    j = 7;

    // Escreve o arquivo codificado bit a bit
    for (int i = 0; i < tamCodificado; i++)
    {
        if(arquivoCodificado[i] == '1')
            byte = setBit(byte, j);
        
        j--;

        if(j < 0)
        {
            j = 7;
            fwrite(&byte, sizeof(unsigned char), 1, f);
            byte = 0;
        }
    }
    if(j != 7)
        fwrite(&byte, sizeof(unsigned char), 1, f);

    fclose(f);
    return 0;
}