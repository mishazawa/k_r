#include <stdio.h>
#include <string.h>

int main () {
  char teststr[] = "asd "
    "dsaaasd "
    "asd "
    "aaa aaa";
  printf("%d\n", strlen(teststr));
  return 0;
}
