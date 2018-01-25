#include <stdio.h>
#include <stdlib.h>

#define MAX 100  //max array length
#define lengthEx3 10 //Ex3 length
#define size 3   //Ex4 matrix size

// Suporting function
void wait();    //Wait for input to continue
float mustBeFloat();  //Force input to be float
int mustBeInt(int positive);   //Force input to be (positive) int
void createIntArr(int arr[], int length);  //Create an int array
void createFloatArr(float arr[], int length);   //Create an float array

//Ex2
int isEqual(int arr1[], int arr2[], int length);  //Check if 2 arrays are equal
//Ex3
void norSort(int arr[], int length);    //Normal decreasing Sort
void oddSort(int arr[], int length);    //Only sort odd numbers
//Ex5
int isSymmetric(int arr[], int length);  //Check symmetricity
//Ex6
void reverse (float arr[], int length);   //Reverse array


              // MAIN PROGRAM
int main() {
  int choice, x, y, z;  //For counting stuff
  int arr[MAX], arr1[MAX];  //All array needed
  float arr2[MAX];  //For ex6
  int l;  //For length assignment
  do {
    //Reset array
    arr[0] = arr1[0] = '\0';
    //Clear screen
    system("clear");
    printf("\tHOMEWORK 9 - Play with arrays:\n\n1. Sum of odd numbers and min value\n");
    printf("2. Equal arrays\n3. Sort array\n4. Matrix multiplication\n");
    printf("5. Symetric array\n6. Reverse array\n\n0. Exit\n");
    printf("\nEnter your choice (1-5): ");
    choice = mustBeInt(0);
    switch (choice) {
      //EX 1 SUM OF ODD AND MIN VALUE
      case 1:
        system("clear");
        printf("\tEx1: Sum of odd and min value\n\n");
        printf("Enter length (you don't want to enter 100 values, right?): ");
        l = mustBeInt(1);  //length
        createIntArr(arr, l);
        int sum = 0, min = arr[0];
        for (x = 0; x < l; x++) {
          if (arr[x] % 2) sum += arr[x];
          if (arr[x] < min) min = arr[x];
        }
        printf("Sum of all odd numbers is: %d\n", sum);
        printf("Minimum value: %d\n", min);
        wait();
        break;

      //EX 2 EQUAL ARRAYS
      case 2:
        system("clear");
        printf("\tEx2: Equal array\n\n");
        int l1, l2;
        printf("Enter length of first array: ");
        l1 = mustBeInt(1);
        printf("Now the second: ");
        l2 = mustBeInt(1);
        if (l1 != l2)
          printf("2 arrays are not equal\n");
        else {
          printf("* Array 1:\n");
          createIntArr(arr, l1);
          printf("* Array 2:\n");
          createIntArr(arr1, l2);
          if (isEqual(arr, arr1, l1))
            printf("2 arrays are equal\n");
          else
            printf("2 arrays are not equal\n");
        }
        wait();
        break;

      //EX 3 SORT ARRAY
      case 3:
        system("clear");
        printf("\tEx3: Sort array\n\n");
        printf("Enter 10 values\n");
        createIntArr(arr, lengthEx3);
        //Copy that array to arr1
        for (x = 0; x < lengthEx3; x++) arr1[x] = arr[x];
        //Apply sort
        norSort(arr, lengthEx3);
        oddSort(arr1, lengthEx3);
        printf("Sort all:\n  ");
        for (x = 0; x < lengthEx3; x++) printf("%d  ", arr[x]);
        printf("\n");
        printf("Sort odd numbers only:\n  ");
        for (x = 0; x < lengthEx3; x++) printf("%d  ", arr1[x]);
        printf("\n");
        wait();
        break;

      //EX 4 MAXTRIX MULTIPLICATION
      case 4:
        system("clear");
        printf("\tEx4: Matrix multiplication\n\n");
        int A[size][size], B[size][size], C[size][size];
        //Initialize matrix A
        printf("Matrix A\n");
        for (x = 0; x < size; x++) {
          printf("  Enter row %d\n", x + 1);
          createIntArr(A[x], size);
        }
        //Initialize matrix B
        printf("Matrix B\n");
        for (x = 0; x < size; x++) {
          printf("  Enter row %d\n", x + 1);
          createIntArr(B[x], size);
        }
        //Calculate A * B
        for (x = 0; x < size; x++) {
          for (y = 0; y < size; y++) {
            //Take all value in row (x+1) of A
            for (z = 0; z < size; z++) arr[z] = A[x][z];
            //Take all value in col (y + 1) of B
            for (z = 0; z < size; z++) arr1[z] = B[z][y];
            //Cij = Ai*Bj
            int sum = 0;
            for (z = 0; z < size; z++) sum += arr[z] * arr1[z];
            C[x][y] = sum;
          }
        }
        //Display
        printf("Matrix multiplication A * B = C\n");
        printf("(Please resize your terminal for best display)\n\n");
        printf(" _           _     _           _     _           _\n");
        for (x = 0; x < size; x++) {
          //Matrix A
          if (x == size - 1) printf("|_");
          else printf("| ");
          for (y = 0; y < size; y++) printf("%3d", A[x][y]);
          if (x == size - 1) printf("  _|");
          else printf("   |");
          // "*" sign
          if (x == size / 2) printf(" * ");
          else printf("   ");
          //Matrix B
          if (x == size - 1) printf("|_");
          else printf("| ");
          for (y = 0; y < size; y++) printf("%3d", B[x][y]);
          if (x == size - 1) printf("  _|");
          else printf("   |");
          // "=" sign
          if (x == size / 2) printf(" = ");
          else printf("   ");
          //Matrix C
          if (x == size - 1) printf("|_");
          else printf("| ");
          for (y = 0; y < size; y++) printf("%3d", C[x][y]);
          if (x == size - 1) printf("  _|");
          else printf("   |");

          printf("\n");
        }
        printf("\n");
        wait();
        break;

      //EX5 SYMETRIC ARRAY
      case 5:
        system("clear");
        printf("\tEx5: Symetric array\n\n");
        printf("Enter array's length: ");
        l = mustBeInt(1);
        createIntArr(arr, l);
        if (isSymmetric(arr, l))
          printf("This array is symmetric\n");
        else
          printf("This array is not symmetric\n");
        wait();
        break;

      //EX6 REVERSE ARRAY
      case 6:
        system("clear");
        printf("\tEx6: Reverse array\n\n");
        printf("Enter array's length: ");
        l = mustBeInt(1);
        createFloatArr(arr2, l);
        reverse(arr2, l);
        printf("The new array is:\n");
        for (x = 0; x < l; x++) printf("%.2f  ", arr2[x]);
        printf("\n");
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
int mustBeInt (int positive) {
  char c;
  int n;
  while(!scanf("%d", &n) || (positive && n <= 0)) {
    //Clear the input
    while((c = getchar()) != '\n' && c != EOF);
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Create an int array
void createIntArr (int arr[], int length) {
  for (int x = 0; x < length; x++) {
    printf("  - Enter value %d: ", x + 1);
    arr[x] = mustBeInt(0);
  }
}
//Create an float array
void createFloatArr (float arr[], int length) {
  for (int x = 0; x < length; x++) {
    printf("  - Enter value %d: ", x + 1);
    arr[x] = mustBeFloat();
  }
}
                  // MAIN FUNCTION
// Ex2 check if 2 arrays are equal
int isEqual (int arr1[], int arr2[], int length) {
  for (int x = 0; x < length; x++) {
    if (arr1[x] != arr2[x]) return 0;
  }
  return 1;
}
// Ex3 normal decreasing Sort
void norSort (int arr[], int length) {
  int next = 1;
  //Apply swap sort
  while (next) {
    next = 0;
    for (int x = 0; x < length - 1; x++) {
      if (arr[x + 1] > arr[x]) {
        int temp = arr[x];
        arr[x] = arr[x + 1];
        arr[x + 1] = temp;
        next = 1;
      }
    }
  }
}
// Ex3 sort only odd numbers
void oddSort (int arr[], int length) {
  int x, y = 0, arr2[MAX], arr3[MAX];
  for (x = 0; x < length; x++) {
    if (arr[x] % 2) {
      //Copy all odd numbers to another array
      arr2[y] = arr[x];
      //Also copy that number's position to another array
      arr3[y] = x;
      y++;
    }
  }
  //Sort all-odd array
  norSort(arr2, y);
  //Place all sorted numbers back to the initial array
  for (x = 0; x < y; x++) {
    arr[arr3[x]] = arr2[x];
  }
}
//Ex 5 check symmetricity
int isSymmetric (int arr[], int length) {
  for (int x = 0; x < length / 2; x++) {
    if (arr[x] != arr[length - x - 1]) return 0;
  }
  return 1;
}
//Ex6 reverse array
void reverse (float arr[], int length) {
  for (int x = 0; x < length / 2; x++) {
    int temp = arr[x];
    arr[x] = arr[length - x -1];
    arr[length - x - 1] = temp;
  }
}
