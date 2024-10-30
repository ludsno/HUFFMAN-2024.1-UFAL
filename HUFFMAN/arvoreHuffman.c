#include "arvoreHuffman.h"

// Verifica se a lista está vazia
int isEmptyList(Node *head)
{
    return head == NULL;
}

// Retorna o maior valor entre dois inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Cria um novo nó da árvore de Huffman
Node *criarNovoNo(int frequency, Node *left, Node *right, unsigned char item)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->frequency = malloc(sizeof(int));
    *(int *)newNode->frequency = frequency;
    newNode->item = malloc(sizeof(unsigned char));
    *(unsigned char *)newNode->item = item;
    newNode->left = left;
    newNode->right = right;
    newNode->next = NULL;
    return newNode;
}

// Insere um nó na fila de prioridade (lista ligada ordenada)
void inserirFila(Node **fila, Node *newNode)
{
    if (isEmptyList(*fila) || *(int *)newNode->frequency <= *(int *)(*fila)->frequency)
    {
        newNode->next = *fila;
        *fila = newNode;
    }
    else
    {
        Node *current = *fila;
        while (current->next != NULL && *(int *)current->next->frequency < *(int *)newNode->frequency)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Cria a árvore de Huffman a partir da fila de prioridade
Node *criarArvoreHuffman(Node *fila)
{
    while (fila->next != NULL)
    {
        int combinedFrequency = *(int *)fila->frequency + *(int *)fila->next->frequency;
        Node *newNode = criarNovoNo(combinedFrequency, fila, fila->next, '\\');
        fila = fila->next->next;
        newNode->left->next = NULL;
        newNode->right->next = NULL;
        inserirFila(&fila, newNode);
    }
    return fila;
}

// Calcula a altura da árvore de Huffman
int height(Node *arvore)
{
    if (arvore == NULL)
        return -1;
    return 1 + max(height(arvore->left), height(arvore->right));
}

// Salva a árvore de Huffman em ordem pré-fixada (pre-order) em um array
void salvarArvorePreOrdem(Node *arvore, unsigned char arr[], int *i, int *tamArvore)
{
    if (!isEmptyList(arvore))
    {
        unsigned char c = *(unsigned char *)arvore->item;
        if (arvore->left == NULL && arvore->right == NULL)
        {
            if (c == '*' || c == '\\')
            {
                arr[*i] = '\\';
                (*i)++;
                (*tamArvore)++;
            }
            arr[*i] = c;
        }
        else
            arr[*i] = '*';

        (*i)++;
        (*tamArvore)++;
        salvarArvorePreOrdem(arvore->left, arr, i, tamArvore);
        salvarArvorePreOrdem(arvore->right, arr, i, tamArvore);
    }
}

// Imprime a árvore de Huffman em ordem pré-fixada (pre-order)
void imprimirArvoreHuffmanPO(Node *arvore)
{
    if (!isEmptyList(arvore))
    {
        unsigned char c = *(unsigned char *)arvore->item;
        if (arvore->left == NULL && arvore->right == NULL)
            printf("%c ", c);
        else
            printf("* ");
        imprimirArvoreHuffmanPO(arvore->left);
        imprimirArvoreHuffmanPO(arvore->right);
    }
}

// Cria uma folha da árvore de Huffman
Node *criarFolha(unsigned char item)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->item = malloc(sizeof(unsigned char));
    *(unsigned char *)node->item = item;
    node->left = node->right = node->next = NULL;
    return node;
}

// Reconstrói a árvore de Huffman a partir de uma string em ordem pré-fixada (pre-order)
Node *refazerArvore(unsigned char str[], int n, int *i, Node *arvore)
{
    if (*i >= n)
        return NULL;

    unsigned char item = str[(*i)++];
    if (item == '*')
    {
        arvore = criarFolha(item);
        arvore->left = refazerArvore(str, n, i, arvore->left);
        arvore->right = refazerArvore(str, n, i, arvore->right);
    }
    else
    {
        if (item == '\\')
            item = str[(*i)++];
        arvore = criarFolha(item);
    }
    return arvore;
}
