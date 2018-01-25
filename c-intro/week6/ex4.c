#include <stdio.h>

//Ticket printer

int main()
{
  int age;
  float price = 1;
  char movie[50], yesno;
  printf("Please enter:\n");
  printf("- Weekend ? (y/n/Y/N): ");
  scanf("%c", &yesno);
  printf("- Age: ");
  scanf("%d", &age);
  printf("- Movie: ");
  scanf("%s", movie);

  printf("\nBKCine\n-----------------------------\n");
  printf("- Movie: %s\n", movie);

  if(0 < age && age < 18){
    printf("- Class: Child\n");
    price *= 0.5;
  }
  else if(18 <= age && age < 65){
    printf("- Class: Adult\n");
  }
  else if(age >= 65){
    printf("- Class: Senior Citizen\n");
    price *= 0.7;
  }
  else{
    printf("- Class: Invalid\n");
    price = 0;
  }

  switch (yesno) {
    case 'y': case 'Y':
      price *= 10;
      printf("- Date: Weekend\n");
      break;
    case 'n': case 'N':
      price *= 7;
      printf("- Date: Weekdays\n");
      break;
    default:
      printf("- Date: Invalid\n");
      price = 0;
  }

  printf("- Price: $%.1f\n\n", price == 0 ? 9999999.9 : price);

  return 0;
}
