#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int getCommand(char* str);
void clearScreen();
void asciiArt();

int main() {

  clearScreen();
  asciiArt();
  int stop = 0;
  char input[80];
  char *ptr;

  do {
    // substituir pelo diretorio atual
    printf(ANSI_COLOR_GREEN); //Set the text to the color red
    printf("/root $ ");
    printf(ANSI_COLOR_RESET); 

    fgets(input,80, stdin);
    ptr = strtok(input," "); // Pega somente a primeira palavra digitada

    /*
    ptr = strtok(NULL," "); // 
    printf("Segunda: %s\n",ptr);
    */

    switch(getCommand(ptr)) {
      case 9:
        clearScreen();
        break;

      case 10:
        stop = 1;
        break;

      case 2:
        break;

      default:
        printf(ANSI_COLOR_RED); //Set the text to the color red
        printf("unknown command ");
        printf(ANSI_COLOR_RESET); 
        printf("%s", ptr);

        break;

    }
  }  while (!stop);
  return 0;
}

void asciiArt() {
  printf("  _     ___ ____ _   _ _____   _____ ____  \n");
  printf(" | |   |_ _/ ___| | | |_   _| |  ___/ ___| \n");
  printf(" | |    | | |  _| |_| | | |   | |_  \___ \\\n);
  printf(" | |    | | |  _| |_| | | |   | |_  \\____ \\ \n");
  printf(" | |___ | | |_| |  _  | | |   |  _| ___) |\n");
  printf(" |_____|___\\____|_| |_| |_|   |_|   |____/");
}

void clearScreen() {
  for(int i=0;i<50;i++)
    printf("\n");
}
int getCommand(char* str) {
  // Recebe o comando em str e retorna int para o swtich/case
  if (!strcmp(str, "cd\n")) return 1;
  if (!strcmp(str, "dir\n")) return 2;
  if (!strcmp(str, "rm\n")) return 3;
  if (!strcmp(str, "mkdir\n")) return 4;
  if (!strcmp(str, "mkfile\n")) return 5;
  if (!strcmp(str, "edit\n")) return 6;
  if (!strcmp(str, "move\n")) return 7;
  if (!strcmp(str, "rename\n")) return 8;

  if (!strcmp(str, "clear\n")) return 9;
  if (!strcmp(str, "exit\n")) return 10;
  return 0;
}
