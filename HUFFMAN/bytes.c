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
        tabela[i] = calloc(colunas, sizeof(char));
    return tabela;
}

// Cria um mapa de codificação a partir da árvore de Huffman

void criarMapa(char **tabela, Node *raiz, char *caminho, int colunas, int *nos)
{
    // Declara dois arrays de caracteres para armazenar os caminhos da esquerda e da direita
    char esquerda[colunas], direita[colunas];

    // Incrementa o contador de nós
    (*nos)++;

    // Verifica se o nó atual é uma folha (não possui filhos)
    if (isEmptyList(raiz->left) && isEmptyList(raiz->right))
    {
        // Se for uma folha, obtém o caractere armazenado no nó
        unsigned char c = *(unsigned char *)raiz->item;
        // Copia o caminho atual para a tabela na posição do caractere
        strcpy(tabela[c], caminho);
    }
    else
    {
        // Se não for uma folha, copia o caminho atual para os arrays esquerda e direita
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        // Adiciona '0' ao caminho da esquerda e '1' ao caminho da direita
        strcat(esquerda, "0");
        strcat(direita, "1");

        // Chama recursivamente a função criarMapa para os filhos esquerdo e direito
        criarMapa(tabela, raiz->left, esquerda, colunas, nos);
        criarMapa(tabela, raiz->right, direita, colunas, nos);
    }
}

// Calcula o tamanho total do arquivo codificado

unsigned long long int tamCodificado(char **tabela, unsigned char *listaBytes, long int tamListaBytes)
{
    unsigned long long int tam_codificado = 0;
    for (int i = 0; i != tamListaBytes; i++)
        tam_codificado += strlen(tabela[listaBytes[i]]);
    return tam_codificado + 1;
}

// Codifica o arquivo usando a tabela de codificação

char *codificarArquivo(char **tabela, unsigned char *listaBytes, long int tamListaBytes, long int *tamSaida)
{
    // Calcula o tamanho do arquivo codificado usando a tabela de codificação e a lista de bytes
    unsigned long long int tam_codificado = tamCodificado(tabela, listaBytes, tamListaBytes);
    // Define o tamanho da saída como o tamanho do arquivo codificado menos 1
    *tamSaida = tam_codificado - 1;

    // Aloca memória para o arquivo codificado
    char *arquivoCodificado = calloc(tam_codificado, sizeof(char));
    // Ponteiro auxiliar para percorrer o arquivo codificado
    char *aux = arquivoCodificado;

    // Itera sobre a lista de bytes
    for (int i = 0; i < tamListaBytes; i++)
    {
        // Copia a codificação do byte atual para o arquivo codificado
        strcpy(aux, tabela[listaBytes[i]]);
        // Avança o ponteiro auxiliar pelo comprimento da codificação copiada
        aux += strlen(tabela[listaBytes[i]]);
    }

    // Retorna o arquivo codificado
    return arquivoCodificado;
}

// Salva o arquivo compactado no formato .huff

int salvarCompactado(long int tamCodificado, unsigned char bytesArvore[], char *arquivoCodificado, int tamArvore, char nomeArquivo[])
{
    // Declara um array de caracteres para armazenar o nome do arquivo
    char str[1000];
    // Copia o nome base do arquivo para o array
    strcpy(str, nomeArquivo);
    // Adiciona a extensão ".huff" ao nome do arquivo
    strcat(str, ".huff");

    // Abre o arquivo no modo de escrita binária
    FILE *f = fopen(str, "wb");
    // Verifica se o arquivo foi criado com sucesso
    if (f == NULL)
    {
        // Se não, imprime uma mensagem de erro e retorna 1
        printf("Erro ao criar o arquivo compactado.\n");
        return 1;
    }

    // Calcula o tamanho total dos dados codificados em bits, arredondado para o byte mais próximo
    int tamTotal = (tamCodificado - (tamCodificado % 8)) + 8;
    // Calcula o número de bits de preenchimento (lixo)
    int lixo = tamTotal - tamCodificado;
    // Calcula o número de bytes necessários para armazenar os dados codificados
    int nBytes = tamTotal / 8;
    // Inicializa o cabeçalho como 0
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
    // Se ainda houver bits não escritos, escreve o último byte
    if(j != 7)
        fwrite(&byte, sizeof(unsigned char), 1, f);

    // Fecha o arquivo
    fclose(f);
    return 1;
}