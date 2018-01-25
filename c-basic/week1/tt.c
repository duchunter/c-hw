#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arrcmp(int arr1[], int arr2[], int l1, int l2) {
  // Different length then arrs are different
  if (l1 != l2) return 0;

  // Suppose that they are equal and symmetric
  int sym = 1, equal = 1;
  for (int x = 0; x < l1; x++) {
    // If not equal then check sym
    if (arr1[x] != arr2[x]) {
      equal = 0;
      if (arr1[x] != arr2[l1 - x - 1]) sym = 0;
    }

    // If not equal and sym, return 0 without continue looping
    if (!sym && !equal) return 0;
  }

  // If loop is finish then they are either equal or sym
  return equal ? 1 : -1;
}

void *createArr (int *arr, int l) {
  for (int x = 0; x < l; x++) {
    printf("- Element %d: ", x + 1);
    scanf("%d", &arr[x]);
  }
}

int main(int argc, char const *argv[]) {
  /* EX1: Find the median
  int x, l, arr[100], median, sum = 0;
  printf("Enter number of element: ");
  scanf("%d", &l);

  // Input elements
  for (x = 0; x < l; x++) {
    printf("Element %d: ", x + 1);
    scanf("%d", &arr[x]);

    // Get the sum of all element
    sum += arr[x];
  }

  float medium = sum / l;

  // Set minRange and median to the first element
  float minRange = arr[0] - medium;
  median = arr[0];

  // Take the positive value only for range
  if (minRange < 0) minRange *= -1;

  // Compare the range of each other element to median
  for (x = 1; x < l; x++) {
    float range = arr[x] - medium;
    if (range < 0) range *= -1;

    // Assign new median
    if (range < minRange) {
      minRange = range;
      median = arr[x];
    }
  }

  printf("Median: %d\n", median);
  */

  /* EX2: Compare 2 arrays about equality and symmetry
  int x, arr1[100], arr2[100], l1, l2;

  // Input array 1
  printf("\n\tArray 1\n");
  printf("Enter number of element: ");
  scanf("%d", &l1);
  createArr(arr1, l1);

  // Input array 2
  printf("\n\tArray 2\n");
  printf("Enter number of element: ");
  scanf("%d", &l2);
  createArr(arr2, l2);

  printf("\n");
  int cmp = arrcmp(arr1, arr2, l1, l2);
  switch (cmp) {
    case 1:
      printf("2 arrays are equal\n");
      break;

    case -1:
      printf("2 arrays are symmetric\n");
      break;

    case 0:
      printf("2 arrays are different\n");
      break;
  }
  */

  /* EX3: Count the frequency of each letter in a string
  char str[100], ch;
  int count[26] = {0}, x;
  printf("Enter a string: ");
  fgets(str, 100, stdin);
  for (x = 0; x < strlen(str); x++) {
    if ('a' <= str[x] && str[x] <= 'z') {
      count[str[x] - 'a']++;
    }
    if ('A' <= str[x] && str[x] <= 'Z') {
      count[str[x] - 'A']++;
    }
  }

  for (x = 0; x < 26; x++) {
    if (count[x] > 0) {
      printf("The letter '%c' appears %d time(s)\n", x + 'a', count[x]);
    }
  }
  */

  /* EX4: Split sentence to words
  char ch;
  int flag = 0;;
  printf("Enter a string: ");
  while ((ch = getchar()) != '\n') {
    if (ch == ' ' || ch == '\t') {
      if (!flag) printf("\n");
      flag = 1;
    } else {
      putchar(ch);
      flag = 0;
    }
  }
  printf("\n");
  */

  /* Calculate rectangle's area and perimeter using argc and argv
  if (argc != 3) {
    printf("Invalid syntax, should be: %s 'height' 'width'\n", argv[0]);
    return -1;
  }

  float height = atof(argv[1]);
  float width = atof(argv[2]);
  printf("Area: %.2f\n", height * width);
  printf("Perirmeter: %.2f\n", (height + width) * 2);
  */

  /* EX5: Word replication using arg */
  if (argc != 3) {
    printf("Invalid syntax, should be: %s 'str' 'int'\n", argv[0]);
    return -1;
  }

  int rep = atoi(argv[2]);
  for (int x = 0; x < rep; x++) printf("%s", argv[1]);
  printf("\n");

  return 0;
}
