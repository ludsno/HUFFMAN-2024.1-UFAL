#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../HUFFMAN/arvoreHuffman.h"

void liberarNo(Node *no)
{
    if (no != NULL)
    {
        free(no->frequency);
        free(no->item);
        free(no);
    }
}

void test_isEmptyList()
{
    Node *head = NULL;
    CU_ASSERT_TRUE(isEmptyList(head));

    head = criarNovoNo(1, NULL, NULL, 'a');
    CU_ASSERT_FALSE(isEmptyList(head));

    liberarNo(head);
}

void test_max()
{
    CU_ASSERT_EQUAL(max(5, 10), 10);
    CU_ASSERT_EQUAL(max(-5, -10), -5);
    CU_ASSERT_EQUAL(max(0, 0), 0);
    CU_ASSERT_EQUAL(max(100, 100), 100);
    CU_ASSERT_EQUAL(max(100, 50), 100);
}

void test_criarNovoNo()
{
    Node *node = criarNovoNo(5, NULL, NULL, 'a');
    CU_ASSERT_PTR_NOT_NULL(node);
    CU_ASSERT_EQUAL(*(int *)node->frequency, 5);
    CU_ASSERT_EQUAL(*(unsigned char *)node->item, 'a');
    CU_ASSERT_PTR_NULL(node->left);
    CU_ASSERT_PTR_NULL(node->right);

    liberarNo(node);
}

void test_inserirFila()
{
    Node *fila = NULL;
    Node *node1 = criarNovoNo(3, NULL, NULL, 'a');
    Node *node2 = criarNovoNo(1, NULL, NULL, 'b');
    Node *node3 = criarNovoNo(4, NULL, NULL, 'c');

    inserirFila(&fila, node1);
    inserirFila(&fila, node2);
    inserirFila(&fila, node3);

    CU_ASSERT_EQUAL(*(int *)fila->frequency, 1);
    CU_ASSERT_EQUAL(*(int *)fila->next->frequency, 3);
    CU_ASSERT_EQUAL(*(int *)fila->next->next->frequency, 4);

    liberarNo(fila->next->next);
    liberarNo(fila->next);
    liberarNo(fila);
}

void test_criarArvoreHuffman()
{
    Node *fila = NULL;
    inserirFila(&fila, criarNovoNo(2, NULL, NULL, 'a'));
    inserirFila(&fila, criarNovoNo(3, NULL, NULL, 'b'));

    Node *arvore = criarArvoreHuffman(fila);
    CU_ASSERT_EQUAL(*(int *)arvore->frequency, 5);
    CU_ASSERT_EQUAL(*(unsigned char *)arvore->item, '\\');

    liberarNo(arvore->left);
    liberarNo(arvore->right);
    liberarNo(arvore);
}

void test_height()
{
    Node *leftChild = criarNovoNo(1, NULL, NULL, 'a');
    Node *rightChild = criarNovoNo(1, NULL, NULL, 'b');
    Node *root = criarNovoNo(2, leftChild, rightChild, '\\');

    CU_ASSERT_EQUAL(height(root), 1);

    liberarNo(leftChild);
    liberarNo(rightChild);
    liberarNo(root);
}

void test_salvarArvorePreOrdem(void)
{
    Node *leftChild = criarNovoNo(1, NULL, NULL, 'a');
    Node *rightChild = criarNovoNo(1, NULL, NULL, 'b');
    Node *root = criarNovoNo(2, leftChild, rightChild, '\\');

    unsigned char arr[10];
    int index = 0, tamArvore = 0;
    salvarArvorePreOrdem(root, arr, &index, &tamArvore);

    CU_ASSERT_EQUAL(arr[0], '*');
    CU_ASSERT_EQUAL(arr[1], 'a');
    CU_ASSERT_EQUAL(arr[2], 'b');
    CU_ASSERT_EQUAL(tamArvore, 3);

    liberarNo(leftChild);
    liberarNo(rightChild);
    liberarNo(root);
}

void test_refazerArvore(void)
{
    unsigned char preOrder[] = {'*', 'a', 'b'};
    int i = 0;
    
    Node *arvore = refazerArvore(preOrder, 3, &i, NULL);

    CU_ASSERT_EQUAL(*(unsigned char *)arvore->item, '*');
    CU_ASSERT_EQUAL(*(unsigned char *)arvore->left->item, 'a');
    CU_ASSERT_EQUAL(*(unsigned char *)arvore->right->item, 'b');
}
