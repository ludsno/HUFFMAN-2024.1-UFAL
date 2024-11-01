#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H

#include "fila.h"

/**
 * @brief Verifica se a lista está vazia.
 *
 * @param head Ponteiro para o início da lista.
 * @return int Retorna 1 se a lista estiver vazia, 0 caso contrário.
 */
int isEmptyList(Node *head);

/**
 * @brief Retorna o máximo de dois inteiros.
 *
 * @param a Primeiro inteiro.
 * @param b Segundo inteiro.
 * @return int O máximo entre a e b.
 */
int max(int a, int b);

/**
 * @brief Cria um novo nó da árvore de Huffman.
 *
 * @param frequency Frequência do nó.
 * @param left Ponteiro para o nó filho à esquerda.
 * @param right Ponteiro para o nó filho à direita.
 * @param item Item armazenado no nó.
 * @return Node* Ponteiro para o novo nó criado.
 */
Node *criarNovoNo(int frequency, Node *left, Node *right, unsigned char item);

/**
 * @brief Insere um nó na fila de prioridade (lista ligada ordenada).
 *
 * @param fila Ponteiro para o início da fila.
 * @param newNode Ponteiro para o novo nó a ser inserido.
 */
void inserirFila(Node **fila, Node *newNode);

/**
 * @brief Cria uma árvore de Huffman a partir de uma lista de nós.
 *
 * @param fila Ponteiro para o início da lista de nós.
 * @return Node* Ponteiro para a raiz da árvore de Huffman criada.
 */
Node *criarArvoreHuffman(Node *fila);

/**
 * @brief Calcula a altura da árvore de Huffman.
 *
 * @param arvore Ponteiro para a raiz da árvore de Huffman.
 * @return int A altura da árvore de Huffman.
 */
int height(Node *arvore);

/**
 * @brief Salva a árvore de Huffman em percurso pré-ordem.
 *
 * @param arvore Ponteiro para a raiz da árvore de Huffman.
 * @param array Array para armazenar o percurso pré-ordem.
 * @param i Ponteiro para o índice atual no array.
 * @param tamArvore Ponteiro para o tamanho da árvore.
 */
void salvarArvorePreOrdem(Node *arvore, unsigned char array[], int *i, int *tamArvore);

/**
 * @brief Imprime a árvore de Huffman em ordem pré-fixada (pre-order).
 *
 * @param arvore Ponteiro para a raiz da árvore de Huffman.
 */
void imprimirArvoreHuffmanPO(Node *arvore);

/**
 * @brief Cria uma folha da árvore de Huffman.
 *
 * @param item Item armazenado na folha.
 * @return Node* Ponteiro para a folha criada.
 */
Node *criarFolha(unsigned char item);

/**
 * @brief Reconstrói a árvore de Huffman a partir de uma string de percurso pré-ordem.
 *
 * @param string Array contendo o percurso pré-ordem.
 * @param size Tamanho do array.
 * @param i Ponteiro para o índice atual no array.
 * @param tree Ponteiro para a raiz da árvore de Huffman.
 * @return Node* Ponteiro para a árvore de Huffman reconstruída.
 */
Node *refazerArvore(unsigned char string[], int size, int *i, Node *tree);

#endif // ARVOREHUFFMAN_H