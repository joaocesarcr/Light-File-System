#include <stdio.h>
#include <string.h>

// Bit manipulation baseado em
// https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c

int getCommand(char* str);

int main() {
  int stop = 0;
  char input[80];
  do {
    fgets(input,80, stdin);
    switch(getCommand(input)) {
      case 0:
        printf("Unknown command\n");
        break;

      case 1:
        stop = 1;
        break;

      case 2:
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
