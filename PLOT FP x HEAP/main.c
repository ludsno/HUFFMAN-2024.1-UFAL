#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

int main()
{
    // Criação de uma fila de prioridade
    FilaPrioridade *pq = criarFilaPrioridade();
    
    // Criação e abertura do arquivo "plot_pior_caso.csv" para escrita dos dados gerados
    // CSV = Comma-Separated Values, ou valores separados por vírgula
    FILE *plot = fopen("plot_pior_caso.csv", "w");
    
    // Escreve o cabeçalho no arquivo indicando as colunas: PRIORIDADE, FILA, HEAP
    fprintf(plot, "PRIORIDADE, FILA, HEAP\n");

    // Solicita ao usuário o número de elementos a serem inseridos
    int qnt;
    printf("Quantos numeros gerar?\n");
    scanf("%d", &qnt);


    // Criação de um heap com capacidade suficiente para armazenar 'qnt' elementos
    Heap *hp = criarHeap(qnt);
    

    // Loop para inserir elementos na fila de prioridade e no heap, até o número especificado pelo usuário
    for (int i = 1; i <= qnt; i++)
    {
        int comparacoesFila, comparacoesHeap;

        comparacoesFila = enfileirarFilaPrioridade(pq, i);
        comparacoesHeap = enfileirarHeap(hp, i);
        
        fprintf(plot, "%d, %d, %d\n", i, comparacoesFila, comparacoesHeap);
    }

    // Fechar o arquivo 
    fclose(plot);

    // Liberar a memória alocada para as estruturas
    freeFilaPrioridade(pq);
    freeHeap(hp);

    return 0;
}