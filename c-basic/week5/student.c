#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOURCE "result.txt"
#define DEST "grade.dat"
#define MAX_LINE 80
#define DIV '\t'
#define BLOCK 10

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

typedef struct {
  int number;
  char id[10];
  char name[30];
  char phone[20];
  float mark;
} student;

student parseLine(FILE *read) {
  student stu;
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (line == NULL) {
    printf("Memory allocation failed\n");
    return stu;
  }

  if (fgets(line, MAX_LINE, read) == NULL) {
    stu.number = -1;
    return stu;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with the string p_start
    switch (l) {
      case 0:
        stu.number = atoi(p_start);
        break;
      case 1:
        strcpy(stu.id, p_start);
        break;
      case 2:
        strcpy(stu.name, p_start);
        break;
      case 3:
        strcpy(stu.phone, p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  stu.mark = atof(p_start);

  // Done
  free(line);
  return stu;
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

  int l = 0;
  student *list = (student *) malloc(sizeof(student));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  // Parse line in file to get data
  student temp;
  while (1) {
    temp = parseLine(src);

    // Break if end of file
    if (temp.number == -1) {
      break;
    }

    // Increase length, realloc and add to list
    l++;
    list = (student *) realloc(list, l * sizeof(student));
    if (list == NULL) {
      printf("Memory reallocation failed\n");
      return;
    }

    list[l - 1] = temp;
  }

  for (int x = 0; x < l; x++) {
    printf(
      "%d\t%s\t%s\t%s\t%.2f\n",
      list[x].number, list[x].id, list[x].name, list[x].phone, list[x].mark
    );
  }

  // Write to dest file
  fwrite(list, sizeof(student), l, dest);
  printf("\n%s created\n", DEST);

  free(list);
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

  student *list = (student *) malloc(BLOCK * sizeof(student));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  while (!feof(f)) {
    int num = fread(list, sizeof(student), BLOCK, f);
    for (int x = 0; x < num; x++) {
      printf(
        "%d\t%s\t%s\t%s\t%.2f\n",
        list[x].number, list[x].id, list[x].name, list[x].phone, list[x].mark
      );
    }
  }

  free(list);
  fclose(f);
}

// Search and update
void update() {
  char id[10];
  printf("Enter student id: ");
  scanf("%s", id);
  getchar();

  // Open file
  FILE *f;
  if ((f = fopen(DEST, "r+b")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  student *list = (student *) malloc(BLOCK * sizeof(student));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  while (!feof(f)) {
    int num = fread(list, sizeof(student), BLOCK, f);
    for (int x = 0; x < num; x++) {
      if (strcmp(id, list[x].id) == 0) {
        printf("Found:\n");
        printf(
          "- %d\t%s\t%s\t%s\t%.2f\n",
          list[x].number, list[x].id, list[x].name, list[x].phone, list[x].mark
        );
        printf("Enter new mark: ");
        scanf("%f", &list[x].mark);
        getchar();

        // Move file pointer to corresponding position to write
        fseek(f, (x - num) * sizeof(student), SEEK_CUR);
        fwrite(&list[x], sizeof(student), 1, f);

        // Done
        printf("Done\n");
        free(list);
        fclose(f);
        return;
      }
    }
  }

  printf("No student found\n");
  free(list);
  fclose(f);
}

// MAIN
int main(int argc, char const *argv[]) {
  int choice;
  do {
    //Clear screen
    system("clear");

    //Display menu
    printf("\t\tStudent list\n\n");
    printf("1. Text to .dat\n");
    printf("2. Display .dat file\n");
    printf("3. Search and update\n");
    printf("\n0. Exit\n");

    //Choose option and start
    printf("\nEnter your choice (0-3): ");
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
        printf("\tDisplay .dat file\n\n");
        readDat();
        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\tSearch and update\n\n");
        update();
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  //Everything done
  system("clear");
  return 0;
}
