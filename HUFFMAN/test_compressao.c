#include <C:/msys64/mingw64/include/CUnit/CUnit.h>
#include <C:/msys64/mingw64/include/CUnit/Basic.h>
#include "fila.h"
#include "codificacao.h"
#include "arvoreHuffman.h"
#include "bytes.h"

// Funções de teste
void test_tamArquivo(void)
{
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "Testa");
  fclose(f);

  f = fopen("testfile.txt", "r");
  CU_ASSERT_EQUAL(tamArquivo(f), 5);
  fclose(f);
}

void test_abrirArquivo(void)
{
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "Testa");
  fclose(f);

  f = abrirArquivo("testfile.txt");
  CU_ASSERT_PTR_NOT_NULL(f);
  fclose(f);
}

void test_criarNomeArquivoCompactado(void)
{
  char nomeArquivo[1000];
  criarNomeArquivoCompactado("C:\\path\\to\\arquivo.txt", nomeArquivo);
  CU_ASSERT_STRING_EQUAL(nomeArquivo, "arquivo.txt");
}

void test_calcularFrequencia(void)
{
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "abcabc");
  fclose(f);

  f = fopen("testfile.txt", "r");
  long int tam_arquivo = tamArquivo(f);
  unsigned char listaBytes[tam_arquivo + 1];
  int frequencia[256] = {0};

  calcularFrequencia(f, tam_arquivo, listaBytes, frequencia);
  fclose(f);

  CU_ASSERT_EQUAL(frequencia['a'], 2);
  CU_ASSERT_EQUAL(frequencia['b'], 2);
  CU_ASSERT_EQUAL(frequencia['c'], 2);
  CU_ASSERT_EQUAL(frequencia['d'], 0);
}

void test_enfileirarBytes(void)
{
  Queue *fila = createQueue();
  int frequencia[256] = {0}; // Inicialize todas as frequências para zero

  // Defina as frequências para os caracteres a serem testados
  frequencia['a'] = 5;
  frequencia['b'] = 3;
  frequencia['c'] = 1;

  enfileirarBytes(fila, frequencia);

  // Verifique se a ordem é correta (ordem crescente de frequência)
  CU_ASSERT_EQUAL(*(unsigned char *)fila->head->item, 'c');
  CU_ASSERT_EQUAL(*(unsigned char *)fila->head->next->item, 'b');
  CU_ASSERT_EQUAL(*(unsigned char *)fila->head->next->next->item, 'a');
}

// Função de inicialização
int init_suite(void) { return 0; }
// Função de limpeza
int clean_suite(void) { return 0; }

// Testes para as funções da fila
void test_createQueue(void)
{
  Queue *fila = createQueue();
  CU_ASSERT_PTR_NOT_NULL(fila);
  CU_ASSERT_PTR_NULL(fila->head);
  free(fila);
}

void test_isEmpty(void)
{
  Queue *fila = createQueue();
  CU_ASSERT_TRUE(isEmpty(fila));
  free(fila);
}

void test_enqueue(void)
{
  Queue *fila = createQueue();
  enqueue(fila, 'a', 1);
  CU_ASSERT_PTR_NOT_NULL(fila->head);
  CU_ASSERT_EQUAL(*(unsigned char *)fila->head->item, 'a');
  CU_ASSERT_EQUAL(*(int *)fila->head->frequency, 1);
  free(fila->head->item);
  free(fila->head->frequency);
  free(fila->head);
  free(fila);
}

void test_printQueue(void)
{
  Queue *fila = createQueue();
  enqueue(fila, 'a', 1);
  enqueue(fila, 'b', 2);
  enqueue(fila, 'c', 3);
  printQueue(fila); // Verifique a saída manualmente
  free(fila->head->next->next->item);
  free(fila->head->next->next->frequency);
  free(fila->head->next->next);
  free(fila->head->next->item);
  free(fila->head->next->frequency);
  free(fila->head->next);
  free(fila->head->item);
  free(fila->head->frequency);
  free(fila->head);
  free(fila);
}

// Testes para as funções da árvore de Huffman

void test_isEmptyList(void)
{
  Node *head = NULL;
  CU_ASSERT_TRUE(isEmptyList(head));
}

