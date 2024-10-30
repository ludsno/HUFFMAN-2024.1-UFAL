#include "fila.h"
#include "comprimir.h"
#include "descomprimir.h"
#include "bytes.h"
#include "arvoreHuffman.h"

void imprimirMenu()
{
  printf("\n");
  printf("\n");
  printf("        _______________                               \n");
  printf("       |         ___   ____           _____          \n");
  printf("  ||   | ||   | ||    ||    |\\    /| ||   | |\\  |  \n");
  printf("  ||---| ||   | |--   |--   ||\\  / | |----| | \\ |  \n");
  printf("  ||   | ||___| ||    ||    || \\/  | ||   | |  \\|  \n");
  printf("                                ____________|       \n");

  printf("\n");
  printf("\n");
  printf("==================================================\n");
  printf("  Por favor, digite abaixo o que deseja realizar\n");
  printf("==================================================\n");
  printf("\n");
  printf("    [C]--> Comprimir arquivo\n");
  printf("    [D]--> Descomprimir arquivo\n");
  printf("    [F]--> Fechar o programa\n");
  printf("\n");
  printf("==================================================\n");
  printf("\n>>> ");
}
void imprimirConfirmacao()
{
  printf("\n===============================================================\n");
  printf("  Operacao realizada. Deseja continuar usando o programa?\n");
  printf("===============================================================\n");
  printf("\n  Digite SIM para prosseguir");
  printf("\n  Digite qualquer outra entrada para sair\n");
  printf("\n>>> ");
}

int main()
{
  char opcao[100];
  while (1)
  {
    imprimirMenu();
    int flag = 1;
    do
    {
      scanf(" %[^\n]", opcao);

      if (opcao[0] == 'F' || opcao[0] == 'f')
        break;
      else if (opcao[0] == 'C' || opcao[0] == 'c')
      {
        flag = 1;
        getchar();
        // C:\Users\cliente\Desktop
        if (compactarArquivo() == 1)
          imprimirConfirmacao();

        scanf(" %s", opcao);

        if (opcao[0] != 'S' && opcao[0] != 's')
        {
          break;
        }
      }
      else if (opcao[0] == 'D' || opcao[0] == 'd')
      {
        flag = 1;
        getchar();

        if (descompactarArquivo() == 1)
          return 1;

        imprimirConfirmacao();
        scanf(" %s", opcao);

        if (opcao[0] != 'S' && opcao[0] != 's')
        {
          opcao[0] = 'F';
          break;
        }
      }
      else
      {
        flag = 0;
        printf("\nPor favor, digite uma entrada valida\n");
        printf("\n>>> ");
      }
    } while (flag == 0);

    if (opcao[0] == 'F' || opcao[0] == 'f')
      break;
  }

  return 0;
}