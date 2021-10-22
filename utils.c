#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct sCluster getCluster(int index) {
  Cluster a;
  return a ;
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
  if (!strcmp(str, "cd")) return 1;
  if (!strcmp(str, "dir\n")) return 2;
  if (!strcmp(str, "rm")) return 3;
  if (!strcmp(str, "mkdir")) return 4;
  if (!strcmp(str, "mkfile")) return 5;
  if (!strcmp(str, "edit")) return 6;
  if (!strcmp(str, "move")) return 7;
  if (!strcmp(str, "rename")) return 8;

  if (!strcmp(str, "clear\n")) return 9;
  if (!strcmp(str, "exit\n")) return 10;
  if (!strcmp(str, "\n")) return 11;
  return 0;
  }
void ascii() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
  }
void clearScreen(int a) {
  for(int i=0;i<a;i++)
    printf("\n");
  }
void begin() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
  }
void printCurrentDirectory(int index) {
  printf(ANSI_COLOR_GREEN); 
  printf("/root $ ");
  printf(ANSI_COLOR_RESET); 
  }
MetaData getMetaData(MetaData* data) {
  FILE* lightfs = fopen("lightfs.bin", "rb");
    if (NULL==lightfs) {
      fprintf(stderr, "Erro arquivo main\n");
    }
    fread(&data->indexSize, 1, 1, lightfs);
    fread(&data->clusterSize, 1, 1, lightfs);
    fread(&data->indexBegin, 1, 1, lightfs);
    fread(&data->clusterBegin, 2, 1, lightfs);
  fclose(lightfs);
  /*
  printf("indexSize: %d\n",data->indexSize);
  printf("clusterSize: %d\n",data->clusterSize);
  printf("indexBegin: %d\n",data->indexBegin);
  printf("clusterBegin: %d\n",data->clusterBegin);
  */
  return *data;
  }

void getDirName(MetaData data, int indexPosition, int cFlag) {
  int clusterSize = data.clusterSize* 1000;
  int position = data.clusterBegin  + (clusterSize * indexPosition);
  int num;
  char nome[30];
//  printf("Cluster Metadata lida em posicao = %d\n", position);
//  printf("Index position = %d\n", indexPosition);
  FILE* lightfs = fopen("lightfs.bin", "rb");
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(nome, 30, lightfs);
  fclose(lightfs);
//  printf("posicao = %d", position);
//  printf("\n%d\n",num);
  if (cFlag == 1) {
    printf(ANSI_COLOR_GREEN); 
    printf("/%s $ ",nome);
  } else printf("/%s ",nome);
  printf(ANSI_COLOR_RESET); 
}

int getDirIndex(MetaData data, char name[30]) {
  // Recebe o nome de um diretorio e retorna seu indice na tabela
  int clusterSize = data.clusterSize* 1000;
  int position = data.clusterBegin + clusterSize;
  int num;
  int index = 0;
  char indexName[30];
  FILE* lightfs = fopen("lightfs.bin", "r+b");

  printf("Index name procurado = %s\n",name); 
  do {
    index++;
    position = data.clusterBegin  + (clusterSize * index);
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(indexName, 30, lightfs);
    if (*indexName) printf("Index name = %s\n",indexName); 
    if (indexName == name) {
      fclose(lightfs);
      return index;
    }
  } while (index != 255);
  fclose(lightfs);
  printf("Nao achou getDirIndex\n)");
  return -1;
}

uint8_t findFreeSpace(MetaData data) {
  // RETORNA A POSICAO NA TABELA FAT
  // Passa pela FAT procurando 255
  // Retorna o primeiro indice com esse valor
  uint8_t position = data.indexBegin;
  int num = 0;

  FILE* lightfs = fopen("lightfs.bin", "rb");
  do {
    position++;
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == 255) {
      return position - data.indexBegin;
      fclose(lightfs);
      printf("Posicao utilizada = %d\n", position);
    }
  } while (position != 255);
  fclose(lightfs);

  return -1;
}

void mkdir(MetaData data, uint8_t currentDir, char name[30]) {
  // Alterar tabela FAT
  // Acha espaço livre
  int freePosition = findFreeSpace(data);
  // Substtui o valor colocando o diretorio atual como pai
  int position = freePosition + data.indexBegin;
  
  name = strtok(name,"\n"); // Separa o input a partir do " "
  printf("Diretorio criado na posicao %d\n",position);
  FILE* lightfs = fopen("lightfs.bin", "r+b");
    fseek(lightfs,position,SEEK_SET);
    fwrite(&currentDir, sizeof(currentDir),1, lightfs);

  // Escrever no cluster
    uint8_t flag = 111;
    int clusterSize = data.clusterSize* 1000;
    position = data.clusterBegin  + (clusterSize * freePosition);
    fseek(lightfs,position,SEEK_SET);
    fwrite(&flag, sizeof(flag),1, lightfs);
    fwrite(name, name[30],1, lightfs);
  fclose(lightfs);
//  printf("Cluster Metadata escrita em posicao = %d\n", position);
//  printf("\n%d\n",num);
}

void dir(MetaData data, uint8_t currentDir) {
  // Percorre a fat inteira achando referencias ao diretorio atual
  // Se diretorio atual == diretorio apontado na fat, imprime
  int position = data.indexBegin;
  uint8_t num = 0;
  FILE* lightfs = fopen("lightfs.bin", "r+b");
  do {
    position++;
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == currentDir) {
      getDirName(data, position - data.indexBegin,0);
      printf("\n");
    }
  } while (position != 255);
  fclose(lightfs);
}

int cd(MetaData data, uint8_t currentDir, char name[30]) {
  // Acha a posicao do diretorio desejado
  int index = getDirIndex(data,name);

  name = strtok(name,"\n"); // Separa o input a partir do " "
  // Verifica se o diretorio desejado tem como pai o diretorio atual
  uint8_t num = 0;
  FILE* lightfs = fopen("lightfs.bin", "r+b");
    fseek(lightfs,index + data.indexBegin,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == currentDir) {
      return index;
    }  
  fclose(lightfs);
  printf("ERROR\n");
  return currentDir;
}

