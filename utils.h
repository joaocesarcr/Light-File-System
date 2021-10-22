#include <stdint.h>
typedef struct sCluster {
  uint8_t dirFlag;
  char name[30];
  int nextCluster;
  int  size;
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
void writeCluster(MetaData mData, Cluster cInfo, int indexPosition);
struct sCluster createCluster(uint8_t dirFlag, char name[30], int size, int nextCluster, char* files);
void clearScreen(int a);
void asciiArt();
int getCommand(char* str);
void ascii();
void printCurrentDirectory(int index); 
MetaData getMetaData(MetaData* data);

void getDirName(MetaData data, int indexPosition, int cFlag);
int getDirIndex(MetaData data, char name[30]);
void mkdir(MetaData data, uint8_t currentDir, char name[30]);
uint8_t findFreeSpace(MetaData data);
void dir(MetaData data, uint8_t currentDir);
int cd(MetaData data, uint8_t currentDir, char name[30]);
