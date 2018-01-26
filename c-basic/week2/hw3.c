#include <stdio.h>

#define MAX 100

int main(int argc, char const *argv[]) {
  // Wrong syntax
  if (argc != 2) {
    printf("Invalid syntax, should be: ./hw3 'filename'\n");
    return 1;
  }

  // Try opening file
  FILE *fptr;
  if ((fptr = fopen(argv[1], "r")) == NULL) {
      printf("Cannot open '%s'\n", argv[1]);
      return 1;
  }

  // Save file content into a string
  char content[MAX], ch;
  int length;
  while ((ch = fgetc(fptr)) != EOF) {
    if ('a' <= ch && ch <= 'z') {
      ch = ch - 'a' + 'A';
    }

    content[length] = ch;
    length++;
  }

  fclose(fptr);

  // Open that file again
  if ((fptr = fopen(argv[1], "w")) == NULL) {
      printf("Cannot open '%s'\n", argv[1]);
      return 1;
  }

  // Write all character in saved string into this file
  for (int x = 0; x < length; x++) fputc(content[x], fptr);

  // Done
  printf("Transformation complete\n");
  fclose(fptr);

  return 0;
}
