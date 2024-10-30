/**
 * @file codificacao.h
 * @brief Arquivo de cabeçalho para funções de codificação Huffman.
 *
 * Este arquivo contém as declarações das funções usadas para compressão
 * e descompressão de arquivos usando o algoritmo de codificação Huffman.
 */

#ifndef COMPRIMIR_H
#define COMPRIMIR_H

#include "fila.h"
#include "bytes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Calcula o tamanho de um arquivo.
 *
 * Esta função calcula o tamanho do arquivo apontado pelo ponteiro de arquivo fornecido.
 * Ela move o ponteiro do arquivo para o final, obtém a posição atual do ponteiro (que é o tamanho do arquivo),
 * e depois volta o ponteiro para o início do arquivo.
 *
 * @param f Ponteiro para o arquivo.
 * @return O tamanho do arquivo em bytes.
 */
long int tamArquivo(FILE *f);

/**
 * @brief Obtém o caminho do arquivo a ser compactado.
 *
 * Esta função solicita ao usuário que insira o caminho do arquivo para compactação
 * e remove o caractere de nova linha do final.
 *
 * @param caminhoArquivo Ponteiro para armazenar o caminho do arquivo.
 */
void obterCaminhoArquivo(char *caminhoArquivo);

/**
 * @brief Abre o arquivo no modo de leitura binária.
 *
 * @param caminhoArquivo Caminho do arquivo a ser aberto.
 * @return Ponteiro para o arquivo aberto ou NULL em caso de erro.
 */
FILE *abrirArquivo(const char *caminhoArquivo);

/**
 * @brief Calcula a frequência de cada byte no arquivo.
 *
 * @param f Ponteiro para o arquivo.
 * @param tam_arquivo Tamanho do arquivo em bytes.
 * @param listaBytes Array para armazenar os bytes lidos.
 * @param frequencia Array para armazenar a frequência dos bytes.
 */
void calcularFrequencia(FILE *f, long int tam_arquivo, unsigned char *listaBytes, int *frequencia);

/**
 * @brief Enfileira bytes com suas frequências em uma fila.
 *
 * @param fila Ponteiro para a fila.
 * @param frequencia Array contendo a frequência dos bytes.
 */
void enfileirarBytes(Queue *fila, int *frequencia);

/**
 * @brief Cria o nome do arquivo compactado.
 *
 * @param caminhoArquivo Caminho original do arquivo.
 * @param nomeArquivo Buffer para armazenar o nome do arquivo compactado.
 */
void criarNomeArquivoCompactado(const char *caminhoArquivo, char *nomeArquivo);

/**
 * @brief Comprime um arquivo usando a codificação Huffman.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int compactarArquivo();

/**
 * @brief Descomprime um arquivo usando a codificação Huffman.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */

#endif // COMPRIMIR.H