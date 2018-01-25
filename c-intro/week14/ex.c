#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 50    //Define max string's length

// Suporting function
void clearInput ();
void wait ();    //Wait for input to continue
int mustBeInt ();   //Force input to be int
//Check if string b exist in the first l characters of string a
int inString (char *a, char *b, int l);

//Exercise's functions
int countSpace (char *str);    //Ex1 count space
void replace (char *str, char a, char b);   //Ex2 replace character
int strend (char *str1, char *str2);   //Ex5 strend()

//Still execise's function but not required
int checkFormat (char *str); //ex3 checking format


                    // MAIN PROGRAM  //
int main() {
  int choice, count;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tHOMEWORK 12\n\n");
    printf("1. Count spaces\n");
    printf("2. Replace character\n");
    printf("3. Check format\n");
    printf("4. Print first name\n");
    printf("5. strend(s,t)\n");
    printf("6. Product lookup\n");
    printf("\n0. Exit\n");
    printf("\nEnter your choice (0-6): ");
    //Choose option and start
    choice = mustBeInt(0);
    getchar();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        printf("\t1. Count spaces\n\n");
        printf("(New line will not be counted)\n");
        char str1[MAX];
        printf("Enter a string: ");
        fgets(str1, MAX, stdin);
        printf("\nThere are (is) %d space(s)\n", countSpace(str1) - 1); //Minus \n
        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\t2. Replace character\n\n");
        char str2[MAX], a, b;
        printf("Enter a string: ");
        fgets(str2, MAX, stdin);
        printf("Enter the letter you want to be replaced: ");
        a = getchar();    //Just take 1 character
        clearInput();    //To clear any leftover, include \n
        printf("Enter the letter you want to replace: ");
        b = getchar();
        clearInput();   //To clear any leftover, include \n
        replace(str2, a, b);
        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\t3. Check format (LLLNNNN)\n\n");
        char str3[MAX];
        printf("Enter id: ");
        fgets(str3, MAX, stdin);
        if (checkFormat(str3))
          printf("\nThis id is valid\n");
        else
          printf("\nThis id is invalid\n");
        //Done
        wait();
        break;

      //EX 4
      case 4:
        system("clear");
        printf("\t4. Print first name\n\n");
        char str4[MAX];
        printf("Enter a full name: ");
        fgets(str4, MAX, stdin);
        count = 0;
        //Set \0 to the first space to cut off everything from firstname
        while (str4[count] != '\0') {
          if(isspace(str4[count])) str4[count] = '\0';
          count++;
        }
        printf("\nFirst name is: %s\n", str4);
        //Done
        wait();
        break;

      //EX 5
      case 5:
        system("clear");
        printf("\t5. strend(s,t)\n\n");
        char str5a[MAX], str5b[MAX];
        printf("Enter string A: ");
        fgets(str5a, MAX, stdin);
        printf("Enter string B: ");
        fgets(str5b, MAX, stdin);
        printf("\nstrend(A, B) return %d\n", strend(str5a, str5b));
        //Done
        wait();
        break;

      //EX 6
      case 6:
        system("clear");
        printf("\t6. Product lookup\n\n");
        //Create the list
        char str6[MAX], *list[] = {
          "TV127  31 inch Television",
          "CD057  CD Player",
          "TA877  Answering Machine",
          "CS409  Car Stereo",
          "PC655  Personal Computer"
        };
        printf("Enter product number (full or partial): ");
        fgets(str6, MAX, stdin);
        printf("\nWe have:\n\n");
        int flag = 0;    //In case of no result found
        for (count = 0; count < 5; count++) {   //Change max value if number of product change
          if (inString(list[count], str6, 5)) {  //only check the ID, which length = 5
            printf("%s\n", list[count]);
            flag = 1;
          }
        }
        if (!flag) printf("\tNo result found\n");
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  system("clear");
  return 0;
}

                  // SUPPORTING FUNCTION

//Clear input
void clearInput () {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}
//Wait for input to continue
void wait () {
  printf("\nEnter anything to return to menu: ");
  //Wait for user to enter anything
  getchar();
}
//Force input value to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n)) {
    clearInput();
    printf("Invalid input, enter again: ");
  }
  return n;
}
//Check if string b exist in the first l character of string a
int inString (char *a, char *b, int l) {
  for (int x = 0; x < l; x++) {
    if (a[x] == b[0]) {
      for (int y = 1; y < strlen(b) - 1; y++) { //strlen - 1 to not check \n
        if (a[x + y] != b[y]) return 0;
      }
      return 1;
    }
  }
  return 0;
}
                //EXERCISE REQUIRED FUNCTIONS

//Ex1 count space
int countSpace (char *str) {
  int x = 0, count = 0;
  while (str[x] != '\0') {
    if (isspace(str[x])) count++;
    x++;
  }
  return count;
}
//Ex2 replace character
void replace (char *str, char a, char b) {
  printf("\nReplacing %c by %c...\n", a, b);
  int x = 0;
  while (str[x] != '\0') {
    if (str[x] == a) str[x] = b;
    x++;
  }
  printf("\nNew string is: %s\n", str);
}
//Ex5 strend()
int strend (char *str1, char *str2) {
  int x = strlen(str1), y = strlen(str2);
  return (x < y) ? 0 : !strcmp(str1 + x - y, str2);
}

            //NOT REQUIRED

//ex3 check checkFormat
int checkFormat (char *str) {
  int x;
  if (strlen(str) != 8) return 0; //7 character + \n
  for (x = 0; x < 3; x++) {
    if (!isalpha(str[x])) return 0;
  }
  for (x = 3; x < 7; x++) {
    if (!isdigit(str[x])) return 0;
  }
  return 1;
}
