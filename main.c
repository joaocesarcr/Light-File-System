#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"
#include "commands.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//
// Arvore vai facilitar a implementacao e deixar o codigo mais legivel/elegante
// Inferno implementar arvore

int main() {
  begin(); // Clear screen & ascii logo
  int stop = 0;
  char input[80];

  // Get filesystem metadata
  MetaData data = getMetaData(&data);

  int currentDir = 0;

  char* token;
  char* rest;
  char* ptr;
  // Main loop
  do {
    printDirPath(data,currentDir);
    printf(" $ ");
    fgets(input,80, stdin);
    rest = input;
    token = strtok_r(rest, " ", &rest);

    switch(getCommand(input)) {
      case 1:
        if (!strcmp(rest,"..\n")) {
          currentDir = findParent(data,currentDir);
        }
        else while ((token = strtok_r(rest, "/", &rest))) 
          currentDir = cd(data,currentDir,token);
        break;

      case 2:
        dir(data,currentDir);
        break;

      case 3:
        // rm
        break;

      case 4:
        ptr = strtok(NULL," "); // 
        mkdir(data,currentDir,rest);
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

      case 12:
        // cd
        currentDir = 0;
        break;

      default:
        printf(ANSI_COLOR_RED); //Set the text to the color red
        printf("unknown command ");
        printf(ANSI_COLOR_RESET); 
        printf("%s", input);

        break;
    }
  }  while (!stop);
  return 0;
}
