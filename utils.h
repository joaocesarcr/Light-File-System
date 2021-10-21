typedef struct sCluster {
  char dirFlag;
  char name[30];
  int  size;
  int nextCluster;
  char* files;
} Cluster;

typedef struct sMetaData {
  uint8_t metaIndexSize;
  uint8_t metaClusterSize;
  uint8_t metaIndexBegin;
  uint16_t metaClusterBegin;
} MetaData;

struct sCluster getCluster(int index);
void mkdir(char* nome);
void writeCluster(MetaData mData, Cluster cInfo, int indexPosition);
struct sCluster createCluster(char dirFlag, char name[30], int size, int nextCluster, char* files);
void clearScreen(int a);
void asciiArt();
int getCommand(char* str);
void ascii();
