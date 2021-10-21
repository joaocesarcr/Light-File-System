// Bit manipulation baseado em
// https://www.mathcs.emory.edu/%7Echeung/Courses/255/Syllabus/1-C-intro/bit-array.html
#include <stdint.h> 
#include <stdlib.h> 
#include <stdio.h> 

void bitManipulation();
int main() {
  // Tamanho do índice (quantas entradas o índice possui, utilizar o valor 2^8)
  uint8_t metaIndice = 255;

  // Tamanho do cluster (utilizar o valor 32KB)
  uint8_t metaClusterSize = 32;

  // Byte onde o índice inicia (metadados iniciam no byte zero e vão até byte 3)
  uint8_t fatBegin = 5;

  // Byte onde inicia o primeiro cluster
  uint16_t clusterBegin = 259;

	FILE* out = fopen("lighfs.bin", "wb");
  if (NULL==out) {
    fprintf(stderr, "erro arquivo\n");
    exit(EXIT_FAILURE);
	}

  fwrite(&metaIndice, sizeof(metaIndice),1, out);
  fwrite(&metaClusterSize, sizeof(metaClusterSize),1, out);
  fwrite(&fatBegin, sizeof(fatBegin),1, out);
  fwrite(&clusterBegin, sizeof(clusterBegin),1, out);

	uint8_t num = 255;
  for(int i=0;i<255;i++) 
    fwrite(&num, sizeof(num),1, out);
  num = 0;
  for(int i = 0; i < 8160000;i++)
    fwrite(&num, sizeof(num),1, out);
  
   printf("COMPILADO\n");
}
