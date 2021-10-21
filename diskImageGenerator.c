// Bit manipulation baseado em
// https://www.mathcs.emory.edu/%7Echeung/Courses/255/Syllabus/1-C-intro/bit-array.html
#include <stdint.h> 
#include <stdlib.h> 
#include <stdio.h> 

void bitManipulation();
int main() {
  bitManipulation();
  return 0;
}
void bitManipulation() {
// Metadata 8bytes 
// 2 bytes cada entrada

  uint8_t metaIndice = 255;
  
  // ○ Tamanho do índice (quantas entradas o índice possui, utilizar o valor 2^8)
  // indice 0 - 15

  // ○ Tamanho do cluster (utilizar o valor 32KB)
  // 16 - 31
  uint8_t metaClusterSize = 32;

  // ○ Byte onde o índice inicia (metadados iniciam no byte zero e vão até byte 3)
  // 0000 0111
  // 32 - 47
  uint8_t fatBegin = 4;

  // ○ Byte onde inicia o primeiro cluster
  // 8bytes metadata + 256bytes indice =  byte 264 
  // 100001000
  // 48- 63
  uint16_t clusterBegin = 259;

/*
  uint8_t indice[254];
  for (int i = 0; i < 255; i++)
    indice[i] = 255;                    // Clear the bit array
*/

  /*
    Os clusters são posicionados logo abaixo do índice e possuem 32KB de tamanho cada.
    A estrutura interna dos clusters é de livre escolha do grupo
    32KB = 256000bits = 8000ints cada cluster
    256 cluster totais
   dependerá do espaco que deixarmos para a arvore
  
 
  unsigned int clusters[255][8000];
  for (int i = 0; i < 256; i++) {
    for(int j = 0; j<8000; j++) 
      clusters[i][j] = 0;
  }

  */

	FILE* out = fopen("lighfs.bin", "wb");
   if (NULL==out) {
       fprintf(stderr, "I bet you saw THAT coming.\n");
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

   for(int i = 0; i < 8160000;i++){
       fwrite(&num, sizeof(num),1, out);
   }

/*
*/
/*
   for(int i = 0; i < 8160000;i++){
       fwrite(&num, sizeof(num),1, out);
   }
   if(ferror(out)){
      perror(__func__);
      exit(EXIT_FAILURE);
   }
   */
   printf("COMPILADO!\n");
}
