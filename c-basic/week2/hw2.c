#include <stdio.h>

int main(int argc, char const *argv[]) {
  // Wrong syntax
  if (argc != 3) {
    printf("Invalid syntax, should be: ./hw2 'source-file' 'new-file'\n");
    return 1;
  }

  FILE *fptr1, *fptr2;
  // Try opening and creating file
  if ((fptr1 = fopen(argv[1], "r")) == NULL) {
      printf("Cannot open source file\n");
      return 1;
  }

  if ((fptr2 = fopen(argv[2], "w+")) == NULL) {
      printf("Cannot create copy file");
      return 1;
  }

  // Get 1 char from file1 and put to file2
  char ch;
  while ((ch = fgetc(fptr1)) != EOF) {
      fputc(ch, fptr2);
  }

  // Done
  printf("Copying file success\n");
  fclose(fptr1);
  fclose(fptr2);

  return 0;
}
