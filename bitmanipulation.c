// Bit manipulation baseado em
// https://www.mathcs.emory.edu/%7Echeung/Courses/255/Syllabus/1-C-intro/bit-array.html
#include "bitops.h"

void bitManipulation() {
/* 
int = 32bits/4bytes
*/

// Metadata 4bytes
  unsigned int metadata =  0;
  // ○ Tamanho do índice (quantas entradas o índice possui, utilizar o valor 2^8)
    //0010 ** 1000 ?

  // ○ Tamanho do cluster (utilizar o valor 32KB)
    // 0010 0000

 
  // ○ Byte onde o índice inicia (metadados iniciam no byte zero e vão até byte 3)
    // byte 4 = 0000 0100

  // ○ Byte onde inicia o primeiro cluster
    // 4bytes metadata + 256bytes indice = 
    // byte 260 = 1 0000 0100

/* 
   Indice =  entradas de 8 bits
   2^8 = 256 entradas, cada entrada 1 byte
   256/4(4bytes 1 int) = 64 ints
  */
  unsigned int indice[63];
  for (int i = 0; i < 63; i++)
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
}

