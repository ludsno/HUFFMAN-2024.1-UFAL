#include "fila.h"
#include "codificacao.h"

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
int compactarArquivo()
{
    Queue *fila = createQueue(); // Cria uma fila para armazenar os nós da árvore de Huffman
    FILE *f;

    char **tabela;           // Tabela de códigos de Huffman
    char *arquivoCodificado; // Arquivo codificado

    printf("Insira o caminho do arquivo que deseja compactar: ");

    char caminhoArquivo[1000];
    fgets(caminhoArquivo, sizeof(caminhoArquivo), stdin); // Lê o caminho do arquivo
    caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o caractere de nova linha

    f = fopen(caminhoArquivo, "rb"); // Abre o arquivo em modo binário
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    long int tam_arquivo = tamArquivo(f);                                        // Obtém o tamanho do arquivo
    unsigned char *listaBytes = malloc(tam_arquivo * sizeof(unsigned char) + 1); // Aloca memória para armazenar os bytes do arquivo
    int frequencia[256] = {0};                                                   // Array para armazenar a frequência de cada byte
    int byte;
    long int i = 0;

    // Lê o arquivo byte a byte e calcula a frequência de cada byte
    while ((byte = fgetc(f)) != EOF)
    {
        frequencia[byte]++;
        listaBytes[i] = byte;
        i++;
    }
    listaBytes[i] = '\0';

    // Enfileira os bytes com suas respectivas frequências
    for (int j = 0; j < 256; j++)
        if (frequencia[j] != 0)
            enqueue(fila, j, frequencia[j]);

    // Falta ser implementada a função createHuffmanTree()
    Node *arvore = criarArvoreHuffman(fila->head); // Cria a árvore de Huffman

    imprimirArvoreHuffmanPO(arvore);

    // Falta ser implementada height()
    int colunas = height(arvore); // Calcula a altura da árvore
    int nos = 0;
    int tamArvore = 0;
    int k = 0;

    tabela = alocarMapa(colunas);                 // Aloca memória para a tabela de códigos
    criarMapa(tabela, arvore, "", colunas, &nos); // Cria a tabela de códigos
    unsigned char bytesArvore[2 * nos];
    salvarArvorePreOrdem(arvore, bytesArvore, &k, &tamArvore); // Salva a árvore em pré-ordem

    long int tamCodificado;
    arquivoCodificado = codificarArquivo(tabela, listaBytes, i, &tamCodificado); // Codifica o arquivo

    char nomeArquivo[1000];

    int j = strlen(caminhoArquivo) - 1;
    for (i = j; i >= 0; i--)
    {
        if (caminhoArquivo[i] != '\\')
        {
            nomeArquivo[j] = caminhoArquivo[i];
            j--;
        }
        else if (caminhoArquivo[i] == '\\')
            break;
    }

    nomeArquivo[strlen(caminhoArquivo)] = '\0';

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

    rewind(f);
    fclose(f);
    return 0;
}

// Função para descompactar o arquivo
int descompactarArquivo()
{
    FILE *f;
    char caminhoArquivo[1000];
    unsigned short cabecalho;
    unsigned short lixo = 0;
    unsigned short tamArvore = 0;

    // Índice
    int h = 0;

    printf("Insira o caminho do arquivo que deseja descompactar: ");
    fgets(caminhoArquivo, sizeof(caminhoArquivo), stdin); // Lê o caminho do arquivo
    caminhoArquivo[strcspn(caminhoArquivo, "\n")] = '\0'; // Remove o caractere de nova linha

    f = fopen(caminhoArquivo, "rb"); // Abre o arquivo em modo binário
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    long int tam_arquivo = tamArquivo(f); // Obtém o tamanho do arquivo

    fread(&cabecalho, sizeof(unsigned short), 1, f); // Lê o cabeçalho do arquivo

    int j = 2;
    for (int i = 15; i >= 13; i--)
    {
        if (isHeaderSet(cabecalho, i))
            lixo = setHeader(lixo, j);
        j--;
    }

    for (int i = 12; i >= 0; i--)
    {
        if (isHeaderSet(cabecalho, i))
            tamArvore = setHeader(tamArvore, i);
    }

    unsigned char arvore[tamArvore];

    for (int i = 0; i < tamArvore; i++)
        fread(&arvore[i], sizeof(unsigned char), 1, f); // Lê a árvore do arquivo

    printf("\n");

    for (int k = 0; k < tamArvore; k++)
        printf("%c", arvore[k]);

    printf("\n");

    // Falta ser implementada a função refazerArvore()
    Node *arvoreHuffman = refazerArvore(arvore, tamArvore, &h, NULL); // Reconstrói a árvore de Huffman
    Node *aux = arvoreHuffman;

    imprimirArvoreHuffmanPO(arvoreHuffman);

    for (int i = strlen(caminhoArquivo) - 1; i >= 0; i--)
    {
        if (caminhoArquivo[i] == '.')
        {
            caminhoArquivo[i] = '\0';
            break;
        }
    }

    char nomeArquivo[1000];
    strcpy(nomeArquivo, "descompactado");
    strcat(nomeArquivo, caminhoArquivo);

    FILE *arquivoDescompactado = fopen(nomeArquivo, "wb"); // Cria o arquivo descompactado
    if (arquivoDescompactado == NULL)
    {
        printf("Erro ao criar o arquivo descompactado.\n");
        return 1;
    }

    unsigned char byte;
    int i;
    int nBitsLidos = 0;

    // Lê o arquivo compactado e escreve o conteúdo descompactado no novo arquivo
    while (fread(&byte, sizeof(unsigned char), 1, f))
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
                fwrite(&c, sizeof(unsigned char), 1, arquivoDescompactado);
                aux = arvoreHuffman;
            }

            if (posicaoArquivo == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
                break;
        }
        if (posicaoArquivo == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
            break;
    }
    fclose(f);
    fclose(arquivoDescompactado);
    return 0;
}