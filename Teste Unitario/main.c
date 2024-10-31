#include "teste_fila.h"
#include "teste_arvore_huffman.h"
#include "teste_bytes.h"

void createFilaSuite()
{
    CU_pSuite suite = CU_add_suite("Suite de testes para fila.c", 0, 0);
    
    CU_add_test(suite, "createQueue", test_createQueue);
    CU_add_test(suite, "isEmpty", test_isEmpty);
    CU_add_test(suite, "enqueue", test_enqueue);
    CU_add_test(suite, "imprimir fila", test_printQueue);
}

void createArvoreHuffmanSuite()
{
    CU_pSuite suite = CU_add_suite("Suite de testes para arvoreHuffman.c", 0, 0);

    CU_add_test(suite, "isEmptyList", test_isEmptyList);
    CU_add_test(suite, "max", test_max);
    CU_add_test(suite, "criarNovoNo", test_criarNovoNo);
    CU_add_test(suite, "inserirFila", test_inserirFila);
    CU_add_test(suite, "criarArvoreHuffman", test_criarArvoreHuffman);
    CU_add_test(suite, "height", test_height);
    CU_add_test(suite, "salvarArvorePreOrdem", test_salvarArvorePreOrdem);
    CU_add_test(suite, "refazerArvore", test_refazerArvore);
}

void createBytesSuite()
{
    CU_pSuite suite = CU_add_suite("Suite de testes para bytes.h", 0, 0);

    CU_add_test(suite, "isBitSet", test_isBitSet);
    CU_add_test(suite, "setBit", test_setBit);
    CU_add_test(suite, "isHeaderSet", test_isHeaderSet);
    CU_add_test(suite, "setHeader", test_setHeader);   
    CU_add_test(suite, "alocarMapa", test_alocarMapa);
    CU_add_test(suite, "criarMapa", test_criarMapa);
}


int main()
{
    CU_initialize_registry();
    
    createFilaSuite();
    createArvoreHuffmanSuite();
    createBytesSuite();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}
