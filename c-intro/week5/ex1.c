#include <stdio.h>

//Convert km to miles

int main()
{
  double km, miles;
  printf("Enter a distance in km:\t");
  scanf("%lf", &km);

  if(km < 0) printf("Please enter a positive value\n");
  else {
    miles = km * 0.621371;
    printf("Distance in miles is:\t%.2lf\n", miles);
  }

  return 0;
}
