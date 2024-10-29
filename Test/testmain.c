// Função para obter o tamanho do arquivo
long int tamArquivo(FILE *f)
{
  fseek(f, 0, SEEK_END);
  long int tam = ftell(f);
  rewind(f);
  return tam;
}

// Função para obter caminho do arquivo com entrada do usuário
void obterCaminho(char *caminho, const char *mensagem)
{
  printf("%s", mensagem);
  fgets(caminho, 1000, stdin);
  caminho[strcspn(caminho, "\n")] = '\0';
}

// Função para ler cabeçalho e definir lixo e tamanho da árvore
void lerCabecalho(FILE *f, unsigned short *lixo, unsigned short *tamArvore)
{
  unsigned short cabecalho;
  fread(&cabecalho, sizeof(unsigned short), 1, f);

  *lixo = (cabecalho >> 13) & 0x7; // 3 bits mais significativos para lixo
  *tamArvore = cabecalho & 0x1FFF; // 13 bits para tamanho da árvore
}

// Função para reconstruir e descompactar o arquivo
int descompactarArquivo()
{
  char caminho[1000];
  obterCaminho(caminho, "Insira o caminho do arquivo que deseja descompactar: ");

  FILE *f = fopen(caminho, "rb");
  if (!f)
  {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }
  long int tam_arquivo = tamArquivo(f);

  unsigned short lixo, tamArvore;
  lerCabecalho(f, &lixo, &tamArvore);

  unsigned char arvoreBytes[tamArvore];
  fread(arvoreBytes, sizeof(unsigned char), tamArvore, f);

  Node *arvoreHuffman = refazerArvore(arvoreBytes, tamArvore, NULL);
  if (!arvoreHuffman)
  {
    fclose(f);
    return 1;
  }

  // Define o nome do arquivo de saída
  char nomeSaida[1000] = "descompactado_";
  strcat(nomeSaida, caminho);
  FILE *saida = fopen(nomeSaida, "wb");
  if (!saida)
  {
    printf("Erro ao criar o arquivo descompactado.\n");
    fclose(f);
    return 1;
  }

  unsigned char byte;
  Node *aux = arvoreHuffman;
  int nBitsLidos = 0;

  while (fread(&byte, sizeof(unsigned char), 1, f) == 1)
  {
    for (int i = 7; i >= 0; i--)
    {
      aux = isBitSet(byte, i) ? aux->right : aux->left;
      nBitsLidos++;

      // Quando encontra uma folha, escreve o caractere no arquivo descompactado
      if (!aux->left && !aux->right)
      {
        fwrite(&aux->item, sizeof(unsigned char), 1, saida);
        aux = arvoreHuffman;
      }

      if (ftell(f) == tam_arquivo && (nBitsLidos + lixo) % 8 == 0)
        break;
    }
  }

  fclose(f);
  fclose(saida);
  return 0;
}