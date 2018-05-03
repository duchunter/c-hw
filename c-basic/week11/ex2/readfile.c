#include <stdio.h>
#include <stdlib.h>

#define BLOCK 20

typedef struct {
    char name[20];
    char tel[11];
    char email[25];
} address;

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("Wrong syntax, should be ./readfile 'filename'\n");
    return 1;
  }

  FILE *f;
  if ((f = fopen(argv[1], "rb")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 1;
  }

  address *block = (address *) malloc(BLOCK * sizeof(address));
  if (block == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }
  
  while (!feof(f)) {
    int n = fread(block, sizeof(address), BLOCK, f);
    for (int x = 0; x < n; x++) {
      printf("%s - %s - %s\n", block[x].name, block[x].tel, block[x].email);
    }
  }

  fclose(f);
  free(block);
  return 0;
}
