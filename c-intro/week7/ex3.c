#include <stdio.h>
#include <math.h>

//List of all prime numbers < 100

int main() {
  int x, y;
  printf("All prime numbers < 100:\n");
  for(x = 2; x < 100; x++){
    for(y = 2; y <= sqrt(x); y++){
      if(!(x % y)) break;
    }
    if(y > sqrt(x)) printf("%d ", x);
  }
  printf("\n");

  return 0;
}
