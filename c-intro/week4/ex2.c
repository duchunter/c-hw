#include <stdio.h>

//A program that use scan set

int main()
{
  char str[50];
  printf("Stop scanning your input when 'aeiou' appear\n");
  printf("Enter a string: ");
  scanf("%[^aeiou]", str);
  printf("Your string now become: %s\n", str);

  return 0;
}
