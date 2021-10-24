#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "commands.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

MetaData getMetaData(MetaData* data) {
  // Le os metadados no comeco do arquive e preenche uma
  // struct
  FILE* lightfs = fopen("lightfs.bin", "rb");
    if (NULL==lightfs) {
      fprintf(stderr, "Erro arquivo main\n");
    }
    fread(&data->indexSize, 1, 1, lightfs);
    fread(&data->clusterSize, 1, 1, lightfs);
    fread(&data->indexBegin, 1, 1, lightfs);
    fread(&data->clusterBegin, 2, 1, lightfs);
  fclose(lightfs);
  return *data;
  }

char* getDirName(MetaData data, int indexPosition) {
  // Printa o nome de um diretorio a partir de seu indice
  int clusterSize = data.clusterSize* 1000;
  // Calcula o byte ocupado pelo nome do cluster
  int position = data.clusterBegin  + (clusterSize * indexPosition);
  int num;
  char *name;
  FILE* lightfs = fopen("lightfs.bin", "rb");
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(name, 30, lightfs);
  fclose(lightfs);
  puts(name);
  return name;
}

int getDirIndex(MetaData data, char name[30]) {
  // Recebe o nome de um diretorio e retorna seu indice na tabela
  int clusterSize = data.clusterSize* 1000;
  int position = data.clusterBegin + clusterSize;
  int num;
  int index = 0;
  char indexName[30];
  FILE* lightfs = fopen("lightfs.bin", "r+b");

//  printf("Index name procurado = %s\n",name); 
  do {
    index++;
    position = data.clusterBegin  + (clusterSize * index);
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(indexName, 30, lightfs);
//    if (*indexName) printf("Index name = %s\n",indexName); 
    if (!strcmp(indexName,name)) {
      fclose(lightfs);
      return index;
    }
  } while (index != 255);
  fclose(lightfs);
  printf(ANSI_COLOR_RED); 
  printf("%s not found\n",name);
  printf(ANSI_COLOR_RESET); 
  return -1;
  }

uint8_t findFreeSpace(MetaData data) {
  // Retorna a primeira posicao vazia na tablea FAT
  // Retorno = indice na tabela fat
  
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

int findParent(MetaData data, int dir) {
  uint8_t position = data.indexBegin + dir;
  int num = 0;

  FILE* lightfs = fopen("lightfs.bin", "rb");
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
  fclose(lightfs);

  return num;
}

void printDirPath(MetaData data, int currentDir) {
  if (currentDir != 0) printDirPath(data, findParent(data,currentDir));
  printDirName(data, currentDir, 1);
}

void printDirName(MetaData data, int indexPosition, int cFlag) {
  // Printa o nome de um diretorio a partir de seu indice
  int clusterSize = data.clusterSize* 1000;
  // Calcula o byte ocupado pelo nome do cluster
  int position = data.clusterBegin  + (clusterSize * indexPosition);
  int num;
  char nome[30];
  FILE* lightfs = fopen("lightfs.bin", "rb");
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(nome, 30, lightfs);
  fclose(lightfs);
  if (cFlag == 1) {
    printf(ANSI_COLOR_GREEN); 
    printf("/%s",nome);
  } else printf("/%s",nome);
  printf(ANSI_COLOR_RESET); 
}

void mkdir(MetaData data, uint8_t currentDir, char name[30]) {
  // TODO cluster diretorio tera array indicando seus filhos
  // Alterar tabela FAT
  // Acha espaço livre
  uint8_t freePosition = findFreeSpace(data);
  int position = freePosition + data.indexBegin;
  
  name = strtok(name,"\n"); // Separa o input a partir do " "
//  printf("Diretorio criado na posicao %d\n",freePosition);
  FILE* lightfs = fopen("lightfs.bin", "r+b");
    fseek(lightfs,position,SEEK_SET);
    fwrite(&currentDir, sizeof(currentDir),1, lightfs);

  // Escrever no cluster flag e seu nome
    uint8_t flag = 1;
    int clusterSize = data.clusterSize* 1000;
    position = data.clusterBegin  + (clusterSize * freePosition);
    fseek(lightfs,position,SEEK_SET);
    fwrite(&flag, sizeof(flag),1, lightfs);
    fwrite(name, name[30],1, lightfs);

  // Escrever no cluster do pai o indice do filho
  // loop para achar byte vazio no cluster
    position = 240 + sizeof(flag) + data.clusterBegin  + (clusterSize * currentDir); // 240 = char[30];
    fseek(lightfs,position,SEEK_SET); // Coloca o cursor onde os enderecos dos filhos comecam
    int8_t number = 0;

    do { // Coloca o cursor no primeiro espaco vazio;
      // Lembrando que FREAD já muda a posicao do cursor:
      // le até encontrar um espaco vazio
      fread(&number, 1, 1, lightfs);
    } while (!number);

    fwrite(&freePosition, sizeof(freePosition),1, lightfs);
  fclose(lightfs);
//  printf("Cluster Metadata escrita em posicao = %d\n", position);
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
      printDirName(data, position - data.indexBegin,0);
      printf("\n");
    }
  } while (position != 255);
  fclose(lightfs);
  }

int cd(MetaData data, uint8_t currentDir, char name[30]) {
  int index = cdAux(data,currentDir,name);
  return index;
  }

int cdAux(MetaData data, uint8_t currentDir, char name[30]) {
  // Acha a posicao do diretorio desejado
  name = strtok(name,"\n"); // Separa o input a partir do " "
  int index = getDirIndex(data,name);
  if (index == -1) return currentDir;

  

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

//void renameD(MetaData data, uint8_t currentDir, char name[30]) {
 // Vai ate o cluster e altera o nome
 // Vai ate o cluster
 //
