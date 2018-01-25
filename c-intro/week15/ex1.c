                //Exercise 1: date

#include <stdio.h>
#include <stdlib.h>

//Date structure
typedef struct date {
  int day, month, year;
} Date;

//Supporting function
Date inputDate ();                   //Input date
int isLeapYear (int y);              //Check leap year
int validate (int d, int m, int y);  //Check date validation
int datecmp (Date a, Date b);        //Compare 2 date

//MAIN PROGRAM

int main(int argc, char const *argv[]) {
  system("clear");
  printf("\t\tEx1: Date\n");
  //Ask for input
  printf("\n- Date 1:");
  Date a = inputDate();
  printf("\n- Date 2:");
  Date b = inputDate();
  //Print date comparision
  printf("\n%d/%d/%d is", a.day, a.month, a.year);
  switch (datecmp(a, b)) {
    case -1:
      printf(" before ");
      break;
    case 0:
      printf(" indentical to ");
      break;
    case 1:
      printf(" after ");
      break;
  }
  printf("%d/%d/%d\n\n", b.day, b.month, b.year);

  printf("\n");
  return 0;
}


//FUNCTIONS

Date inputDate () {
  Date d;
  printf("\nEnter date in format dd/mm/yyyy: ");
  while (1) {
    if (!scanf("%d/%d/%d", &d.day, &d.month, &d.year)) {
      //Clear input
      while(getchar() != '\n');
      printf("Invalid input, try again: ");
    }
    else if (!validate(d.day, d.month, d.year)) {
      printf("That date is impossible, try again: ");
      //Clear input
      while(getchar() != '\n');
    }
    else break;
  }
  //clear input
  while(getchar() != '\n');
  return d;
}

int isLeapYear (int y) {
  return (y % 400) ? (!(y % 4) && (y % 100)) : 1;
}

int validate (int d, int m, int y) {
  if (d < 0 || y < 0) return 0;
  switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      return (d <= 31);
    case 4: case 6: case 9: case 11:
      return (d <= 30);
    case 2:
      return isLeapYear(y) ? (d <= 29) : (d <= 28);
    default:
      return 0;
  }
}

int datecmp (Date a, Date b) {
  if (a.year == b.year) {
    if (a.month == b.month) {
      if (a.day == b.day) {
        return 0;
      }
      else return (a.day > b.day) ? 1 : -1;
    }
    else return (a.month > b.month) ? 1 : -1;
  }
  else return (a.year > b.year) ? 1 : -1;
}
