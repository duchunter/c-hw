#include <stdio.h>

//BK library™ DVD shop online banking system

void main()
{
  //Intro
  printf("\n\tBK library™ DVD shop online banking system\n\n");
  printf("Rental rates:\n");
  printf("\t\tOvernight\t$7.00\n");
  printf("\t\tThree-day\t$5.00\n");
  printf("\t\tWeekly\t\t$3.00\n\n");
  printf("Please enter your order below:\n\n");

  char day[20];
  int overnight, threeday, weekly;
  float total;
  //Wait for input
  printf("+ Day started:\t\t\t");
  scanf("%s", day);
  printf("+ Number of overnight rental:\t");
  scanf("%d", &overnight);
  printf("+ Number of three-day rental:\t");
  scanf("%d", &threeday);
  printf("+ Number of weekly rental:\t");
  scanf("%d", &weekly);
  total = overnight * 7.00 + threeday * 5.00 + weekly * 3.00;
  printf("\nTotal cost: $%.2f\n\n", total);
}
