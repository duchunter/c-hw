#include <stdio.h>
#include <string.h>

// A structure contain student's name and name's length
typedef struct {
  char name[20][30];
  int l; // The number of words in student's name
} Student;

// Receive input and add name to a list
void getName (Student list[], int listLength) {
  for (int x = 0; x < listLength; x++) {
    int a = 0, b = 0;
    char ch;
    printf("- Student %d: ", x + 1);
    while (1) {
      ch = getchar();

      // Line break = end of name
      if (ch == '\n') {
        list[x].name[a][b] = '\0';
        break;
      }

      // Space = end of word
      else if (ch == ' ') {
        list[x].name[a][b] = '\0';
        a++;
        b = 0;
      }

      // Other = character in a word
      else {
        list[x].name[a][b] = ch;
        b++;
      }
    }

    // Set the number of words
    list[x].l = a + 1;
  }
}

// Compare 2 names in Vietnamese way
int namecmp (Student a, Student b) {
  int la = a.l - 1;
  int lb = b.l - 1;
  while (1) {
    int result = strcmp(a.name[la], b.name[lb]);
    if (result != 0) return result;

    // If equal, compare the next word
    la--;
    lb--;

    // One name is shorter = smaller
    if (la == 0 && lb > 0) return -1;
    else if (la > 0 && lb == 0) return 1;

    // Same length and same every word
    else return 0;
  }
}

                      // MAIN PROGRAM

int main(int argc, char const *argv[]) {
  Student list[100];
  int listLength, x, y;

  // Input the student list
  printf("How many students do you want to add?: ");
  scanf("%d", &listLength);
  getchar();
  getName(list, listLength);

  // Sort the list using selection method
  Student temp;
  for (x = 0; x < listLength - 1; x++) {
    int min = x;

    // Choose the smallest value
    for (y = x + 1; y < listLength; y++) {
      if (namecmp(list[y], list[min]) < 0) min = y;
    }

    // Swap min with current x
    temp = list[x];
    list[x] = list[min];
    list[min] = temp;
  }

  //  Print sorted list and count similar name
  int max = 0, index = 0, count = 0, target = 0;
  printf("\nThe sorted list is:\n");

  // One loop, 2 purpose
  for (x = 0; x < listLength; x++) {
    // Print name
    for (y = 0; y < list[x].l; y++) printf("%s ", list[x].name[y]);
    printf("\n");

    // Compare and count
    char *currentName = list[x].name[list[x].l - 1];
    char *targetName = list[target].name[list[target].l - 1];

    // Increase count until new lastname appear
    if (strcmp(currentName, targetName) == 0) {
      count++;
    } else {
      // Before count new lastname, check previous first
      if (count > max) {
        max = count;
        index = x - 1;
      }
      // Reset count and set new target
      count = 1;
      target = x;
    }
  }

  // One more check due to end of array/loop
  if (count > max) {
    max = count;
    index = x - 1;
  }

  char *popular = list[index].name[list[index].l - 1];
  printf("\n'%s' is the most popular name (%d times)\n", popular, max);

  return 0;
}
