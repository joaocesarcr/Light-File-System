#include "utils.h"

struct sCluster getCluster(int index) {
  return NULL;
}

void mkdir(char* nome) {
  
}

void writeCluster(Metadata mData, Cluster cInfo, int indexPosition) {
  int position = data.clusterBegin + (mData.clusterSize * 1000 * indexPosition);
 	FILE* lightfs = fopen("lightfs.bin", "wb");
    fseek(lightfs,position,SEEK_SET),
    fwrite(&c.Info, sizeof(cInfo),1, lightfs);
  fclose(lightfs);
}

struct sCluster createCluster(char dirFlag, char name[30], int size, int nextCluster, char* files) {
  Cluster newCluster;
  newCluster.dirFlag = dirFlag;
  newCluster.name = name;
  newCluster.size = size;
  newCluster.nextCluster = nextCLuster;
  newCluster.files  = flies;

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

void ascii() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
}

