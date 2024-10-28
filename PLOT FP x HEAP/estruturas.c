#include "estruturas.h"

// Fila de prioridade crescente

Node* criarNo(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->next = NULL;
    return node;
}

FilaPrioridade* criarFilaPrioridade()
{
    FilaPrioridade* pq = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));

    pq->front = NULL;
    return pq;
}

int enfileirarFilaPrioridade(FilaPrioridade* pq, int data)
{
    int comparacoes = 0;
    Node* newNode = criarNo(data);

    if (pq->front == NULL || data < pq->front->data)
    {
        newNode->next = pq->front;
        pq->front = newNode;
        comparacoes++;
    }
    else
    {
        Node* prev = NULL;
        Node* current = pq->front;

        while (current != NULL && data >= current->data)
        {
            prev = current;
            current = current->next;
            comparacoes++;
        }

        newNode->next = current;

        if (prev != NULL)
        {
            prev->next = newNode;
        }
    }
    return comparacoes;
}

void freeFilaPrioridade(FilaPrioridade* pq)
{
    Node* current = pq->front;

    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(pq);
}

// MAX-HEAP

Heap* criarHeap(int capacidade)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    heap->capacity = capacidade;
    heap->size = 0;
    heap->data = (int*)malloc(capacidade * sizeof(int));
    
    return heap;
}

int enfileirarHeap(Heap *hp, int value)
{
    if (hp->size == hp->capacity)
    {
        printf("Heap cheia!\n");
        return -1;
    }

    int i = hp->size;
    hp->data[i] = value;
    hp->size++;
    int comparacoes = 0;

    while (i > 0 && hp->data[i] > hp->data[(i - 1) / 2])
    {
        int temp = hp->data[i];
        hp->data[i] = hp->data[(i - 1) / 2];
        hp->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
        comparacoes++;
    }

    return comparacoes;
}

void freeHeap(Heap *hp)
{
    free(hp->data);
    free(hp);
}