#include <stdio.h>

//Require input and display name and studentID

int main()
{
  char id[10], name[30];
  printf("Enter your student's ID (HUSTxxx): ");
  scanf("%[HUST0123456789]s", id);
  printf("Enter your name: ");
  scanf("%s", name);
  printf("Your name is: %s\nYour student's ID: %s\n", name, id);

  return 0;
}
