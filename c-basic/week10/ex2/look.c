#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORD 20
#define TOTAL 466544
#define WORDLIST "./wordlist.dat"

void lower(char *str) {
  for (int x = 0; x < strlen(str); x++) {
    str[x] = tolower(str[x]);
  }
}

int main(int argc, char const *argv[]) {
  // Check syntax
  if (argc != 2) {
    printf("Invalid syntax, should be ./look 'word'\n");
    return -1;
  }

  // Lowercase input
  char input[WORD];
  input[0] = '\0';
  strcpy(input, argv[1]);
  lower(input);

  // Open file
  FILE *f;
  if ((f = fopen(WORDLIST, "rb")) == NULL) {
    printf("Cannot open %s\n", WORDLIST);
    return -1;
  }

  // Binary search
  int cmp, mid, oldmid = 0, low = 0, high = TOTAL - 1;
  char word[WORD];
  while (low <= high) {
      mid = (low + high) / 2;
      fseek(f, (mid - oldmid - 1) * WORD * sizeof(char), SEEK_CUR);
      fread(word, sizeof(char), WORD, f);
      lower(word);
      cmp = strcmp(input, word);
      if (cmp == 0) {
          break;
      }

      if (cmp < 0) {
          high = mid - 1;
      } else {
          low = mid + 1;
      }

      oldmid = mid;
  }

  // Not found
  if (cmp != 0) {
    printf("'%s' not found\n", argv[1]);
    return -1;
  }

  // If found, keep printing until not include or eof
  while (strstr(word, input) != NULL && !feof(f)) {
    printf("%s\n", word);
    fread(word, sizeof(char), WORD, f);
    lower(word);
  }

  // Done
  fclose(f);
  return 0;
}
