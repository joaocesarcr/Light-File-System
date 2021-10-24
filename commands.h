#include <stdint.h>
typedef struct sMetaData {
  uint8_t indexSize; uint8_t clusterSize;
  uint8_t indexBegin;
  uint16_t clusterBegin;
} MetaData;

MetaData getMetaData(MetaData* data);
void printDirName(MetaData data, int indexPosition, int cFlag);

uint8_t findFreeSpace(MetaData data);
char* getDirName(MetaData data, int indexPosition);
int getDirIndex(MetaData data, char name[30]);
void mkdir(MetaData data, uint8_t currentDir, char name[30]);
void dir(MetaData data, uint8_t currentDir);
int cd(MetaData data, uint8_t currentDir, char name[30]);
int cdAux(MetaData data, uint8_t currentDir, char name[30]);

void printDirPath(MetaData data, int currentDir);
int findParent(MetaData data, int dir);
void remover(MetaData data, uint8_t currentDir, char name[30]);
void mkfile(MetaData data, uint8_t currentDir, char name[30]);
void renameD(MetaData data, uint8_t currentDir, char name[30]);
int gDI(MetaData data, char name[30]);
int movBDiv(MetaData data, uint8_t currentDir, char name[30]);
void movebarra (MetaData data, char *primeiro, char *segundo);
void edit(MetaData data, char* name);
