#include "arvoreHuffman.h"

int isEmptyList(Node *head)
{
    return head == NULL;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *criarArvoreHuffman(Node *fila)
{
    while (fila->next != NULL)
    {
        unsigned char item = '\\';
        unsigned char *itemPtr = (unsigned char *)malloc(sizeof(unsigned char));
        *itemPtr = item;

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->frequency = malloc(sizeof(int));

        *(int *)newNode->frequency = *(int *)fila->frequency + *(int *)fila->next->frequency;

        newNode->left = fila;
        newNode->right = fila->next;
        newNode->item = (void *)itemPtr;
        free(itemPtr);

        fila = fila->next->next;
        newNode->left->next = NULL;
        newNode->right->next = NULL;

        if (isEmptyList(fila) || *(int *)newNode->frequency <= *(int *)fila->frequency)
        {
            newNode->next = fila;
            fila = newNode;
        }
        else
        {
            Node *current = fila;
            while (current->next != NULL && *(int *)current->next->frequency < *(int *)newNode->frequency)
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    return fila;
}

int height(Node *arvore)
{
    if (arvore == NULL)
        return -1;
    else
        return 1 + max(height(arvore->left), height(arvore->right));
}

void salvarArvorePreOrdem(Node *arvore, unsigned char arr[], int *i, int *tamArvore)
{
    if (isEmptyList(arvore))
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

Node *refazerArvore(unsigned char str[], int n, int *i, Node *arvore)
{
    if (*i < n)
    {
        unsigned char *item = (unsigned char *)malloc(sizeof(unsigned char));
        *item = str[*i];
        (*i)++;

        if (*item == '*')
        {
            arvore = (Node *)malloc(sizeof(Node));
            arvore->item = item;
            arvore->left = NULL;
            arvore->right = NULL;
            arvore->left = refazerArvore(str, n, i, arvore->left);
            arvore->right = refazerArvore(str, n, i, arvore->right);
        }
        else
        {
            if (*item == '\\')
            {
                *item = str[*i];
                (*i)++;
            }

            arvore = (Node *)malloc(sizeof(Node));
            arvore->item = item;
            arvore->left = NULL;
            arvore->right = NULL;
        }
    }
    return arvore;
}