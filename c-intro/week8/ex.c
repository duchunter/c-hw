#include <stdio.h>
#include <stdlib.h>

//A menu or ex5

int main() {
  int choice;
  char c; //Just to handle getchar()
  double result, count; //for ex1 2 and 3
  do {
    system("clear");
    printf("\tHOMEWORK 7:\n\n1. Caculate n!\n2. Average grade\n");
    printf("3. Replace multiple blank\n4. Replace tab and \\\n5. Exit\n");
    printf("\nEnter your choice (1-5): ");
    if(!scanf("%d", &choice)) choice = -1; //If input is not number
    switch (choice) {

      //EX1 CALCULATE n!

      case 1:
        system("clear");
        printf("Caculate n!\n");
        int n;
        result = count = 1;
        printf("Enter n (positive int): ");
        //No letter or negative number
        while(!scanf("%d", &n) || n < 0) {
          //Clear the input
          while((c = getchar()) != '\n' && c != EOF);
          printf("Invalid input, enter again: ");
        }
        //Calculate
        while(count <= n) {
          result *= count;
          count++;
        }
        printf("n! = %.0f\n", result);
        printf("Enter any character to return to menu: ");
        //Clear the input
        while((c = getchar()) != '\n' && c != EOF);
        //Wait for user to enter anything
        getchar();
        break;

      //EX2 CALCULATE AVERAGE GRADE

      case 2:
        system("clear");
        result = count = 0;
        int num;
        printf("Enter a negative value to stop\n");
        while(1) {
          printf("Enter a value: ");
          //If user not input a number
          while(!scanf("%d", &num)) {
            //Clear the input
            while((c = getchar()) != '\n' && c != EOF);
            printf("Must be a number: ");
          }
          //Break if negative
          if(num < 0) break;
          result += num;
          count ++;
        }
        //Print the average grade
        printf("Average grade: %.1f\n", result / count);
        printf("Enter any character to return to menu: ");
        //Clear the input
        while((c = getchar()) != '\n' && c != EOF);
        //Wait for user to enter anything
        getchar();
        break;

      //EX3 DELETE REDUNDANT SPACES

      case 3:
        system("clear");
        //Clear the input
        while((c = getchar()) != '\n' && c != EOF);
        count = 0;
        printf("Enter anything, redundant spaces will disappear: ");
        c = getchar();
        printf("Now you only see: ");
        while(c != '\n' && c != EOF) {
          if(c == ' ') {
            if(count == 0) {
              count ++;
              putchar(c);
            }
          }
          else {
            count = 0;
            putchar(c);
          }
          c = getchar();
        }
        printf("\nEnter any character to return to menu: ");
        //Wait for user to enter anything
        getchar();
        break;

      //REPLACE /t AND /

      case 4:
        system("clear");
        //Clear the input
        while((c = getchar()) != '\n' && c != EOF);
        printf("Enter anything, tab will be replaced by \\t and \\ will become \\\\\n");
        c = getchar();
        printf("\nLike this: ");
        while(c != '\n' && c != EOF) {
          if(c == '\t') printf("\\t");
          else if(c == '\\') printf("\\\\");
          else putchar(c);
          c = getchar();
        }
        printf("\nEnter any character to return to menu: ");
        //Wait for user to enter anything
        getchar();
        break;

      //INVALID INPUT

      default:
        //Clear the input
        while((c = getchar()) != '\n' && c != EOF);
    }
  } while(choice != 5);

  return 0;
}
