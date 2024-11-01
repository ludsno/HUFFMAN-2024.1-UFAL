/**
 * @file codificacao.h
 * @brief Arquivo de cabeçalho para funções de codificação Huffman.
 *
 * Este arquivo contém as declarações das funções usadas para compressão
 * e descompressão de arquivos usando o algoritmo de codificação Huffman.
 */

#ifndef CODIFICACAO_H
#define CODIFICACAO_H

#include "fila.h"
#include "bytes.h"
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
 * @brief Comprime um arquivo usando a codificação Huffman.
 *
 * Esta função comprime um arquivo usando o algoritmo de codificação Huffman. Ela realiza as seguintes etapas:
 * 1. Lê o arquivo e calcula a frequência de cada byte.
 * 2. Constrói a árvore de Huffman com base nas frequências calculadas.
 * 3. Cria uma tabela de códigos de Huffman a partir da árvore.
 * 4. Codifica o arquivo original usando a tabela de códigos.
 * 5. Salva o arquivo comprimido, incluindo a árvore de Huffman e os dados codificados.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int compactarArquivo();

/**
 * @brief Descomprime um arquivo usando a codificação Huffman.
 *
 * Esta função descomprime um arquivo que foi comprimido usando o algoritmo de codificação Huffman. Ela realiza as seguintes etapas:
 * 1. Lê o cabeçalho do arquivo comprimido para obter o tamanho da árvore de Huffman e a quantidade de bits de lixo.
 * 2. Reconstrói a árvore de Huffman a partir dos dados lidos.
 * 3. Lê os dados comprimidos e decodifica-os usando a árvore de Huffman.
 * 4. Salva os dados descomprimidos em um novo arquivo.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int descompactarArquivo();

#endif