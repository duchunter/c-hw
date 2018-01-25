#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                        //STRUCTURES
typedef struct {

};

                    // SUPPORTING FUNCTIONS

//fflush
void clear () {
  while(getchar() != '\n');
}
//Wait for input to continue
void wait () {
  printf("\nEnter anything to return to menu: ");
  //Wait for user to enter anything
  getchar();
}
//Force input value to be float
float mustBeFloat () {
  double n;
  while(!scanf("%lf", &n)) {
    clear();
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Force input value to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n)) {
    clear();
    printf("Invalid input, enter again: ");
  }
  return n;
}


                    // MAIN PROGRAM  //
int main() {
  int choice;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\t \n\n");
    printf("1.\n");
    printf("2.\n");
    printf("3.\n");
    printf("4.\n");
    printf("\n0. Exit\n");
    //Variables for all exercise that must be reset

    //Choose option and start
    printf("\nEnter your choice (0-): ");
    choice = mustBeInt();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        printf("\t\n\n");

        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\t\n\n");

        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\t\n\n");

        //Done
        wait();
        break;

      //EX 4
      case 4:
        system("clear");
        printf("\t\n\n");

        //Done
        wait();
        break;
    }
  } while(choice != 0);
  //Everything done
  system("clear");
  return 0;
}
