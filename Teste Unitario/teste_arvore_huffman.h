#ifndef TESTE_ARVORE_HUFFMAN_H
#define TESTE_ARVORE_HUFFMAN_H

#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../HUFFMAN/arvoreHuffman.h"

void liberarNo(Node *no);

void test_isEmptyList();
void test_max();
void test_criarNovoNo();
void test_inserirFila();
void test_criarArvoreHuffman();
void test_height();
void test_salvarArvorePreOrdem();
void test_refazerArvore();

#endif // TESTE_ARVORE_HUFFMAN_H