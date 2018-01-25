#include <stdio.h>

//A program that display numbers

int main()
{
  int num1;
  double num2;
  //Part a)
  printf("Part a)\n   Please enter:\n");
  printf("\tA normal integer: ");
  scanf("%d", &num1);
  printf("\tA normal double: ");
  scanf("%lf",&num2);
  printf("You entered:\n\tInterger: %d\n\tDouble: %f\n", num1, num2);
  //Part b)
  printf("Part b)\n   Please enter:\n");
  printf("\tA hexadecimal integer: ");
  scanf("%X", &num1);
  printf("\tA scientific format floating point: ");
  scanf("%lG",&num2);
  printf("You entered:\n\tHexadecima: %X --> %d (normal)\n", num1, num1);
  printf("\tScientific: %G --> %f (normal)\n", num2, num2);

  return 0;
}
