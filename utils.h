#include <stdint.h>
typedef struct sCluster {
  char dirFlag;
  char name[30];
  int  size;
  int nextCluster;
  char* files;
} Cluster;

typedef struct sMetaData {
  uint8_t indexSize;
  uint8_t clusterSize;
  uint8_t indexBegin;
  uint16_t clusterBegin;
} MetaData;

void begin();
struct sCluster getCluster(int index);
void mkdir(char* nome);
void writeCluster(MetaData mData, Cluster cInfo, int indexPosition);
struct sCluster createCluster(uint8_t dirFlag, char name[30], int size, int nextCluster, char* files);
void clearScreen(int a);
void asciiArt();
int getCommand(char* str);
void ascii();
void printCurrentDirectory(int index); 
MetaData getMetaData(MetaData* data);