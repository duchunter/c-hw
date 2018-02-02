#include <stdio.h>
#include <ctype.h>

enum { START = 33, END = 126 };

void count(FILE *target, int *arr) {
  char ch;
  while ((ch = fgetc(target)) != EOF) {
    if (START <= ch && ch <= END) {
      if (isupper(ch)) ch = tolower(ch);
      arr[ch - START]++;
    }
  }
}

int main(int argc, char const *argv[]) {
  // Invalid syntax
  if (argc != 2) {
    printf("Missing target file\n");
    return 1;
  }

  // Open target file
  FILE *target;
  if ((target = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open '%s'\n", argv[1]);
    return 1;
  }

  // Open result file
  FILE *result;
  if ((result = fopen("stat.txt", "w+")) == NULL) {
    printf("Cannot create '%s'\n", "stat.txt");
    return 1;
  }

  // Count and save result in an array
  int arr[END- START] = {0};
  count(target, arr);

  // Print result and save to stat.txt
  for (int x = 0; x < END - START; x++) {
    if (arr[x] != 0) {
      printf("%c appears %d time(s)\n", x + START, arr[x]);
      fprintf(result, "%c appears %d time(s)\n", x + START, arr[x]);
    }
  }

  // Done
  printf("\nResult saved in '%s'\n", "stat.txt");
  fclose(target);
  fclose(result);
  return 0;
}
