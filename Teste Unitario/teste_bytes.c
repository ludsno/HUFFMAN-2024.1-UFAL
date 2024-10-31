#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "teste_bytes.h"

void test_isBitSet()
{
    unsigned char c = 0b10101010; // 170

    CU_ASSERT_TRUE(isBitSet(c, 1));
    CU_ASSERT_FALSE(isBitSet(c, 2));
    CU_ASSERT_TRUE(isBitSet(c, 3));
    CU_ASSERT_FALSE(isBitSet(c, 0));
}

void test_setBit()
{
    unsigned char c = 0b00000000; // 0
    c = setBit(c, 3);

    CU_ASSERT_TRUE(isBitSet(c, 3));
    CU_ASSERT_FALSE(isBitSet(c, 1));
}

void test_isHeaderSet()
{
    unsigned short c = 0b1010101010101010; // 4369

    CU_ASSERT_TRUE(isHeaderSet(c, 1));
    CU_ASSERT_FALSE(isHeaderSet(c, 2));
    CU_ASSERT_TRUE(isHeaderSet(c, 3));
}

void test_setHeader()
{
    unsigned short c = 0b0000000000000000;
    c = setHeader(c, 10);

    CU_ASSERT_TRUE(isHeaderSet(c, 10));
    CU_ASSERT_FALSE(isHeaderSet(c, 1));
}

void test_alocarMapa()
{
    int colunas = 10;
    char **tabela = alocarMapa(colunas);

    CU_ASSERT_PTR_NOT_NULL(tabela);

    for (int i = 0; i < 256; i++)
    {
        CU_ASSERT_PTR_NOT_NULL(tabela[i]);
        CU_ASSERT_EQUAL(strlen(tabela[i]), 0);
    }

    for (int i = 0; i < 256; i++)
    {
        free(tabela[i]);
    }
    
    free(tabela);
}

void test_criarMapa()
{
    char *tabela[256] = {0};

    for (int i = 0; i < 256; i++)
    {
        tabela[i] = malloc(256 * sizeof(unsigned char));
    }

    int nos = 0;

    Node nodeA = { (void *)(unsigned char *)"A", NULL, NULL, NULL };
    Node nodeB = { (void *)(unsigned char *)"B", NULL, NULL, NULL };
    Node root = { NULL, NULL, NULL, &nodeA, &nodeB };

    criarMapa(tabela, &root, "", 256, &nos);

    CU_ASSERT_STRING_EQUAL(tabela['A'], "0");
    CU_ASSERT_STRING_EQUAL(tabela['B'], "1");
    CU_ASSERT_EQUAL(nos, 3);

    for (int i = 0; i < 256; i++)
    {
        free(tabela[i]);
    }
}
