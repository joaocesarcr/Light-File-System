#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int getCommand(char* str);
void clearScreen(int a);
void asciiArt();

int main() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
  int stop = 0;
  char input[80];
  char *ptr;

  do {
    printf(ANSI_COLOR_GREEN); //Set the text to the color red
    // substituir pelo diretorio atual
    printf("/root $ ");
    printf(ANSI_COLOR_RESET); 

    fgets(input,80, stdin);
    ptr = strtok(input," "); // Separa o input a partir do " "

    /*
    ptr = strtok(NULL," "); // 
    printf("Segunda: %s\n",ptr);
    */

    switch(getCommand(ptr)) {
      case 1:
        // cd
        break;

      case 2:
        // dir
        break;

      case 3:
        // rm
        break;

      case 4:
        //mkdir
        break;

      case 5:
        //mkfile
        break;

      case 6:
        //edit
        break;

      case 7:
        //move
        break;

      case 8:
        // rename
        break;

      case 9:
        clearScreen(40);
        break;

      case 10:
        stop = 1;
        break;

      case 11:
        // repete o loop
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

void clearScreen(int a) {
  for(int i=0;i<a;i++)
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
  if (!strcmp(str, "\n")) return 11;
  return 0;
}
void asciiArt() {
  printf("                                            ");
  printf("  _     ___ ____ _   _ _____   _____ ____  \n");
  printf("                                            ");
  printf(" | |   |_ _/ ___| | | |_   _| |  ___/ ___| \n");
  printf("                                            ");
  printf(" | |    | | |  _| |_| | | |   | |_  \\____\\ \n");
  printf("                                            ");
  printf(" | |___ | | |_| |  _  | | |   |  _|  __) |\n");
  printf("                                            ");
  printf(" |_____|___\\____|_| |_| |_|   |_|   |____/\n");
}
