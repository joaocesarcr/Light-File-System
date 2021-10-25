#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void art();
void asciiArt() {
  printf(ANSI_COLOR_GREEN); 
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
  printf(ANSI_COLOR_RESET); 
	art();
  }

void art() {

printf("                                            ");
printf("          ___\n");
  printf("                                            ");
printf("       ___)__|_\n");
  printf("                                            ");
printf("  .-*'          '*-,\n");
  printf("                                            ");
printf(" /      /|   |\\     \\n");
  printf("                                            ");
printf(";      /_|   |_\\     ;\n");
printf(";   |\\           /|  ;\n");
printf(";   | ''--...--'' |  ;\n");
printf(" \\  ''---.....--''  /\n");
printf("  ''*-.,_______,.-*'   \n");
}
void maisArt() {
printf("⊂_ヽ\n");
printf("　 ＼＼\n");
printf("　　 ＼( ͡° ͜ʖ ͡°)\n");
printf("　　　 >　⌒ヽ\n");
printf("　　　/ 　 へ＼\n");
printf("　　 /　　/　＼＼\n");
printf("　　 ﾚ　ノ　　 ヽ_つ\n");
printf("　　/　/\n");
printf("　 /　/|\n");
printf("　(　(ヽ\n");
printf("　|　|、＼\n");
printf("　| 丿 ＼ ⌒)\n");
printf("　| |　　) /\n");
printf("ノ )　　Lﾉ\n");
printf("(_／\n");
}
int getCommand(char* str) {
  // Recebe o comando em str e retorna int para o swtich/case
  if (!strcmp(str, "cd")) return 1; if (!strcmp(str, "cd\n")) return 12;
  if (!strcmp(str, "dir\n")) return 2;
  if (!strcmp(str, "rm")) return 3;
  if (!strcmp(str, "mkdir")) return 4;
  if (!strcmp(str, "mkfile")) return 5;
  if (!strcmp(str, "edit")) return 6;
  if (!strcmp(str, "move")) return 7;
  if (!strcmp(str, "rename")) return 8;

  if (!strcmp(str, "clear\n")) return 9;
  if (!strcmp(str, "exit\n")) return 10;
  if (!strcmp(str, "\n")) return 11;
  if (!strcmp(str, "move")) return 15;
  return 0;
  }
void clearScreen(int a) {
  for(int i=0;i<a;i++)
  printf("\n");
  }
void begin() {
  clearScreen(10);
  asciiArt();
  clearScreen(25);
  }

