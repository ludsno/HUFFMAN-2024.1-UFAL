#include "teste_fila.h"

Queue *test_queue;

void test_createQueue()
{
    test_queue = createQueue();

    CU_ASSERT_PTR_NOT_NULL(test_queue);
    CU_ASSERT_PTR_NULL(test_queue->head);
}

void test_isEmpty()
{
    CU_ASSERT_TRUE(isEmpty(test_queue));
    enqueue(test_queue, 'a', 1);
    CU_ASSERT_FALSE(isEmpty(test_queue));
}

void test_enqueue()
{
    CU_ASSERT_PTR_NOT_NULL(test_queue->head);
    CU_ASSERT_EQUAL(*(unsigned char *)test_queue->head->item, 'a');

    enqueue(test_queue, 'b', 2);
    CU_ASSERT_PTR_NOT_NULL(test_queue->head->next);
    CU_ASSERT_EQUAL(*(unsigned char *)test_queue->head->next->item, 'b');
    CU_ASSERT_EQUAL(*(int *)test_queue->head->next->frequency, 2);

    enqueue(test_queue, 'c', 0);
    CU_ASSERT_EQUAL(*(unsigned char *)test_queue->head->item, 'c');
}

void test_printQueue()
{
    unsigned char expected_items[] = {'c', 'a', 'b'};
    int expected_frequencies[] = {0, 1, 2};

    Node *current = test_queue->head;

    for (int i = 0; i < 3; i++)
    {
        CU_ASSERT_PTR_NOT_NULL(current);
        CU_ASSERT_EQUAL(*(unsigned char *)current->item, expected_items[i]);
        CU_ASSERT_EQUAL(*(int *)current->frequency, expected_frequencies[i]);
        current = current->next;
    }

    CU_ASSERT_PTR_NULL(current);

    while (!isEmpty(test_queue))
    {
        Node *temp = test_queue->head;
        test_queue->head = test_queue->head->next;
        free(temp->item);
        free(temp->frequency);
        free(temp);
    }
    free(test_queue);
}