#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *subStr(const char *str, int offset, int length) {
  int remaining = strlen(str) - offset;

  // Validate params
  if (offset > strlen(str) || length <= 0) return "(empty)";
  if (offset < 0) offset = 0;
  if (length > remaining) length = remaining;

  char *sub = (char *) malloc(length * sizeof(char));
  // Check if malloc failed
  if (sub == NULL) {
    printf("Memory allocation failed\n");
    return "(empty)";
  }

  strcpy(sub, str + offset);
  sub[length] = '\0';

  return sub;
}

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("Invalid syntax, should be: ./subStr |str| |offset| |number|\n");
    return 1;
  }

  printf("Result: '%s'\n", subStr(argv[1], atoi(argv[2]), atoi(argv[3])));

  return 0;
}
