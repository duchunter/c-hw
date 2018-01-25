#include <stdio.h>

//Calculate n!

int main() {
  int n;
  double total = 1;
  printf("Enter a positive integer: ");
  scanf("%d", &n);
  if(n < 0)
    printf("Must be positive number\n");
  else if(n > 170)
    printf("Too big!!! Please stop!!!\n");
  else {
    for(int x = n; x > 1; x--) total *= x;
    printf("n! = %.0lf\n", total);
  }

  return 0;
}
