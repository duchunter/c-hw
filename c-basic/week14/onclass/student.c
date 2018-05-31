#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 80
#define MAX_LENGTH 40
#define MAX_NAME 25
#define INPUT "student.txt"

void wait () {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

// Import student list from file
int import(char arr[][MAX_NAME]) {
  FILE *f;
  int l = 0;
  if ((f = fopen(INPUT, "r")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return 0;
  }

  char name[MAX_NAME];
  while (fgets(name, LINE, f) != NULL) {
    name[strlen(name) - 1] = '\0';
    strcpy(arr[l++], name);
  }

  fclose(f);
  return l;
}

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

// Code less
int vncmp(char *name1, char *name2) {
  int l1 = strlen(name1);
  int l2 = strlen(name2);
  return namecmp(name1 + l1, name2 + l2, l1, l2);
}

// Heap sort
void adjustArr(char arr[][MAX_NAME], int root, int l) {
    char temp[MAX_NAME];
    int child, l1, l2;
    strcpy(temp, arr[root - 1]);
    child = (root) * 2 - 1;
    while (child <= l - 1) {
        if ((child < l - 1) && (vncmp(arr[child], arr[child + 1]) < 0)) {
            child++;
        }

        if (vncmp(temp, arr[child]) > 0) break;
        else {
            strcpy(arr[(child + 1) / 2 - 1], arr[child]);
            child = (child + 1) * 2 - 1;
        }
    }

    strcpy(arr[(child + 1) / 2 - 1], temp);
}

void heapSort(char arr[][MAX_NAME], int l) {
    l -= 1;
    char temp[MAX_NAME];
    int x;
    for (x = l / 2; x > 0; x--) {
        adjustArr(arr, x, l);
    }

    for (x = l; x > 0; x--) {
        strcpy(temp, arr[0]);
        strcpy(arr[0], arr[x]);
        strcpy(arr[x], temp);
        adjustArr(arr, 1, x);
    }
}

// Quick sort
void quickSort(char arr[][MAX_NAME], int left, int right) {
    int i, j;
    char temp[MAX_NAME], pivot[MAX_NAME];
    if (left < right) {
        i = left;
        j = right + 1;
        strcpy(pivot, arr[left]);
        do {
            do {
                i++;
            } while (vncmp(arr[i], pivot) < 0);

            do {
                j--;
            } while (vncmp(arr[j], pivot) > 0);

            if (i < j) {
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        } while (i < j);

        strcpy(temp, arr[left]);
        strcpy(arr[left], arr[j]);
        strcpy(arr[j], temp);
        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
}


// Print arr
void printArr(char arr[][MAX_NAME], int l) {
    for (int x = 0; x < l; x++) {
        printf("%s\n", arr[x]);
    }
}

int main(int argc, char const *argv[]) {
  char arr[MAX_LENGTH][MAX_NAME];
  int l = import(arr);
  //heapSort(arr, l);
  quickSort(arr, 0, l);
  printArr(arr, l);
  return 0;
}
