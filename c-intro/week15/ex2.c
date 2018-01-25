            //Ex2: student management program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Student structure
typedef struct {
  char id[6];
  char name[31];
  float grade;
  char level;
} student;

//Supporting functions
student inputStd ();                //Input student's data
void sort (student arr[], int l);   //Sort according to grade

// MAIN PROGRAM

int main(int argc, char const *argv[]) {
  system("clear");
  printf("\t\tEx2: Student management program\n\n");
  int n, x;
  student arr[100];
  //Input number of student
  printf("How many student you want to input?: ");
    //Validate input
  while(!scanf("%d", &n) || n < 0) {
    //Clear input
    while(getchar() != '\n');
    printf("Invalid input, enter again: ");
  }
  //Input student's data
  for (x = 0; x < n; x++) {
    getchar();
    printf("\n- Student %d:\n", x + 1);
    arr[x] = inputStd();
  }
  //Sort and print the list
  sort(arr, n);
  printf("\n\t\tStudent list:\n");
  printf("%-6s  %-31s  %s\t%s\n", "ID", "Name", "Grade", "Level");
  printf("%-6s  %-31s  %s\t%s\n", "--", "----", "-----", "-----");
  for (x = 0; x < n; x++) {
    printf("%-6s  %-31s  %.1f\t%c\n", arr[x].id, arr[x].name, arr[x].grade, arr[x].level);
  }
  //Done
  printf("\n");
  return 0;
}

// FUNCTIONS

student inputStd () {
  student a;
  char str[100];  //Handle string input
  //Get name
  printf("Name: ");
  scanf("%[^\n]s", str);
  if (strlen(str) > 30) str[30] = '\0';    //only take 30 characters
  getchar();         //Eliminate \n left
  strcpy(a.name, str);
  //Get id
  printf("ID: ");
  scanf("%[^\n]s", str);
  if (strlen(str) > 5)  str[5] = '\0';   //only take 5 characters
  getchar();       //Eliminate \n left
  strcpy(a.id, str);
  //Get grade
  printf("Grade: ");
  //Check grade validation
  while(!scanf("%f", &a.grade) || a.grade < 0 || a.grade > 10) {
    //Clear the input
    while(getchar() != '\n');
    printf("Invalid grade, enter again: ");
  }
  //Evaluate level
  if (a.grade >= 9)
    a.level = 'A';
  if (8 <= a.grade && a.grade < 9)
    a.level = 'B';
  if (6.5 <= a.grade && a.grade < 8)
    a.level = 'C';
  if (a.grade < 6.5)
    a.level = 'D';
  //Done
  return a;
}

void sort (student arr[], int l) {
  int flag = 1;
  //Apply swap sort
  while (flag) {
    flag = 0;
    for (int x = 0; x < l - 1; x++) {
      if (arr[x + 1].grade > arr[x].grade) {
        student temp = arr[x];
        arr[x] = arr[x + 1];
        arr[x + 1] = temp;
        flag = 1;
      }
    }
  }
}
