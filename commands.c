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
	if (num) {
		if (cFlag == 1) {
			printf(ANSI_COLOR_GREEN); 
			printf("/%s",nome);
		} else printf("/%s",nome);
		printf(ANSI_COLOR_RESET); 
	} else printf("%s",nome);
}

void mkdir(MetaData data, uint8_t currentDir, char name[30]) {
  // TODO cluster diretorio tera array indicando seus filhos
  // Alterar tabela FAT
  // Acha espaço livre
  uint8_t freePosition = findFreeSpace(data);
  int position = freePosition + data.indexBegin;
	name = strtok(name,"\n"); // Separa o input a partir do " "

	uint8_t empty = 255;

	int index = gDI(data,name);
	if ((index != -1) && (returnFatValue(data,index)!= 255)){
		// Se ja existiu E nao foi apagado NAO USA O NOME
		 printf ("MKDIR Este nome ja foi utilizado\n"); 
	}	else { 
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
			fwrite(name, 240,1, lightfs);

			fclose(lightfs);
	//  printf("Cluster Metadata escrita em posicao = %d\n", position);
		}
  }

void dir(MetaData data, uint8_t currentDir) {
  // Percorre a fat inteira achando referencias ao diretorio atual
  // Se diretorio atual == diretorio apontado na fat, imprime
	int emptyFlag = 0;
  int position = data.indexBegin;
  uint8_t num = 0;
  FILE* lightfs = fopen("lightfs.bin", "r+b");
  do {
    position++;
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == currentDir) {
      printDirName(data, position - data.indexBegin,0);
			emptyFlag++;
      printf("\n");
    }
  } while (position != 255);
	if (!emptyFlag) printf("Empty\n");
  fclose(lightfs);
  }

int cd(MetaData data, uint8_t currentDir, char name[30]) {
  return cdAux(data,currentDir,name);
}

int cdAux(MetaData data, uint8_t currentDir, char name[30]) {
	uint8_t num;

  name = strtok(name,"\n"); // Separa o input a partir do " "
  int index = getDirIndex(data,name);
  if (index == -1) return currentDir;

	// Verifica se é arquivo ou dir
	int clusterSize = data.clusterSize * 1000;
	int position = data.clusterBegin  + (clusterSize * index);
  FILE* lightfs = fopen("lightfs.bin", "r+b");
		fseek(lightfs,position,SEEK_SET);
		fread(&num, 8, 1, lightfs);
	if (!num) {
		printf(ANSI_COLOR_RED); 
		printf("Can't CD into file\n");
		printf(ANSI_COLOR_RESET); 
		return currentDir;	
	}

  // Verifica se o diretorio desejado tem como pai o diretorio atual
    fseek(lightfs,index + data.indexBegin,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == currentDir) {
      return index;
    }  

  fclose(lightfs);
  printf("Error\n");
  return currentDir;
  }


int searchSon(MetaData data, uint8_t father){
  FILE* lightfs = fopen("lightfs.bin","rb");
  int pos;
  uint8_t num = 0;
  for(int i = 1; i < 255; i++){
    pos = data.indexBegin + i;
    fseek(lightfs,pos,SEEK_SET);
    fread(&num,1,1,lightfs);
    if(num == father){
      return -1;
    }
  }
  return 1;
}

void remover(MetaData data, uint8_t currentDir, char name[30]){
  name = strtok(name,"\n");
  int pos = getDirIndex(data, name);
  if(pos == -1){
    return;
  }
  if(pos == currentDir){
		printf(ANSI_COLOR_RED); 
    printf("Can't delete current directory\n");
		printf(ANSI_COLOR_RESET); 

    return;
  }
  int check = searchSon(data, pos);
  if(check == -1){
		printf(ANSI_COLOR_RED); 
    printf("Can't delete a directory that is not empty\n");
		printf(ANSI_COLOR_RESET); 

    return;
  }
  int position = pos + data.indexBegin; 
  uint8_t  final = 255; 
  FILE* lightfs = fopen("lightfs.bin", "r+b");
    fseek(lightfs,position,SEEK_SET);
    fwrite(&final, sizeof(currentDir),1, lightfs);
  fclose(lightfs);
}

void mkfile(MetaData data, uint8_t currentDir, char name[30]) {
  uint8_t freePosition = findFreeSpace(data);
  int position = freePosition + data.indexBegin;
  name = strtok(name,"\n");

	int index = gDI(data,name);
 	if ((index != -1) && (returnFatValue(data,index)!= 255)){
		// Se ja existiu E nao foi apagado NAO USA O NOME
		 printf ("Este nome ja foi utilizado\n"); 
	}	else { 

		//Escreve na fat quem e o pai
		FILE* lightfs = fopen("lightfs.bin", "r+b");
			fseek(lightfs,position,SEEK_SET);
			fwrite(&currentDir, sizeof(currentDir),1, lightfs);

			// Escrever no cluster flag e seu nome
			uint8_t flag = 0;
			int clusterSize = data.clusterSize* 1000;
			position = data.clusterBegin  + (clusterSize * freePosition);
			fseek(lightfs,position,SEEK_SET);
			fwrite(&flag, sizeof(flag),1, lightfs);
			fwrite(name, 30*8,1, lightfs);
			fclose(lightfs);
	} 
}

