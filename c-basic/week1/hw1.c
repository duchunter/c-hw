#include <stdio.h>
#include <string.h>

/*
Return pointer to the start of lastword
Require address of the last element of the string and its length
*/
char *getLastWord(char *e, int l) {
  // Move the pointer up until reach ' ' or start of the string
  while (*e != ' ' && l > 0) {
    l--;
    e -= 1;
  }

  return e;
}

/*
Compare 2 names in Vietnamese
Require 2 address of last element and 2 length
*/
int namecmp(char *e1, char *e2, int l1, int l2) {
  // Cut out 2 lastwords and decrease string length
  char *ne1 = getLastWord(e1, l1);
  l1 -= e1 - ne1;
  char *ne2 = getLastWord(e2, l2);
  l2 -= e2 - ne2;

  // Compare 2 lastwords
  int cmp = strcmp(ne1 + 1, ne2 + 1);
  if (cmp == 0) {
    // Depend on the remaining character in 2 strings
    if (l1 == 0 && l2 > 0) return -1;
    if (l2 == 0 && l1 > 0) return 1;
    if (l1 == 0 && l2 == 0) return 0;

    // If cannot decide, continue comparing the remaining words
    return namecmp(ne1 - 1, ne2 - 1, l1 - 1, l2 - 1);
  }

  // If can compare from the first words then stop
  return cmp;
}

                        // MAIN PROGRAM

int main(int argc, char const *argv[]) {
  // One-time used variables
  int x, y;

  // List array and its length
  int n;
  char list[100][100];

  // Input name list
  printf("How many students do you want to add?: ");
  scanf("%d", &n);
  getchar();
  for (x = 0; x < n; x++) {
    printf("Student %d: ", x + 1);
    fgets(list[x], 100, stdin);
  }

  // Sort the list using selection method
  char temp[100];
  for (x = 0; x < n - 1; x++) {
    int min = x;

    // Choose the smallest value
    for (y = x + 1; y < n; y++) {
      int l1 = strlen(list[min]);
      int l2 = strlen(list[y]);
      if (namecmp(&list[min][l1 - 1], &list[y][l2 - 1], l1, l2) == 1) {
        min = y;
      }
    }

    /*
    Swap min with current x
    to push min toward the start of array
    */
    strcpy(temp, list[x]);
    strcpy(list[x], list[min]);
    strcpy(list[min], temp);
  }

  // Print the sorted list and count same name
  int max = 0, maxIndex = 0, count = 0, target = 0;
  printf("\nThe sorted list is:\n");

  // While looping, compare it with target
  for (x = 0; x < n; x++) {
    printf("%d. %s", x + 1, list[x]);

    // Compare
    int l1 = strlen(list[target]);
    int l2 = strlen(list[x]);
    int cmp = strcmp(
          getLastWord(&list[target][l1 - 1], l1),
          getLastWord(&list[x][l2 - 1], l2)
    );

    /*
    Action based on compare result
    strcmp return != 0 means new lastname appear
    */
    if (cmp == 0) {
      count++;
    } else {
      // Before count new lastname, check previous first
      if (count > max) {
        max = count;
        maxIndex = x - 1;
      }
      // Reset count and set new target
      count = 1;
      target = x;
    }
  }

  // One more check due to end of array
  if (count > max) {
    max = count;
    maxIndex = x - 1;
  }

  // Get the common lastname and print out
  x = strlen(list[maxIndex]);
  char *common = getLastWord(&list[maxIndex][x - 1], x);
  // Omit '\n' in lastname
  common[strlen(common) - 1] = '\0';
  printf("\n'%s' (%d times) is the most common name\n", common, max);

  return 0;
}
