#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
  // Wrong syntax
  if (argc != 2) {
    printf("Invalid syntax, should be: ./transform 'filename'\n");
    return 1;
  }

  // Try opening file
  FILE *fptr;
  if ((fptr = fopen(argv[1], "r+")) == NULL) {
      printf("Cannot open '%s'\n", argv[1]);
      return 1;
  }

  // For each lowercase met, move pointer back one char and write new char
  char ch;
  while ((ch = fgetc(fptr)) != EOF) {
    if (islower(ch)) {
      fseek(fptr, -1, SEEK_CUR);
      fputc(toupper(ch), fptr);
    }
  }

  // Done
  printf("Transformation complete\n");
  fclose(fptr);

  return 0;
}
