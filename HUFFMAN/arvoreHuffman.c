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
    // Verifica se a lista está vazia ou se a frequência do novo nó é menor ou igual à frequência do primeiro nó da lista
    if (isEmptyList(*fila) || *(int *)newNode->frequency <= *(int *)(*fila)->frequency)
    {
        // Insere o novo nó no início da lista
        newNode->next = *fila;
        *fila = newNode;
    }
    else
    {
        // Percorre a lista para encontrar a posição correta para inserir o novo nó
        Node *current = *fila;
        while (current->next != NULL && *(int *)current->next->frequency < *(int *)newNode->frequency)
            // Avança para o próximo nó na lista
            current = current->next;
        // Insere o novo nó na posição encontrada
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Cria a árvore de Huffman a partir da fila de prioridade

Node *criarArvoreHuffman(Node *fila)
{
    // Loop através da fila até o penúltimo elemento
    while (fila->next != NULL)
    {
        // Combina as frequências dos dois primeiros nós na fila
        int combinedFrequency = *(int *)fila->frequency + *(int *)fila->next->frequency;
        
        // Cria um novo nó com a frequência combinada e os dois primeiros nós como filhos
        Node *newNode = criarNovoNo(combinedFrequency, fila, fila->next, '\\');
        
        // Move o ponteiro da fila para o próximo par de nós
        fila = fila->next->next;
        
        // Desconecta os filhos esquerdo e direito do novo nó da fila
        newNode->left->next = NULL;
        newNode->right->next = NULL;
        
        // Insere o novo nó de volta na fila
        inserirFila(&fila, newNode);
    }
    
    // Retorna o nó final na fila, que é a raiz da árvore de Huffman
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
    if (!isEmptyList(arvore)) // Verifica se a árvore não está vazia
    {
        unsigned char c = *(unsigned char *)arvore->item; // Obtém o item do nó atual
        if (arvore->left == NULL && arvore->right == NULL) // Verifica se o nó é uma folha
        {
            if (c == '*' || c == '\\') // Verifica se o caractere é '*' ou '\'
            {
                arr[*i] = '\\'; // Adiciona o caractere de escape '\' ao array
                (*i)++; // Incrementa o índice do array
                (*tamArvore)++; // Incrementa o tamanho da árvore
            }
            arr[*i] = c; // Adiciona o caractere da folha ao array
        }
        else
            arr[*i] = '*'; // Adiciona '*' ao array para indicar um nó interno

        (*i)++; // Incrementa o índice do array
        (*tamArvore)++; // Incrementa o tamanho da árvore
        salvarArvorePreOrdem(arvore->left, arr, i, tamArvore); // Salva a subárvore esquerda em ordem pré-fixada
        salvarArvorePreOrdem(arvore->right, arr, i, tamArvore); // Salva a subárvore direita em ordem pré-fixada
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
