#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
  begin(); // Clear screen & ascii logo
  int stop = 0;
  char input[80];
  char *ptr;

  // Get filesystem metadata
  MetaData data = getMetaData(&data);

  int currentDir = 0;
  // Main loop
  do {
    getDirName(data, currentDir,1); 
    fgets(input,80, stdin);
    ptr = strtok(input," "); // Separa o input a partir do " "

    switch(getCommand(ptr)) {
      case 1:
        ptr = strtok(NULL," "); // 
        currentDir = cd(data,currentDir,ptr);
        break;

      case 2:
        dir(data,currentDir);
        break;

      case 3:
        // rm
        break;

      case 4:
        ptr = strtok(NULL," "); // 
        mkdir(data,currentDir,ptr);
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
