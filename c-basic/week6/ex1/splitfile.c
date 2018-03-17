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
  if (argc != 5) {
    printf("Syntax should be ./splitfile 'source' 'num' 'file1' 'file2'\n");
    return 1;
  }

  int num = atoi(argv[2]);
  if (num < 0) {
    printf("Number of contact should be greater than 0\n");
    return 1;
  }

  // Open files
  FILE *source, *f1, *f2;
  if ((source = fopen(argv[1], "rb")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 1;
  }

  if ((f1 = fopen(argv[3], "w+b")) == NULL) {
    printf("Cannot create %s\n", argv[3]);
    return 1;
  }

  if ((f2 = fopen(argv[4], "w+b")) == NULL) {
    printf("Cannot create %s\n", argv[4]);
    return 1;
  }

  // Write to file 1
  address *block = (address *) malloc(num * sizeof(address));
  if (block == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  int read = fread(block, sizeof(address), num, source);
  fwrite(block, sizeof(address), read, f1);

  // Write to file 2
  while (!feof(source)) {
    read = fread(block, sizeof(address), BLOCK, source);
    fwrite(block, sizeof(address), read, f2);
  }

  // Done
  printf("Done\n");
  free(block);
  fclose(source);
  fclose(f1);
  fclose(f2);
  return 0;
}
