#include <stdio.h>

//Evaluation program

int main()
{
  double x, y;
  printf("Please enter 2 value, i will evaluate them\nx: ");
  scanf("%lf", &x);
  printf("y: ");
  scanf("%lf", &y);

  if(x < y) printf("x is less than y\n");
  if(x > y) printf("x is greater than y\n");
  if(x >= y) printf("x is greater or equal to y\n");
  if(x <= y) printf("x is less than or equal to y\n");
  if(x == y) printf("x is equal to y\n");
  if(x != y) printf("x is different from y\n");

  return 0;
}
