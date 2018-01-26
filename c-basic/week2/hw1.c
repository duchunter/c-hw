#include <stdio.h>
#include <string.h>

void replace(char *new, const char *str, const char *a, const char *b) {
  int length = 0, isEqual;
  for (int x = 0; x < strlen(str); x++) {
    isEqual = 1;

    // If a char in str = first char of a --> it can be a
    if (*(str + x) == *a) {
      // Check others char to firgure out
      for (int y = 1; y < strlen(a); y++) {
        // If it's not a, treat it like normal char
        if (*(str + x + y) != *(a + y)) {
          isEqual = 0;
          *(new + length) = *(str + x);
          length++;
          break;
        }
      }

      /**
       * If it's a, transform new into a string instead of a pointer
       * and strcat b into it, increase length corr to b and move
       * str pointer up corr to a
      */
      if (isEqual) {
        *(new + length) = '\0';
        strcat(new, b);
        length += strlen(b);
        x += strlen(a) - 1;
      }

    } else {
      // No sign of a, treat like normal char
      *(new + length) = *(str + x);
      length++;
    }
  }

  *(new + length) = '\0';
}

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("Invalid syntax, shouldbe: ./hw1 'string' 'string' 'string'\n");
    return 1;
  }

  char str[100];
  replace(str, argv[1], argv[2], argv[3]);
  printf("New string: %s\n", str);

  return 0;
}
