#include <stdio.h>
#include <string.h>

int getCommand(char* str);

int main() {
  int stop = 0;
  char input[80];
  char *ptr;
  do {
    fgets(input,80, stdin);
    ptr = strtok(input," "); // Pega somente a primeira palavra digitada

    /*
    ptr = strtok(NULL," "); // 
    printf("Segunda: %s\n",ptr);
    */

    switch(getCommand(ptr)) {
      case 1:
        stop = 1;
        break;

      case 2:
        break;

      default:
        printf("Unknown command\n");
        break;

    }
  }  while (!stop);
  return 0;
}

int getCommand(char* str) {
  // Recebe o comando em str e retorna int para o swtich/case
  if (!strcmp(str, "exit\n")) return 1;
  if (!strcmp(str, "cd\n")) return 2;
  if (!strcmp(str, "dir\n")) return 3;
  if (!strcmp(str, "rm\n")) return 4;
  if (!strcmp(str, "mkdir\n")) return 5;
  if (!strcmp(str, "mkfile\n")) return 6;
  if (!strcmp(str, "edit\n")) return 7;
  if (!strcmp(str, "move\n")) return 9;
  if (!strcmp(str, "rename\n")) return 10;

  return 0;
}
