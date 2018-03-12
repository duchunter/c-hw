#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOURCE "dict.txt"
#define DEST "dict.dat"
#define MAX_LINE 120
#define BLOCK 10
#define PAGE 25

// SUPPORTING FUNCTIONS

//fflush
void clear () {
  while(getchar() != '\n');
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
    clear();
    printf("Invalid input, enter again: ");
  }

  return n;
}

// Text to dat
void text2dat() {
  FILE *src, *dest;
  if ((src = fopen(SOURCE, "r")) == NULL) {
    printf("Cannot open %s\n", SOURCE);
    return;
  }

  if ((dest = fopen(DEST, "w+b")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  char list[1][MAX_LINE];
  char line[MAX_LINE];

  // Parse line in file to get data
  while (fgets(line, MAX_LINE, src) != NULL) {
    strcpy(list[0], line);

    // Write to dest file
    fwrite(list, MAX_LINE * sizeof(char), 1, dest);
  }

  printf("\n%s created\n", DEST);
  fclose(src);
  fclose(dest);
}

// Read .dat file
void readDat() {
  // Open file
  FILE *f;
  if ((f = fopen(DEST, "rb")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  // Choose print mode
  int start, end, x, num, page = 0;
  printf("- Start from: ");
  start = mustBeInt();
  printf("- To: ");
  end = mustBeInt();
  getchar();

  fseek(f, (start - 1) * MAX_LINE * sizeof(char), SEEK_SET);
  int range = end - start + 1;

  char list[range][MAX_LINE];

  num = fread(list, MAX_LINE * sizeof(char), range, f);
  for (x = 0; x < num; x++) {
    printf("%s", list[x]);
    page++;
    if (page >= PAGE) {
      printf("(Press ENTER to see next page)\n");
      getchar();
      system("clear");
      page = 0;
    }
  }

  fclose(f);
}

// MAIN
int main(int argc, char const *argv[]) {
  int choice;
  do {
    //Clear screen
    system("clear");

    //Display menu
    printf("\t\tPhone\n\n");
    printf("1. Text to .dat\n");
    printf("2. Read from dictionary\n");
    printf("\n0. Exit\n");

    //Choose option and start
    printf("\nEnter your choice (0-2): ");
    choice = mustBeInt();
    getchar();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        printf("\tText to .dat\n\n");
        text2dat();
        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\tRead from dictionary\n\n");
        readDat();
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  //Everything done
  system("clear");
  return 0;
}
