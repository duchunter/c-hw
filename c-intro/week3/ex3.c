#include <stdio.h>

/*A program that ask for name to greet*/

void main()
{
  char name[20]; //Maximum 19 characters
  printf("Hello, i'm Cortana, what's your name?\nEnter your name (20, no spacing): ");
  scanf("%s", name);
  printf("Nice to meet you, %s\n", name);
}
