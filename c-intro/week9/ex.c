#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Suporting function
void wait();    //Wait for input to continue
float mustBeFloat();  //Force input to be positive float
int mustBeInt();   //Force input to be positive int
//Ex1
float KE(float m, float v);    //kinetic energy
//Ex2
int is_prime(int n);   //check prime number
//Ex3
int salary(int h);   //calculate salary
//Ex4
int isLeapYear(int y);  //check leap year

              // MAIN PROGRAM
int main() {
  int choice;
  do {
    system("clear");
    printf("\tHOMEWORK 8:\n\n1. Kinetic energy\n2. Prime numbers\n");
    printf("3. Salary calculator\n4. Leap year\n5. Exit\n");
    printf("\nEnter your choice (1-5): ");
    choice = mustBeInt();
    switch (choice) {
      //EX 1 CALCULATE KINETIC ENERGY
      case 1:
        system("clear");
        printf("\tCalculate kinetic energy\n\n");
        printf("Enter mass: ");
        float mass = mustBeFloat();
        printf("Enter velocity: ");
        float vel = mustBeFloat();
        printf("Kinetic energy is: %.2f J\n", KE(mass, vel));
        wait();
        break;

      //EX 2 LIST OF PRIME NUMBERS
      case 2:
        system("clear");
        printf("\tList of prime numbers\n\n");
        printf("Enter a positive integer: ");
        int n = mustBeInt();
        printf("All the prime numbers from 2 up to %d is:\n", n);
        for (int x = 2; x <= n; x++) {
          if(is_prime(x)) printf("%d  ", x);
        }
        printf("\n");
        wait();
        break;

      //EX 3 CALCULATE SALARY
      case 3:
        system("clear");
        printf("\tSalary calculator\n\n");
        printf("Enter total working hour: ");
        int h;
        do {
          h = mustBeInt();
          if (h < 10) printf("Cannot work less than 10 hours, enter again: ");
          if (h > 65) printf("Cannot work more than 65 hours, enter again: ");
        } while (h < 10 || h > 65);
        printf("Salary: %d VND\n", salary(h));
        wait();
        break;

      //EX 4 DAY IN MONTH IN (LEAP) YEAR
      case 4:
        system("clear");
        printf("\tLeap year\n\n");
        printf("Enter year: ");
        int y = mustBeInt();
        printf("Enter month: ");
        int m;
        do {
          m = mustBeInt();
          if (m > 12) printf("Invalid, enter again: ");
        } while (m > 12);
        printf("This month has ");
        switch (m) {
          case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            printf("31 days\n");
            break;
          case 4: case 6: case 9: case 11:
            printf("30 days\n");
            break;
          case 2:
            printf("%d days\n", isLeapYear(y) ? 29: 28);
            break;
        }
        wait();
        break;
    }
  } while(choice != 5);

  return 0;
}

                  // SUPPORTING FUNCTION
//Wait for input to continue
void wait () {
  char c;
  printf("Enter any character to return to menu: ");
  //Clear the input
  while((c = getchar()) != '\n' && c != EOF);
  //Wait for user to enter anything
  getchar();
}
//Force input value to be positive float
float mustBeFloat () {
  char c;
  float n;
  while(!scanf("%f", &n) || n < 0) {
    //Clear the input
    while((c = getchar()) != '\n' && c != EOF);
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Force input value to be positive int
int mustBeInt () {
  char c;
  int n;
  while(!scanf("%d", &n) || n < 0) {
    //Clear the input
    while((c = getchar()) != '\n' && c != EOF);
    printf("Invalid input, enter again: ");
  }
  return n;
}

                  // MAIN FUNCTION
//Ex1 calculate kinetic energy
float KE (float m, float v) {
  return m * v * v / 2;
}
//Ex2 check is prime
int is_prime (int n) {
  if (n == 2) return 1;
  for (int x = 2; x <= sqrt(n); x++) {
    if (!(n % x)) return 0;
  }
  return 1;
}
//Ex3 calculate salary
int salary (int h) {
  int a = 15000; //Average salary per hour
  return h > 40 ? (40 * a) + ((h - 40) * a * 1.5) : h * a;
}
//Ex4 check leap year
int isLeapYear (int y) {
  if (!(y % 400))
    return 1;
  else
    return (!(y % 4) && (y % 100)) ? 1 : 0;
}
