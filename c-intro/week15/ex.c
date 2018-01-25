#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20   //Max array's size

// Suporting function
void wait ();    //Wait for input to continue
double mustBeDouble ();  //Force input to be double
int mustBeInt ();   //Force input to be int
void intArray (int arr[], int size);  //Create int array
void doubleArray (double arr[], int size);  //Create double array
int getSize (); //Choose array's size

//Exercise's functions
int countEven (int *arr, int size); // Count even numbers in ex1
double *maximum (double *a, int size); // Return pointer to max val in arr ex2

//Still execise's function but not required
void subArr (int *arr, int size); // List all subarr ex3
void indexReverse (int arr[], int size); // Reverse using indexes ex4
void pointerReverse (int *arr, int size); // Reverse using pointer ex4


                    // MAIN PROGRAM  //
int main() {
  int choice;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tHOMEWORK 11\n\n");
    printf("1. Count even numbers in an array\n");
    printf("2. Returns a pointer to the maximum value of an array\n");
    printf("3. List all sub array of an array\n");
    printf("4. Reverse an array in 2 different ways\n");
    printf("\n0. Exit\n");
    printf("\nEnter your choice (0-4): ");
    //Variables for all exercise
    int arr1[MAXSIZE], size;
    double arr2[MAXSIZE], *ptr = NULL;
    //Choose option and start
    choice = mustBeInt(0);
    switch (choice) {
      //EX 1 COUNT EVEN
      case 1:
        system("clear");
        printf("\t1. Count even numbers in an array\n\n");
        size = getSize();  // Choose arr size
        intArray(arr1, size);  // Input value
        printf("\nThere are (is) %d even number(s) in your array\n", countEven(arr1, size));
        //Done
        wait();
        break;

      //EX 2 POINTER TO THE MAXIMUM
      case 2:
        system("clear");
        printf("2. Returns a pointer to the maximum value of an array\n\n");
        size = getSize();  // Choose arr size
        doubleArray(arr2, size);  // Input value
        ptr = maximum(arr2, size);
        printf("\nThe pointer pointing to the maximum value:\n");
        printf("- Address:\t%p\n", ptr);
        printf("- Value:\t%.2lf\n", *ptr);
        //Done
        wait();
        break;

      //EX 3 SUB ARRAYS
      case 3:
        system("clear");
        printf("\t3. List all sub array of an array\n\n");
        size = getSize();  // Choose arr size
        intArray(arr1, size);  // Input value
        printf("\nAll sub-arrays are:\n");
        subArr(arr1, size);
        //Done
        wait();
        break;

      //EX 4 REVERSE ARRAY
      case 4:
        system("clear");
        printf("\t4. Reverse an array in 2 different ways\n\n");
        int c; // Used for counting
        size = getSize();  // Choose arr size
        intArray(arr1, size);  // Input value
        // Reverse using index
        indexReverse(arr1, size);
        printf("\nReverse using indexes: \n");
        for (c = 0; c < size; c++)
          printf("%d ", arr1[c]);
        //Reverse again using pointer
        pointerReverse(arr1, size);
        printf("\nReverse again using pointer: \n");
        for (c = 0; c < size; c++)
          printf("%d ", arr1[c]);
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  system("clear");
  return 0;
}

                  // SUPPORTING FUNCTION

//Wait for input to continue
void wait () {
  char c;
  printf("\nEnter anything to return to menu: ");
  //Clear the input
  while((c = getchar()) != '\n' && c != EOF);
  //Wait for user to enter anything
  getchar();
}
//Force input value to be double
double mustBeDouble () {
  char c;
  double n;
  while(!scanf("%lf", &n)) {
    //Clear the input
    while((c = getchar()) != '\n' && c != EOF);
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Force input value to be int
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
//Create int array
void intArray (int arr[], int size) {
  //Input value for arr
  for (int x = 0; x < size; x++) {
    printf("Enter value %d: ", x + 1);
    arr[x] = mustBeInt();
  }
}
//Create double array
void doubleArray (double arr[], int size) {
  //Input value for arr
  for (int x = 0; x < size; x++) {
    printf("Enter value %d: ", x + 1);
    arr[x] = mustBeDouble();
  }
}
//Choose array's size
int getSize () {
  printf("Enter array's size: ");
  int size;
  //Size must be > 0
  while (1) {
    size = mustBeInt();
    if (size <= 0)
      printf("Must be greater than 0. Try again: ");
    else
      break;
  }
  return size;
}

              // EXERCISE'S REQUIRED FUNCTIONS

//Count even numbers in ex1
int countEven (int *arr, int size) {
  int even = 0;
  for (int x = 0; x < size; x++) {
    if (*(arr + x) % 2 == 0)
      even++;
  }
  return even;
}
//Return pointer to max val in arr ex2
double *maximum (double *a, int size) {
  //Check arr length
  if (size == 0)
    return NULL;
  //Ok
  double *max = a;
  for (int x = 1; x < size; x++) {
    if (*(a + x) > *max)
      max = a + x;
  }
  return max;
}
// List all subarr ex3
void subArr (int *arr, int size) {
  int a, b, c;  // Used for counting
  for (int a = 0; a < size; a++) {
    for (int b = size - 1; b >= a; b--) {
      for (int c = 0; c < size - b; c++)
        //Print an array
        printf("%d ", *(arr + a + c));
      //New line for next sub arr
      printf("\n");
    }
  }
}
// Reverse using indexes ex4
void indexReverse (int arr[], int size) {
  int tmp;
  for (int x = 0; x < size / 2; x++) {
    tmp = arr[x];
    arr[x] = arr[size - x - 1];
    arr[size - x - 1] = tmp;
  }
}
// Reverse using pointer ex4
void pointerReverse (int *arr, int size) {
  int tmp;
  for (int x = 0; x < size / 2; x++) {
    tmp = *(arr + x);
    *(arr + x) = *(arr + size - x - 1);
    *(arr + size - x - 1) = tmp;
  }
}
