# Comparação entre Fila de Prioridade com e sem Heap

Este projeto analisa o número de comparações realizadas durante a enfileiração em uma **Fila de Prioridade**, comparando uma implementação que utiliza uma estrutura de dados de **Max-Heap** com outra que não a utiliza. 

## Objetivo

O objetivo deste projeto é demonstrar as diferenças de eficiência entre as duas abordagens, medindo o número de comparações feitas durante o processo de enfileiração. O foco é testar o **pior caso**, que ocorre quando sempre é inserido um número maior que o anterior.

## Requisitos

- **Compilador GCC**: Certifique-se de ter o GCC instalado em seu sistema.
- **R**: Necessário para rodar o script de geração de gráficos.

## Compilação e Execução

Siga os passos abaixo para compilar e executar o projeto:

1. **Compilar e abrir o executável**:
   ```bash
   gcc main.c estruturas.c -o plotar
   ./plotar
1. **Rodar o script R e abrir o PDF gerado**:
   ```bash
   Rscript plot.r
   Rplots.pdf
