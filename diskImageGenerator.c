#include <stdint.h> 
#include <stdlib.h> 
#include <stdio.h> 

int main() {
  // Tamanho do índice
  //(quantas entradas o índice possui, utilizar o valor 2^8)
  uint8_t metaIndice = 255;

  // Tamanho do cluster (utilizar o valor 32KB)
  uint8_t metaClusterSize = 32;

  // Byte onde o índice inicia 
  uint8_t fatBegin = 5;

  // Byte onde inicia o primeiro cluster
  uint16_t clusterBegin = 259;

  FILE* out = fopen("lightfs.bin", "wb");
  if (NULL==out) {
    fprintf(stderr, "erro arquivo\n");
    exit(EXIT_FAILURE);
	}

  fwrite(&metaIndice, sizeof(metaIndice),1, out);
  fwrite(&metaClusterSize, sizeof(metaClusterSize),1, out);
  fwrite(&fatBegin, sizeof(fatBegin),1, out);
  fwrite(&clusterBegin, sizeof(clusterBegin),1, out);

  // Primeira entrada no índice = ROOT
  uint8_t num = 0;
    fwrite(&num, sizeof(num),1, out);

  // Preenche o resto com FF
	num = 255;
  for(int i=0;i<254;i++) 
    fwrite(&num, sizeof(num),1, out);

  // Inicia a escrita dos clusters
  // Primeiro metadados
  // Diretorio 
  num = 1;
  fwrite(&num, sizeof(num),1, out);
  // Nome
  char nome[30] = "root";
  fwrite(&nome, 30,1, out);
  // Prox Cluster
  num = 0;
  fwrite(&num, sizeof(num) * 4,1, out);
  // Size
  fwrite(&num, sizeof(num) * 4,1, out);
  // 32 000 - (8 + 240 + 32 + 32)
  // 32.000bytes - 312bits

  num = 0;
//  for(int i = 0; i < 8160000;i++)
  for(int i = 0; i < 816000;i++)
    fwrite(&num, sizeof(num),1, out);
}
