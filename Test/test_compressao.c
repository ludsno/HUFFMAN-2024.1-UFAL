#include <C:/msys64/mingw64/include/CUnit/CUnit.h>
#include <C:/msys64/mingw64/include/CUnit/Basic.h>
#include "fila.h"
#include "comprimir.h"
#include "descomprimir.h"

// Função de teste para tamArquivo
void test_tamArquivo(void)
{
  // Cria um arquivo de teste e escreve "Testa" nele
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "Testa");
  fclose(f);

  // Abre o arquivo para leitura e verifica o tamanho
  f = fopen("testfile.txt", "r");
  CU_ASSERT_EQUAL(tamArquivo(f), 5); // Verifica se o tamanho é 5
  fclose(f);
}

// Função de teste para abrirArquivo
void test_abrirArquivo(void)
{
  // Cria um arquivo de teste e escreve "Testa" nele
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "Testa");
  fclose(f);

  // Usa a função abrirArquivo para abrir o arquivo e verifica se não é NULL
  f = abrirArquivo("testfile.txt");
  CU_ASSERT_PTR_NOT_NULL(f); // Verifica se o arquivo foi aberto com sucesso
  fclose(f);
}

// Função de teste para criarNomeArquivoCompactado
void test_criarNomeArquivoCompactado(void)
{
  char nomeArquivo[1000];
  // Cria o nome do arquivo compactado a partir do caminho fornecido
  criarNomeArquivoCompactado("C:\\path\\to\\arquivo.txt", nomeArquivo);
  CU_ASSERT_STRING_EQUAL(nomeArquivo, "arquivo.txt"); // Verifica se o nome está correto
}

// Função de teste para calcularFrequencia
void test_calcularFrequencia(void)
{
  // Cria um arquivo de teste e escreve "abcabc" nele
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "abcabc");
  fclose(f);

  // Abre o arquivo para leitura e calcula a frequência dos bytes
  f = fopen("testfile.txt", "r");
  long int tam_arquivo = tamArquivo(f);
  unsigned char listaBytes[tam_arquivo + 1];
  int frequencia[256] = {0};

  calcularFrequencia(f, tam_arquivo, listaBytes, frequencia);
  fclose(f);

  // Verifica se as frequências estão corretas
  CU_ASSERT_EQUAL(frequencia['a'], 2);
  CU_ASSERT_EQUAL(frequencia['b'], 2);
  CU_ASSERT_EQUAL(frequencia['c'], 2);
  CU_ASSERT_EQUAL(frequencia['d'], 0); // Verifica que 'd' não está presente
}

// Função de teste para enfileirarBytes
void test_enfileirarBytes(void)
{
  // Define as frequências dos bytes
  int frequencia[256] = {0};
  frequencia['a'] = 2;
  frequencia['b'] = 2;
  frequencia['c'] = 2;

  // Cria uma fila e enfileira os bytes com suas frequências
  Queue *fila = createQueue();
  enfileirarBytes(fila, frequencia);

  // Verifica se os bytes foram enfileirados corretamente
  CU_ASSERT_EQUAL(fila->head->byte, 'a');
  CU_ASSERT_EQUAL(fila->head->frequency, 2);
  CU_ASSERT_EQUAL(fila->head->next->byte, 'b');
  CU_ASSERT_EQUAL(fila->head->next->frequency, 2);
  CU_ASSERT_EQUAL(fila->head->next->next->byte, 'c');
  CU_ASSERT_EQUAL(fila->head->next->next->frequency, 2);
  CU_ASSERT_PTR_NULL(fila->head->next->next->next); // Verifica que não há mais elementos na fila

  // Libera a memória da fila
  freeQueue(fila);
}

// Função de teste para compactarArquivo
void test_compactarArquivo(void)
{
  // Cria um arquivo de teste e escreve "abcabc" nele
  FILE *f = fopen("testfile.txt", "w");
  fprintf(f, "abcabc");
  fclose(f);

  // Executa a função de compactação
  int resultado = compactarArquivo();

  // Verifica se a função retornou sucesso
  CU_ASSERT_EQUAL(resultado, 0);

  // Verifica se o arquivo compactado foi criado
  FILE *compactado = fopen("testfile.txt.comp", "r");
  CU_ASSERT_PTR_NOT_NULL(compactado); // Verifica se o arquivo compactado existe
  if (compactado != NULL)
  {
    fclose(compactado);
  }
}

int main()
{
  // Inicializa o registro de testes
  if (CU_initialize_registry() != CUE_SUCCESS)
  {
    return CU_get_error();
  }

  // Adiciona um suite de testes
  CU_pSuite suite = CU_add_suite("Suite de Testes de Compactacao", 0, 0);
  if (suite == NULL)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Adiciona os testes ao suite
  if ((CU_add_test(suite, "Teste tamanho do arquivo", test_tamArquivo) == NULL) ||
      (CU_add_test(suite, "Teste abrir arquivo", test_abrirArquivo) == NULL) ||
      (CU_add_test(suite, "Teste criar nome do arquivo compactado", test_criarNomeArquivoCompactado) == NULL) ||
      (CU_add_test(suite, "Teste calcular frequencia", test_calcularFrequencia) == NULL) ||
      (CU_add_test(suite, "Teste enfileirar bytes", test_enfileirarBytes) == NULL) ||
      (CU_add_test(suite, "Teste compactar arquivo", test_compactarArquivo) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Executa os testes
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
