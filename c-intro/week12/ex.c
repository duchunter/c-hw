#include <stdio.h>
#include <stdlib.h>

// Suporting function
void wait();    //Wait for input to continue
float mustBeFloat();  //Force input to be float
int mustBeInt();   //Force input to be int

// Rotate 3 values
void rotate (int *a, int *b, int *c);

              // MAIN PROGRAM
int main() {
  int choice;
  do {
    //Clear screen
    system("clear");
    printf("\t\tHOMEWORK 10\n\n");
    printf("1. Display value of a pointer\n");
    printf("2. Print out the address of elements of a predefined array\n");
    printf("3. Adding 100 using pointer\n");
    printf("4. Rotate 3 values\n");
    printf("5. Swaping values and pointers\n");
    printf("\n0. Exit\n");
    printf("\nEnter your choice (1-5): ");
    choice = mustBeInt(0);
    switch (choice) {
      //EX 1 VALUE OF A POINTER
      case 1:
        system("clear");
        printf("\t1. Display value of a pointer\n\n");
        //Input value
        int val1, val2, val3, *ptr1;
        printf("Enter value 1: ");
        val1 = mustBeInt();
        printf("Enter value 2: ");
        val2 = mustBeInt();
        printf("Enter value 3: ");
        val3 = mustBeInt();
        //Set pointer and print
        ptr1 = &val1;
        printf("Value of the pointer: %d\n", *ptr1);
        ptr1 = &val2;
        printf("Value of the pointer: %d\n", *ptr1);
        ptr1 = &val3;
        printf("Value of the pointer: %d\n", *ptr1);
        //Done
        wait();
        break;

      //EX 2 PRINT ADDRESS OF ARRAY'S ELEMENTS
      case 2:
        system("clear");
        printf("\t2. Print out the address of elements of a predefined array\n\n");
        printf("\t{13, -355, 235, 47, 67, 943, 1222}\n\n");
        int arr[] = {13, -355, 235, 47, 67, 943, 1222};
        int *ptr2 = arr;
        for (int count = 0; count < 5; count++) {
          printf("Element %d's address: %p\n", count + 1, ptr2 + count);
        }
        wait();
        break;

      //EX 3 ADDING USING POINTER
      case 3:
        system("clear");
        printf("\t3. Adding 100 using pointer\n\n");
        //Input value
        float a, b, c, *ptr3;
        printf("Enter value a: ");
        a = mustBeFloat();
        printf("Enter value b: ");
        b = mustBeFloat();
        printf("Enter value c: ");
        c = mustBeFloat();
        //Adding 100
        ptr3 = &a;
        *ptr3 += 100;
        ptr3 = &b;
        *ptr3 += 100;
        ptr3 = &c;
        *ptr3 += 100;
        //Print result
        printf("New values are: %.2f  %.2f  %.2f\n", a, b, c);
        //Done
        wait();
        break;

      //EX 4 ROTATE 3 VALUES
      case 4:
        system("clear");
        printf("\t4. Rotate 3 values\n\n");
        //Input
        int m, n, l;
        printf("Enter value 1: ");
        m = mustBeInt();
        printf("Enter value 2: ");
        n = mustBeInt();
        printf("Enter value 3: ");
        l = mustBeInt();
        //Rotate and print the result
        rotate(&m, &n, &l);
        printf("New order is: %d  %d  %d\n", m, n, l);
        //Done
        wait();
        break;

      //EX 5 SWAPPING VALUES AND POINTERS
      case 5:
        system("clear");
        printf("\t5. Swaping values and pointers\n\n");
        //Input
        int x, y, z;
        printf("Enter value x: ");
        x = mustBeInt();
        printf("Enter value y: ");
        y = mustBeInt();
        printf("Enter value z: ");
        z = mustBeInt();
        //Set pointer to x, y, z
        int *p = &x, *q = &y, *r = &z;
        //Print out
        printf("\nx = %d\ny = %d\nz = %d\n", x, y, z);
        printf("p = %p\nq = %p\nr = %p\n", p, q, r);
        printf("*p = %d\n*q = %d\n*r = %d\n", *p, *q, *r);
        //Swap x, y ,z and print out
        rotate(&x, &y, &z);
        printf("\nx = %d\ny = %d\nz = %d\n", x, y, z);
        printf("p = %p\nq = %p\nr = %p\n", p, q, r);
        printf("*p = %d\n*q = %d\n*r = %d\n", *p, *q, *r);
        //Swap p, q, r
        int *tmp = p;
        p = r;
        r = q;
        q = tmp;
        //Print out
        printf("\nx = %d\ny = %d\nz = %d\n", x, y, z);
        printf("p = %p\nq = %p\nr = %p\n", p, q, r);
        printf("*p = %d\n*q = %d\n*r = %d\n", *p, *q, *r);
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  return 0;
}

                  // SUPPORTING FUNCTION

//Wait for input to continue
void wait () {
  char c;
  printf("\nEnter any character to return to menu: ");
  //Clear the input
  while((c = getchar()) != '\n' && c != EOF);
  //Wait for user to enter anything
  getchar();
}
//Force input value to be positive float
float mustBeFloat () {
  char c;
  float n;
  while(!scanf("%f", &n)) {
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
  while(!scanf("%d", &n)) {
    //Clear the input
    while((c = getchar()) != '\n' && c != EOF);
    printf("Invalid input, enter again: ");
  }
  return n;
}

              // EXERCISE'S REQUIRED FUNCTIONS

// Rotate 3 values
void rotate (int *a, int *b, int *c) {
  int tmp = *a;
  *a = *c;
  *c = *b;
  *b = tmp;
}
