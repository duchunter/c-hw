#include <stdio.h>
#include <stdlib.h>

#define BLOCK 20

typedef struct {
    char name[20];
    char tel[11];
    char email[25];
} address;

int main(int argc, char const *argv[]) {
  // Check syntax
  if (argc != 4) {
    printf("Syntax should be ./mergefile 'file1' 'file2' 'dest'\n");
    return 1;
  }

  // Open files
  FILE *dest, *f1, *f2;
  if ((dest = fopen(argv[3], "w+b")) == NULL) {
    printf("Cannot create %s\n", argv[3]);
    return 1;
  }

  if ((f1 = fopen(argv[1], "rb")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 1;
  }

  if ((f2 = fopen(argv[2], "rb")) == NULL) {
    printf("Cannot open %s\n", argv[2]);
    return 1;
  }

  // Write from file 1
  address *block = (address *) malloc(BLOCK * sizeof(address));
  if (block == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  int read = fread(block, sizeof(address), BLOCK, f1);
  fwrite(block, sizeof(address), read, dest);

  // Write to file 2
  read = fread(block, sizeof(address), BLOCK, f2);
  fwrite(block, sizeof(address), read, dest);

  // Done
  printf("Done\n");
  free(block);
  fclose(dest);
  fclose(f1);
  fclose(f2);
  return 0;
}
