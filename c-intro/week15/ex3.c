#include <stdio.h>
#include <stdlib.h>

//Fraction structure
typedef struct {
  int x, y;    //  x / y
} frac;

//Supporting funtionc
void wait ();                       //Enter anything to return to menu
int mustBeInt ();                   //Force user to input int
int gcd (int x, int y);             //Find the greatest common divisor
frac inputFrac ();                  //Input a fraction
void arrFrac (frac *arr, int l);    //Input an array of fractions
void printAFrac (frac f);           //Print a fraction
void printFracs (frac *arr, int l); //Print all fractions in array
void inverseArr (frac *arr, int l); //Inverse all fractions in array
int fraccmp (frac a, frac b);       //Compare 2 fractions
frac mulFrac (frac a, frac b);      //Multiply 2 fractions
frac addFrac (frac a, frac b);      //Add 2 fractions

//MAIN PROGRAM (menu based)

int main(int argc, char const *argv[]) {
  int choice;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tEx3: Fractions\n\n");
    printf("1. Input an array of fractions -> inverse all fractions\n");
    printf("2. Compare 2 fractions -> multiply and add\n");
    printf("\n0. Exit\n");
    printf("\nEnter your choice (0-2): ");
    //Variables for all option
    frac arr[30];
    //Choose option and start
    choice = mustBeInt();
    switch (choice) {
      case 1:
        system("clear");
        int l;
        printf("\nEnter number of fractions: ");
        while (1) {
          l = mustBeInt();
          if (l <= 0) {
            printf("You must enter at least 1 fraction, enter again: ");
          }
          else break;
        }
        arrFrac(arr, l);
        printf("\nBefore inverse: ");
        printFracs(arr, l);
        inverseArr(arr, l);
        printf("\nAfter inverse: ");
        printFracs(arr, l);
        //Done
        printf("\n");
        wait();
        break;

      case 2:
        system("clear");
        arrFrac(arr, 2);
        //Compare
        printf("\nComparision:\t");
        printAFrac(arr[0]);
        switch (fraccmp(arr[0], arr[1])) {
          case -1:
            printf(" < ");
            break;
          case 0:
            printf(" = ");
            break;
          case 1:
            printf(" > ");
            break;
        }
        printAFrac(arr[1]);
        //Multiply
        printf("\nProduct:\t");
        printAFrac(mulFrac(arr[0], arr[1]));
        //Add
        printf("\nSum:\t\t");
        printAFrac(addFrac(arr[0], arr[1]));
        printf("\n");
        //Done
        wait();
        break;
    }
  } while (choice != 0);

  //End of program
  printf("\n");
  return 0;
}

//FUNCTIONS

void wait () {
  printf("\nEnter anything to return to menu: ");
  //Clear the input
  while(getchar() != '\n');
  //Wait for user to enter anything
  getchar();
}
//Force input to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n)) {
    //Clear the input
    while(getchar() != '\n');
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Calculate gcd
int gcd (int x, int y) {
  x = (x > 0) ? x : -x;
  y = (y > 0) ? y : -y;
  return (x == y) ? x : (x > y) ? gcd(x - y, y) : gcd(x, y - x);
}
//Input fraction
frac inputFrac () {
  frac f;
  printf("Enter x: ");
  f.x = mustBeInt();
  printf("Enter y: ");
  f.y = mustBeInt();
  while (f.y == 0) {
    printf("y cannot be 0, enter y again: ");
    f.y = mustBeInt();
  }
  if (f.x != 0) {
    int common = gcd(f.x, f.y);
    f.x /= common;
    f.y /= common;
  }
  return f;
}
//Input array of fractions
void arrFrac (frac *arr, int l) {
  for (int x = 0; x < l; x++) {
    printf("\n- Fraction %d\n", x + 1);
    arr[x] = inputFrac();
  }
}
//Print a fraction
void printAFrac (frac f) {
  if (f.y == 1 || f.x == 0)
    printf("%d", f.x);
  else if (f.y == 0)    //This happen when inverse 0
    printf("ERROR");
  else
    printf("%d/%d", f.x, f.y);
}
//Print fraction array
void printFracs (frac *arr, int l) {
  for (int x = 0; x < l; x++) {
    printAFrac(arr[x]);
    //Space between 2 Fractions
    printf("%s", (x == l - 1) ? "." : ", ");
  }
}
//Inverse all fractions in array
void inverseArr (frac *arr, int l) {
  for (int x = 0; x < l; x++) {
    int temp = arr[x].x;
    arr[x].x = arr[x].y;
    arr[x].y = temp;
  }
}
//Compare 2 fractions
int fraccmp (frac a, frac b) {
  float n = (float)a.x / (float)a.y - (float)b.x / (float)b.y;
  return (n == 0) ? 0 : (n > 0) ? 1 : -1;
}
//Multiply 2 fractions
frac mulFrac (frac a, frac b) {
  frac f;
  f.x = a.x * b.x;
  f.y = a.y * b.y;
  if (f.x != 0) {
    int common = gcd(f.x, f.y);
    f.x /= common;
    f.y /= common;
  }
  return f;
}
//Add 2 fractions
frac addFrac (frac a, frac b) {
  frac f;
  f.y = a.y * b.y;
  f.x = a.x * b.y + b.x * a.y;
  if (f.x != 0) {
    int common = gcd(f.x, f.y);
    f.x /= common;
    f.y /= common;
  }
  return f;
}
