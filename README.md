
# Projeto de Estruturas de Dados 2024.1 - UFAL

Este repositório reúne implementações e experimentos de algoritmos clássicos de estruturas de dados, com ênfase especial na **Codificação de Huffman** para compressão de arquivos.

## Estrutura do Projeto

- **HUFFMAN/**: Implementação completa do algoritmo de compressão e descompressão de arquivos usando Huffman.
- **Dijkstra's Algorithm/**: Apresentação teórica sobre o algoritmo de Dijkstra (sem implementação de código).
- **PLOT FP x HEAP/**: Scripts e códigos para análise comparativa entre filas de prioridade simples e com heap.
- **Test/**: Arquivos de teste e validação das implementações.

---

## Foco: Codificação de Huffman

A pasta **HUFFMAN/** contém uma implementação modular do algoritmo de Huffman, capaz de:

- Calcular a frequência de bytes em um arquivo.
- Construir a árvore de Huffman a partir das frequências.
- Gerar a tabela de códigos binários para cada byte.
- Comprimir arquivos, salvando a árvore e os dados comprimidos.
- Descomprimir arquivos, reconstruindo o original a partir do arquivo .huff.

### Principais arquivos

- `main.c`: Interface de menu para compressão/descompressão.
- `codificacao.c/.h`: Funções de compressão e descompressão.
- `arvoreHuffman.c/.h`: Construção e manipulação da árvore de Huffman.
- `fila.c/.h`: Fila de prioridade para montagem da árvore.
- `bytes.c/.h`: Utilidades para manipulação de bits e bytes.

### Como compilar e executar

1. Acesse a pasta `HUFFMAN/`.
2. Compile todos os arquivos `.c`:
    ```sh
    gcc *.c -o huffman
    ```
3. Execute o programa:
    ```sh
    ./huffman
    ```
4. Siga o menu para comprimir ou descomprimir arquivos.

#### Exemplo de uso

Ao rodar o programa, você verá um menu interativo para:
- [C] Comprimir arquivo
- [D] Descomprimir arquivo
- [F] Fechar o programa

Basta informar o caminho do arquivo desejado e seguir as instruções.

---

## Outras partes do projeto

- **Dijkstra's Algorithm/**: Apresentação teórica sobre o algoritmo de Dijkstra.
- **PLOT FP x HEAP/**: Scripts em R e C para comparar desempenho entre filas de prioridade simples e com heap.

---

## Autoria

Projeto desenvolvido para a disciplina de Estruturas de Dados - UFAL 2024.1
