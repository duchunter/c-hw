#include <stdio.h>

//a program that finds and displays the alphabetically first letter
//in a sequence of three characters

int main()
{
  char a, b, c, winner;
  printf("Enter 3 random letters (all uppercase or lowercase): ");
  scanf("%c%c%c", &a, &b, &c);
  if(a > b)
    winner = c > b ? b : c;
  else
    winner = c > a ? a : c;
  printf("The alphabetically first letter is: %c\n", winner);

  return 0;
}
