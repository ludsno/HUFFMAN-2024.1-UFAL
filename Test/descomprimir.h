/**
 * @file codificacao.h
 * @brief Cabeçalho para funções de descompactação usando codificação Huffman.
 *
 * Este arquivo contém as declarações das funções necessárias para descompactar
 * arquivos que foram compactados usando o algoritmo de codificação Huffman.
 */

#ifndef DESCOMPRIMIR_H
#define DESCOMPRIMIR_H

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Lê o caminho do arquivo a ser descompactado.
 *
 * @param caminhoArquivo Ponteiro para armazenar o caminho do arquivo.
 */
void lerCaminhoArquivo(char *caminhoArquivo);

/**
 * @brief Lê o cabeçalho do arquivo compactado e extrai as informações de lixo e tamanho da árvore.
 *
 * @param f Ponteiro para o arquivo.
 * @param lixo Ponteiro para armazenar o valor do lixo.
 * @param tamArvore Ponteiro para armazenar o tamanho da árvore de Huffman.
 * @return O valor do cabeçalho lido.
 */
unsigned short lerCabecalho(FILE *f, unsigned short *lixo, unsigned short *tamArvore);

/**
 * @brief Lê a árvore de Huffman do arquivo compactado.
 *
 * @param f Ponteiro para o arquivo.
 * @param arvore Array onde a árvore de Huffman será armazenada.
 * @param tamArvore Tamanho da árvore.
 */
void lerArvore(FILE *f, unsigned char *arvore, unsigned short tamArvore);

/**
 * @brief Gera o nome do arquivo descompactado.
 *
 * @param caminhoArquivo Caminho original do arquivo.
 * @param nomeArquivo Buffer para armazenar o nome do arquivo descompactado.
 */
void criarNomeArquivoDescompactado(char *caminhoArquivo, char *nomeArquivo);

/**
 * @brief Executa o processo de descompactação dos dados do arquivo.
 *
 * @param f Ponteiro para o arquivo compactado.
 * @param arquivoDescompactado Ponteiro para o arquivo onde os dados descompactados serão escritos.
 * @param arvoreHuffman Ponteiro para a árvore de Huffman reconstruída.
 * @param tam_arquivo Tamanho do arquivo original.
 * @param lixo Número de bits de lixo presentes no último byte.
 */
void descompactarDados(FILE *f, FILE *arquivoDescompactado, Node *arvoreHuffman, long tam_arquivo, int lixo);

/**
 * @brief Função principal que gerencia o processo de descompactação de um arquivo.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int descompactarArquivo();

#endif // DESCOMPRIMIR_H