void test_max(void)
{
  CU_ASSERT_EQUAL(max(3, 4), 4);
  CU_ASSERT_EQUAL(max(5, 2), 5);
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
// Testes para as funções de manipulação de bits
void test_isBitSet(void)
{
  CU_ASSERT_TRUE(isBitSet(0b00001000, 3));
  CU_ASSERT_FALSE(isBitSet(0b00001000, 2));
}

void test_setBit(void)
{
  CU_ASSERT_EQUAL(setBit(0b00000000, 3), 0b00001000);
  CU_ASSERT_EQUAL(setBit(0b00001000, 2), 0b00001100);
}

void test_isHeaderSet(void)
{
  CU_ASSERT_TRUE(isHeaderSet(0b00001000, 3));
  CU_ASSERT_FALSE(isHeaderSet(0b00001000, 2));
}

void test_setHeader(void)
{
  CU_ASSERT_EQUAL(setHeader(0b00000000, 3), 0b00001000);
  CU_ASSERT_EQUAL(setHeader(0b00001000, 2), 0b00001100);
}

void test_alocarMapa(void)
{
  char **mapa = alocarMapa(10);
  CU_ASSERT_PTR_NOT_NULL(mapa);
  for (int i = 0; i < 256; i++)
  {
    CU_ASSERT_PTR_NOT_NULL(mapa[i]);
    free(mapa[i]);
  }
  free(mapa);
}

void test_criarMapa(void)
{
  Queue *fila = createQueue();
  enqueue(fila, 'a', 1);
  enqueue(fila, 'b', 2);
  Node *arvore = criarArvoreHuffman(fila->head);
  char **mapa = alocarMapa(10);
  char caminho[10] = "";
  int nos = 0;
  criarMapa(mapa, arvore, caminho, 10, &nos);
  CU_ASSERT_STRING_EQUAL(mapa['a'], "0");
  CU_ASSERT_STRING_EQUAL(mapa['b'], "1");
  for (int i = 0; i < 256; i++)
  {
    free(mapa[i]);
  }
}

void test_tamCodificado(void)
{
  char **mapa = alocarMapa(10);
  strcpy(mapa['a'], "0");
  strcpy(mapa['b'], "1");
  unsigned char listaBytes[] = {'a', 'b', 'a'};
  CU_ASSERT_EQUAL(tamCodificado(mapa, listaBytes, 3), 4);
  for (int i = 0; i < 256; i++)
  {
    free(mapa[i]);
  }
  free(mapa);
}

void test_codificarArquivo(void)
{
  char **mapa = alocarMapa(10);
  strcpy(mapa['a'], "0");
  strcpy(mapa['b'], "1");
  unsigned char listaBytes[] = {'a', 'b', 'a'};
  long int tamSaida;
  char *codificado = codificarArquivo(mapa, listaBytes, 3, &tamSaida);
  CU_ASSERT_STRING_EQUAL(codificado, "010");
  CU_ASSERT_EQUAL(tamSaida, 3);
  free(codificado);
  for (int i = 0; i < 256; i++)
  {
    free(mapa[i]);
  }
  free(mapa);
}

// Teste para a função salvarCompactado
void test_salvarCompactado(void)
{
  unsigned char bytesArvore[] = {'a', 'b'};
  char arquivoCodificado[] = "010";
  int tamArvore = 2;
  char nomeArquivo[] = "teste";
  int resultado = salvarCompactado(3, bytesArvore, arquivoCodificado, tamArvore, nomeArquivo);
  CU_ASSERT_EQUAL(resultado, 1);
  // Verifique manualmente o arquivo "teste.huff" gerado
}

// Função de teste para descompactarArquivo
void test_descompactarArquivo()
{
  char caminhoCompactado[] = "testfile.txt.huff";
  char caminhoEsperado[] = "NICEEtestfile.txt";

  // Chama a função para descompactar o arquivo
  int resultado = descompactarArquivo(caminhoCompactado);

  // Verifica se o arquivo foi criado corretamente e contém os dados esperados
  FILE *fileDescompactado = fopen("descompactado_exemplo", "rb");
  FILE *fileEsperado = fopen(caminhoEsperado, "rb");

  if (fileDescompactado == NULL || fileEsperado == NULL)
  {
    CU_FAIL("Falha ao abrir os arquivos para comparação");
    if (fileDescompactado != NULL)
      fclose(fileDescompactado);
    if (fileEsperado != NULL)
      fclose(fileEsperado);
    return;
  }

  // Compara o conteúdo dos arquivos byte a byte
  unsigned char byte1, byte2;
  while (fread(&byte1, sizeof(unsigned char), 1, fileEsperado) &&
         fread(&byte2, sizeof(unsigned char), 1, fileDescompactado))
  {
    CU_ASSERT_EQUAL(byte1, byte2);
  }

  // Libera recursos
  fclose(fileDescompactado);
  fclose(fileEsperado);
  remove("descompactado_exemplo"); // Limpa o arquivo gerado pelo teste

  // Verifica se a função foi executada corretamente
  CU_ASSERT_EQUAL(resultado, 0);
}

int main()
{
  CU_initialize_registry();
  CU_pSuite pSuite = CU_add_suite("Hora da verdade", init_suite, clean_suite);

  // Adicionando testes da fila
  CU_add_test(pSuite, "test of createQueue", test_createQueue);
  CU_add_test(pSuite, "test of isEmpty", test_isEmpty);
  CU_add_test(pSuite, "test of enqueue", test_enqueue);
  CU_add_test(pSuite, "test of printQueue", test_printQueue);

  // Adicionando testes da árvore de Huffman
  CU_add_test(pSuite, "test of isEmptyList", test_isEmptyList);
  CU_add_test(pSuite, "test of max", test_max);
  CU_add_test(pSuite, "test of refazerArvore", test_refazerArvore);

  // Adicionando testes de manipulação de bits
  CU_add_test(pSuite, "test of isBitSet", test_isBitSet);
  CU_add_test(pSuite, "test of setBit", test_setBit);
  CU_add_test(pSuite, "test of isHeaderSet", test_isHeaderSet);
  CU_add_test(pSuite, "test of setHeader", test_setHeader);

  // Adicionando testes de funções de bytes
  CU_add_test(pSuite, "test of alocarMapa", test_alocarMapa);
  CU_add_test(pSuite, "test of criarMapa", test_criarMapa);
  CU_add_test(pSuite, "test of tamCodificado", test_tamCodificado);
  CU_add_test(pSuite, "test of codificarArquivo", test_codificarArquivo);
  CU_add_test(pSuite, "test of salvarCompactado", test_salvarCompactado);

  // Adicionando testes de funções de compressao
  CU_add_test(pSuite, "test of tamArquivo", test_tamArquivo);
  CU_add_test(pSuite, "test of abrirArquivo", test_abrirArquivo);
  CU_add_test(pSuite, "test of criarNomeArquivoCompactado", test_criarNomeArquivoCompactado);
  CU_add_test(pSuite, "test of calcularFrequencia", test_calcularFrequencia);
  CU_add_test(pSuite, "test of enfileirarBytes", test_enfileirarBytes);

  // Adicionando teste de descompressao
  CU_add_test(pSuite, "Testar função de descompactação de Huffman", test_descompactarArquivo);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
