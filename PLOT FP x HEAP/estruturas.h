
#ifndef FILAPRIORIDADES_H
#define FILAPRIORIDADES_H

#include <stdio.h>
#include <stdlib.h>

// Fila de prioridade crescente

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
} FilaPrioridade;

Node *criarNo(int data);
FilaPrioridade* criarFilaPrioridade();
int enfileirarFilaPrioridade(FilaPrioridade* pq, int data);
void freeFilaPrioridade(FilaPrioridade* pq);

// Max-Heap

typedef struct {
    int *data;
    int capacity;
    int size;
} Heap;

Heap *criarHeap(int capacidade);
int enfileirarHeap(Heap *hp, int value);
void freeHeap(Heap *hp);

#endif /* FILAPRIORIDADES_H */
