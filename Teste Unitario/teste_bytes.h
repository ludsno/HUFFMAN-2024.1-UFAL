#ifndef TESTE_BYTES_H
#define TESTE_BYTES_H

#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../HUFFMAN/bytes.h"

void test_isBitSet();
void test_setBit();
void test_isHeaderSet();
void test_setHeader();
void test_alocarMapa();
void test_criarMapa();

#endif // TESTE_BYTES_H