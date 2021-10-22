#include <stdint.h>
typedef struct sMetaData {
  uint8_t indexSize;
  uint8_t clusterSize;
  uint8_t indexBegin;
  uint16_t clusterBegin;
} MetaData;

MetaData getMetaData(MetaData* data);
void getDirName(MetaData data, int indexPosition, int cFlag);
int getDirIndex(MetaData data, char name[30]);
void mkdir(MetaData data, uint8_t currentDir, char name[30]);
uint8_t findFreeSpace(MetaData data);
void dir(MetaData data, uint8_t currentDir);
int cd(MetaData data, uint8_t currentDir, char name[30]);
