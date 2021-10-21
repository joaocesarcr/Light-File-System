void mkdir(char* nome) {
  
}

void writeCluster(Metadata mData, Cluster cInfo, int indexPosition) {
  int position = data.clusterBegin + (mData.clusterSize * 1000 * indexPosition);

 	FILE* lightfs = fopen("lightfs.bin", "wb");
    fseek(lightfs,position,SEEK_SET),
    fwrite(&c.Info, sizeof(cInfo),1, lightfs);
  fclose(lightfs);
}

struct sCluster createCluster(char dirFlag, char name[30], int size, int nextCluster, char* files);
struct sCluster createCluster(char dirFlag, char name[30], int size, int nextCluster, char* files) {
  Cluster newCluster;
  newCluster.dirFlag = dirFlag;
  newCluster.name = name;
  newCluster.size = size;
  newCluster.nextCluster = nextCLuster;
  newCluster.files  = flies;

}
typedef struct sCluster {
  char dirFlag
  char name[30];
  int  size;
  int nextCluster;
  char* files;
} Cluster;
