// Bit manipulation baseado em
// https://www.mathcs.emory.edu/%7Echeung/Courses/255/Syllabus/1-C-intro/bit-array.html
#include "bitops.h"
#include <stdint.h> 

void bitManipulation() {
/* 
int = 32bits/4bytes
*/

// Metadata 8bytes 
// 2 bytes cada entrada

  uint16_t metaIndice = 256

  // ○ Tamanho do índice (quantas entradas o índice possui, utilizar o valor 2^8)
  // indice 0 - 15
  // 0000 0001 0000 0000

  // ○ Tamanho do cluster (utilizar o valor 32KB)
  // 16 - 31
  uint8_t metaTamanhoCuster = 32

  // ○ Byte onde o índice inicia (metadados iniciam no byte zero e vão até byte 7)
  // 0000 0111
  // 32 - 47
  uint8_t metaTamanhoCuster = 24

  // ○ Byte onde inicia o primeiro cluster
  // 8bytes metadata + 256bytes indice =  byte 264 
  // 100001000
  // 48- 63

/* 
   Indice =  entradas de 8 bits
   2^8 = 256 entradas, cada entrada 1 byte
   256/4(4bytes 1 int) = 64 ints
  */
  unsigned int indice[63];
  for (int i = 0; i < 64; i++)
    indice[i] = 0;                    // Clear the bit array

// ○ ponteiro
// ○ EOF
// ○ vazio
// ○ corrompido

  /*
    Os clusters são posicionados logo abaixo do índice e possuem 32KB de tamanho cada.
    A estrutura interna dos clusters é de livre escolha do grupo
    32KB = 256000bits = 8000ints cada cluster
    256 cluster totais
  */
  // dependerá do espaco que deixarmos para a arvore
  unsigned int clusters[255][8000];
  for (i = 0; i < 256; i++) {
    for(int j = 0; j<8000; j++) 
      clusters[i][j] = 0;
  }

