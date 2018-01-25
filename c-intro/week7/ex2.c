#include <stdio.h>

//All odd number > 27 from 1 to 100

int main() {
  int x;
  printf("All odd number > 27 from 1 to 100:\n");
  for(x = 1; x < 100; x += 2){
    if(x > 27) printf("%d ", x);
  }
  printf("\n");

  return 0;
}
