#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "utils.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void asciiArt();
void clearScreen(int a);
int getCommand(char* str);

int main() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
  int stop = 0;
  char input[80];
  char *ptr;

  uint8_t metaIndexSize;
  uint8_t metaClusterSize;
  uint8_t metaIndexBegin;
  uint16_t metaClusterBegin;

  FILE* lightfs = fopen("lightfs.bin", "rb");
  if (NULL==lightfs) {
    fprintf(stderr, "Erro arquivo main\n");
	}
  fread(&metaIndexSize, 1, 1, lightfs);
  fread(&metaClusterSize, 1, 1, lightfs);
  fread(&metaIndexBegin, 1, 1, lightfs);
  fread(&metaClusterBegin, 2, 1, lightfs);
  fclose(lightfs);
/*
  printf("size of metaIndexSize = %d\n",metaIndexSize);
  printf("size of meta indice = %d\n",metaClusterSize);
  printf("size of meta indice = %d\n",metaIndexBegin);
  printf("size of meta indice = %d\n",metaClusterBegin);
*/


  int dirIndex = 0;
//  Cluster currentCluster =  getCluster(dirIndex);

  do {
    printf(ANSI_COLOR_GREEN); 
//    printf("/%s/ $ ",currentCluster.name);
    printf("/root $ ");
    printf(ANSI_COLOR_RESET); 

    fgets(input,80, stdin);
    ptr = strtok(input," "); // Separa o input a partir do " "

    /*
    ptr = strtok(NULL," "); // 
    printf("Segunda: %s\n",ptr);
    */

    switch(getCommand(ptr)) {
      case 1:
        // cd
        break;

      case 2:
        // dir
        break;

      case 3:
        // rm
        break;

      case 4:
        //mkdir
        break;

      case 5:
        //mkfile
        break;

      case 6:
        //edit
        break;

      case 7:
        //move
        break;

      case 8:
        // rename
        break;

      case 9:
        clearScreen(40);
        break;

      case 10:
        stop = 1;
        break;

      case 11:
        // repete o loop
        break;

      default:
        printf(ANSI_COLOR_RED); //Set the text to the color red
        printf("unknown command ");
        printf(ANSI_COLOR_RESET); 
        printf("%s", ptr);

        break;

    }
  }  while (!stop);
  return 0;
}


void clearScreen(int a) {
  for(int i=0;i<a;i++)
    printf("\n");
}
void asciiArt() {
  printf(ANSI_COLOR_GREEN); 
  printf("                                            ");
  printf("  _     ___ ____ _   _ _____   _____ ____  \n");
  printf("                                            ");
  printf(" | |   |_ _/ ___| | | |_   _| |  ___/ ___| \n");
  printf("                                            ");
  printf(" | |    | | |  _| |_| | | |   | |_  \\____\\ \n");
  printf("                                            ");
  printf(" | |___ | | |_| |  _  | | |   |  _|  __) |\n");
  printf("                                            ");
  printf(" |_____|___\\____|_| |_| |_|   |_|   |____/\n");
  printf(ANSI_COLOR_RESET); 
}
int getCommand(char* str) {
  // Recebe o comando em str e retorna int para o swtich/case
  if (!strcmp(str, "cd\n")) return 1;
  if (!strcmp(str, "dir\n")) return 2;
  if (!strcmp(str, "rm\n")) return 3;
  if (!strcmp(str, "mkdir\n")) return 4;
  if (!strcmp(str, "mkfile\n")) return 5;
  if (!strcmp(str, "edit\n")) return 6;
  if (!strcmp(str, "move\n")) return 7;
  if (!strcmp(str, "rename\n")) return 8;

  if (!strcmp(str, "clear\n")) return 9;
  if (!strcmp(str, "exit\n")) return 10;
  if (!strcmp(str, "\n")) return 11;
  return 0;
}
