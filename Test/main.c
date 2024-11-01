#include "fila.h"
#include "codificacao.h"
#include "bytes.h"
#include "arvoreHuffman.h"

int main()
{
    char opcao[100];
    while (1)
    {

        printf("\n");
        printf("==============================================\n");
        printf("Por favor, digite abaixo o que deseja realizar\n");
        printf("==============================================\n");
        printf("\n");
        printf("[C]--> Comprimir arquivo\n");
        printf("[D]--> Descomprimir arquivo\n");
        printf("[F]--> Fechar o programa\n");
        printf("\n");
        printf("==============================================\n");
        printf("\n>>> ");

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

                if (compactarArquivo() == 1)
                    printf("\n===============================================================\n");
                printf("O arquivo foi compactado. Deseja continuar usando o programa?\n");
                printf("===============================================================\n");
                printf("\nDigite SIM para prosseguir");
                printf("\nDigite qualquer outra entrada para sair\n");
                printf("\n>>> ");
                scanf(" %s", opcao);

                if (opcao[0] != 'S' && opcao[0] != 's')
                {
                    opcao[0] = 'F';
                    break;
                }
            }
            else if (opcao[0] == 'D' || opcao[0] == 'd')
            {
                flag = 1;
                getchar();

                if (descompactarArquivo() == 1)
                    return 1;

                printf("\n===============================================================\n");
                printf("O arquivo foi descompactado. Deseja continuar usando o programa?\n");
                printf("===============================================================\n");
                printf("\nDigite SIM para prosseguir");
                printf("\nDigite qualquer outra entrada para sair\n");
                printf("\n>>> ");
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