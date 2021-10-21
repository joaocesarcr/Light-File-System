typedef struct sCluster {
  char dirFlag
  char name[30];
  int  size;
  int nextCluster;
} Cluster;