int movBDiv(MetaData data, uint8_t currentDir, char name[30]) {
	uint8_t num;

  name = strtok(name,"\n"); // Separa o input a partir do " "
  int index = gDI(data,name);
	// Verifica se é arquivo ou dir
	int clusterSize = data.clusterSize * 1000;
	int position = data.clusterBegin  + (clusterSize * index);
  FILE* lightfs = fopen("lightfs.bin", "r+b");
		fseek(lightfs,position,SEEK_SET);
		fread(&num, 8, 1, lightfs);
	if (!num) {
		printf(ANSI_COLOR_RED); 
		printf("Error\n");
		printf(ANSI_COLOR_RESET); 
		return currentDir;	
	}

  // Acha a posicao do diretorio desejado
  if (index == -1) return currentDir;

  // Verifica se o diretorio desejado tem como pai o diretorio atual
    fseek(lightfs,index + data.indexBegin,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    if (num == currentDir) {
      return index;
    }  
  fclose(lightfs);
  return currentDir;
  }

int gDI(MetaData data, char name[30]) { // get dir Index
  // Recebe um nome e retorna seu indice na tabela
  int clusterSize = data.clusterSize* 1000;
  int position = data.clusterBegin + clusterSize;
  int num;
  int index = 0;
  char indexName[30];
  FILE* lightfs = fopen("lightfs.bin", "r+b");
//  printf("Index name procurado = %s\n",name); 
	// Olha de cluster em cluster se o nome é igual
  do {
    index++;
    position = data.clusterBegin  + (clusterSize * index);
    fseek(lightfs,position,SEEK_SET);
    fread(&num, 1, 1, lightfs);
    fgets(indexName, 30, lightfs);
    if (!strcmp(indexName,name)) {
      fclose(lightfs);
      return index;
    }
  } while (index != 255);
  fclose(lightfs);
  return -1;
  }

void renameD(MetaData data, uint8_t currentDir, char name[30]){
	char* token = strtok_r(name, " ", &name);
	int clusterSize = data.clusterSize * 1000;
	//token = a.txt
	// name = b.txt
//	printf("name = %s\n",name);
//	printf("token = %s\n",token);
	int position = getDirIndex(data,token);
	
	int index = gDI(data,name);
	if ((index != -1) && (returnFatValue(data,index)!= 255)){
		// Se ja existiu E nao foi apagado NAO USA O NOME
		 printf ("Este nome ja foi utilizado\n"); 
	}	else { 

		position = data.clusterBegin  + (clusterSize * position);
		FILE* lightfs = fopen("lightfs.bin", "r+b");
			fseek(lightfs,position+1,SEEK_SET);
			fwrite(name, 240,1, lightfs);
		fclose(lightfs);
	} 
}

void movebarra (MetaData data, char *primeiro, char *segundo) {
    //char *nameOrigem, *nameDestino, *rest;
    int clusterSize = data.clusterSize* 1000;
    int position = 0;
    uint8_t indexOrigem, indexDestino;
    char *atual;

    //nameOrigem = strtok_r(name," ",&nameDestino);
    //nameDestino = strtok(nameDestino,"\n");

    indexOrigem = getDirIndex(data, primeiro);
    indexDestino = getDirIndex(data, segundo);

    position = data.indexBegin + indexOrigem;
    FILE* lightfs = fopen("lightfs.bin", "r+b");
    fseek(lightfs,position,SEEK_SET);
    fwrite(&indexDestino,sizeof(indexDestino),1,lightfs);
    fclose(lightfs);
}

void edit(MetaData data, char* name)
{
  char *parte = strtok_r(name, " ", &name);
  int pos = getDirIndex(data, parte);  
  int position = data.clusterBegin + (pos*data.clusterSize*1000);
  uint8_t eof = 255;
  FILE* lightfs = fopen("lightfs.bin", "r+b");
  fseek(lightfs, position+241,SEEK_SET);
  fwrite(name, sizeof(name) * 10, 1, lightfs);
  fwrite(&eof, sizeof(eof), 1, lightfs);
  fclose(lightfs);
}

int returnFatValue(MetaData data, int index) {
	// Pega indice fat e retorna se é 255
 int position, valorIndex;
 position = data.indexBegin + index;
 FILE* lightfs = fopen("lightfs.bin", "r+b");
	 fseek(lightfs,position,SEEK_SET);
	 fread(&valorIndex, 1, 1, lightfs);
 fclose(lightfs);
 return valorIndex;
}

