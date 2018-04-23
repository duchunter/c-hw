#include <stdio.h>
#include <string.h>

#define WORD 20

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Missing input or output file\n");
    return -1;
  }

  FILE *in, *out;
  if ((in = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
  }

  if ((out = fopen(argv[2], "wb+")) == NULL) {
    printf("Cannot open %s\n", argv[2]);
  }

  char word[WORD];
  while (fgets(word, WORD, in) != NULL) {
    word[strlen(word) - 1] = '\0';
    fwrite(word, sizeof(char), WORD, out);
  }

  printf("Done\n");
  fclose(in);
  fclose(out);
  return 0;
}
