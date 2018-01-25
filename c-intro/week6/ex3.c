#include <stdio.h>

//Enter an age and it will show you what is your age class.
//(Child, Senior Citizen or Adult)

int main() {
  int age;
  printf("Enter your age: ");
  scanf("%d", &age);

  if(0 < age && age < 18)
    printf("You belong to Child class\n");
  else if(18 <= age && age < 65)
    printf("You belong to Adult class\n");
  else if(age >= 65)
    printf("You belong to Senior Citizen class\n");
  else
    printf("Invalid input\n");

  return 0;
}
