#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
int main() {
  char* str = "cd p1/p2/p3/p4";
  char* rest = str;
  char* token;
  while ((token = strtok_r(rest, " ", &rest)))
           printf("%s\n", token);

  return 0;
}
*/
int main() {
 char str[] = "cd p1/p2/p3/p4 a1/a2/a3";
 //char str[] = "cd p1";
	char* token;
	char* rest = str;

  printf("\n");

  printf("PRIMEIRO STRTOP\n");
	token = strtok_r(rest, " ", &rest);
  printf("str = %s\n", str);
  printf("token = %s\n", token);
  printf("rest =%s\n", rest);

  printf("Segundo STRTOP\n");
	token = strtok_r(rest, " ", &rest);
  printf("str = %s\n", str);
  printf("token = %s\n", token);
  printf("rest =%s\n", rest);

/*
  printf("token = %s\n", token);
  printf("\n");
	while ((token = strtok_r(rest, "/", &rest))) {
    printf("token = %s\n", token);
    printf("rest =%s\n", rest);
    printf("str = %s\n", str);
    printf("\n");
  }
*/

	return (0);
}
