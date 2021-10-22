#include <stdint.h>
typedef struct sCluster {
  uint8_t dirFlag;
  char name[30];
  int nextCluster;
  int  size;
  char* files;
} Cluster;


void begin();
struct sCluster getCluster(int index);
struct sCluster createCluster(uint8_t dirFlag, char name[30], int size, int nextCluster, char* files);
void clearScreen(int a);
void asciiArt();
int getCommand(char* str);
void ascii();
void printCurrentDirectory(int index); 

