typedef struct sDir {
  char name[20];
  struct sLinkedList* childrenList;
} node;

typedef struct sLinkedList {
  struct sDir* Node;
  struct sDir* Next;
} lList;

