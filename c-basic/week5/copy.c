#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE 80

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

                        // MAIN FUNCTIONS
void copy(int mode) {
  clock_t t;
  int block, num;
  char source[20], dest[20], ch, line[LINE + 1], str[LINE];
  printf("Enter source file: ");
  scanf("%[^\n]", source);
  getchar();
  printf("Enter dest file: ");
  scanf("%[^\n]", dest);
  getchar();

  FILE *f1, *f2;
  if ((f1 = fopen(source, "r")) == NULL) {
    printf("Cannot open %s\n", source);
    return;
  }

  if ((f2 = fopen(dest, "w+")) == NULL) {
    printf("Cannot open %s\n", dest);
    return;
  }

  if (mode == 3) {
    printf("Enter block size: ");
    block = mustBeInt();
  }

  t = clock();
  switch (mode) {
    case 1:
      while ((ch = fgetc(f1)) != EOF) {
        fputc(ch, f2);
      }

      break;

    case 2:
      while (fgets(line, LINE, f1) != NULL) {
        fputs(line, f2);
      }

      break;

    case 3:
      while (!feof(f1)) {
          num = fread(str, sizeof(char), block, f1);
          fwrite(str, sizeof(char), num, f2);
      }

      break;
  }

  fclose(f1);
  fclose(f2);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("Done! Time taken: %.4lf seconds\n", time_taken);
}


                    // MAIN PROGRAM  //
int main() {
  int choice;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tCopy file\n\n");
    printf("1. By character\n");
    printf("2. By line\n");
    printf("3. By block\n");
    printf("\n0. Exit\n");
    //Variables for all exercise that must be reset

    //Choose option and start
    printf("\nEnter your choice (0-3): ");
    choice = mustBeInt();
    getchar();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        printf("\tBy character\n\n");
        copy(1);
        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\tBy line\n\n");
        copy(2);
        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\tBy block\n\n");
        copy(3);
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  //Everything done
  system("clear");
  return 0;
}
