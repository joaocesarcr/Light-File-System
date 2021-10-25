#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"
#include "commands.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
  begin(); // Clear screen & ascii logo
  int stop = 0;
  char input[80];

  // Get filesystem metadata
  MetaData data = getMetaData(&data);

  int currentDir = 0, cDir = 0;;

	char* segundo,* tokenAtual2;
  char* token;
  char* rest;
  char* ptr;
	char* tokenAtual;
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
        else while ((token = strtok_r(rest, "/", &rest)))  {
          currentDir = cd(data,currentDir,token);
				}
        break;

      case 2:
        dir(data,currentDir);
        break;

      case 3:
        // rm removeDdata,currentDir,rest);
					remover(data,currentDir,rest);
        break;

      case 4:
//        ptr = strtok(NULL," "); // 
        mkdir(data,currentDir,rest);
        break;

      case 5:
				mkfile(data,currentDir,rest);
        break;

      case 6:
        //edit
				cDir = currentDir;
				while ((token = strtok_r(rest, "/", &rest)))  {
          currentDir = movBDiv(data,currentDir,token);
					tokenAtual = token;
				}
/*
				printf("rest = %s\n",rest);
				printf("token = %s\n",token);
				printf("input = %s\n",input);
				printf("tokenAtual = %s\n",tokenAtual);
				currentDir = cDir;
*/
				edit(data,tokenAtual);
        break;

      case 7:
				strtok_r(rest," ",&segundo);
        printf("token: %s\n",segundo); //token é o segundo
        printf("rest: %s\n",rest); //rest é o primeiro

        printf("segundo: %s",segundo);

				tokenAtual = rest;
        while ((token = strtok_r(rest, "/",&rest)))
        {
          currentDir = movBDiv(data, currentDir, token);
          tokenAtual = rest;
        }

        printf("tokenAtual: %s\n",tokenAtual); //token é o segundo
        
				tokenAtual2 = segundo;
        while ((token = strtok_r(segundo, "/",&segundo)))
        {
          currentDir = movBDiv(data, currentDir, token);
          tokenAtual2 = segundo;
        }
        printf("tokenAtual2: %s\n",tokenAtual2); //token é o segundo

        movebarra(data,tokenAtual,tokenAtual2);

        currentDir = cDir;
				break;

      case 8:
        // rename
				cDir = currentDir;
				while ((token = strtok_r(rest, "/", &rest)))  {
          currentDir = movBDiv(data,currentDir,token);
					tokenAtual = token;
				}
				renameD(data,currentDir,tokenAtual);
				currentDir = cDir;
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
