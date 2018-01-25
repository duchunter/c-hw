#include <stdio.h>

//A program that calculate wages based on total work hours
//Will not work correctly without if else operations

int main()
{
  unsigned int total, regular, overtime, wages;
  printf("Enter total work hours: ");
  scanf("%u", &total);
  overtime = total - 40;
  regular = total - overtime;
  wages = regular * 25000 + overtime * 40000;
  printf("Regular (25000/h): %uH\nOvertime (40000/h): %uH", regular, overtime);
  printf("\nTotal wages: %u VND\n", wages);

  return 0;
}
