#include <stdio.h>

//Calculation program

int main()
{
  float a, b, result1, result2;

  printf("Enter a: ");
  scanf("%f", &a);
  printf("Enter b: ");
  scanf("%f", &b);

  if((a == b) || ((a * a - b * b - a * b) == 0)) {
    printf("Division by 0\n");
  }
  else {
    result1 = ((a + b) * (a + b) * (a + b)) / ((a * a - b * b) - a * b);
    result2 = (a - b) * (a + b) / (a * a - b * b) / (a * a + b * b);

    printf("Result 1: %f\n", result1);
    printf("Result 2: %f\n", result2);
  }

  return 0;
}
