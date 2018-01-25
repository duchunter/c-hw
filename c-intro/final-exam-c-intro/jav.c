#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Data structure
typedef struct {
  char name[31];
  char des[501];
  float rating;
  char add[101];
} res;

// SUPPORTING FUNCTION

//Clear
void clear () {
  while (getchar() != '\n');
}
//Wait for input to continue
void wait () {
  printf("\nEnter anything to return to menu: ");
  //Wait for user to enter anything
  getchar();
}
//Force input value to be double
float rate () {
  float n;
  while(!scanf("%f", &n) || n < 0 || n > 5) {
    clear();
    printf("Must be 0-5, enter again: ");
  }
  return n;
}
//Force input value to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n) || n <= 0) {
    clear();
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Check if string b exist in string a
int inString (char *a, char *b) {
  if (strlen(b) > strlen(a)) return 0;
  for (int x = 0; x < strlen(a); x++) {
    if (a[x] == b[0]) {
      for (int y = 1; y < strlen(b); y++) {
        if (a[x + y] != b[y]) return 0;
      }
      return 1;
    }
  }
  return 0;
}
//Return a new lowercase string
void lowercase (char *str1, char *str2) {
  int x;
  for (x = 0; x < strlen(str1); x++) {
    str2[x] = ('A' <= str1[x] && str1[x] <= 'Z') ? str1[x] - 'A' + 'a' : str1[x];
  }
  str2[x] = '\0';
}
//Print list
void printList (res *arr, int l) {
  for (int x = 0; x < l; x++) {
    printf("\nRestaurant %d\n", x + 1);
    printf("Name: %s\n", arr[x].name);
    printf("Description: %s\n", arr[x].des);
    printf("Rating: %.1f\n", arr[x].rating);
    printf("Address: %s\n", arr[x].add);
  }
}


                    // MAIN PROGRAM  //
int main() {
  int choice, n = 0, new, x;
  res list[50];
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tTEST\n\n");
    printf("1. Input restaurant\n");
    printf("2. Restaurant's info\n");
    printf("3. Search name\n");
    printf("4. Search food\n");
    printf("\n5. Exit\n");
    //Variables for all exercise that must reset
    res chosen[50];
    int l = 0;
    char query[50], lower1[50], lower2[50];
    //Choose option and start
    printf("\nEnter your choice (1-5): ");
    choice = mustBeInt();
    clear();
    switch (choice) {
      //EX 1 COUNT EVEN
      case 1:
        system("clear");
        printf("\tInput restaurant\n\n");
        printf("Current: %d\n", n);
        printf("Enter number of new restaurant: ");
        new = mustBeInt();
        clear();
        for (x = 0; x < new; x++) {
          printf("\n- Restaurant %d:\n", x + n + 1);
          printf("Name: ");
          scanf("%[^\n]s", list[x + n].name);
          getchar();
          printf("Description: ");
          scanf("%[^\n]s", list[x + n].des);
          getchar();
          printf("Rating: ");
          list[x + n].rating = rate();
          getchar();
          printf("Address: ");
          scanf("%[^\n]s", list[x + n].add);
          getchar();
        }
        n += new;
        //Done
        wait();
        break;

      //EX 2 POINTER TO THE MAXIMUM
      case 2:
        system("clear");
        printf("\tRestaurant's info\n\n");
        printList(list, n);
        //Done
        wait();
        break;

      //EX 3 SUB ARRAYS
      case 3:
        system("clear");
        printf("\tSearch name\n\n");
        printf("Enter restaurant's name: ");
        scanf("%[^\n]s", query);
        getchar();
        lowercase(query, lower1);
        for (x = 0; x < n; x++) {
          lowercase(list[x].name, lower2);
          if(inString(lower2, lower1)) {
            chosen[l] = list[x];
            l++;
          }
        }
        printf("\nResults:\n");
        if (l == 0) printf("\n\tNo restaurant found\n");
        else printList(chosen, l);
        //Done
        wait();
        break;

      //EX 4 REVERSE ARRAY
      case 4:
        system("clear");
        printf("\tSearch food\n\n");
        printf("Enter a food: ");
        scanf("%[^\n]s", query);
        getchar();
        lowercase(query, lower1);
        for (x = 0; x < n; x++) {
          lowercase(list[x].des, lower2);
          if(inString(lower2, lower1)) {
            chosen[l] = list[x];
            l++;
          }
        }
        printf("\nResults:\n");
        if (l == 0) printf("\n\tNo restaurant found\n");
        else printList(chosen, l);
        //Done
        wait();
        break;
    }
  } while(choice != 5);

  system("clear");
  return 0;
}
