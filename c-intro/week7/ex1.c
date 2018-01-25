#include <stdio.h>

//Draw a triagle

int main() {
  int x, y;
  printf("A pretty triagle:\n");
  for(x = 1; x <= 10; x++){
    for(y = 0; y < x; y++) printf("*");
    printf("\n");
  }

  return 0;
}
