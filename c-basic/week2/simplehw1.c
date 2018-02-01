#include <stdio.h>
#include <string.h>

void replace(char *new, const char *str, const char *a, const char *b) {
  for (int x = 0; x < strlen(str); x++) {
    int isEqual = 1;

    // If a char in str = first char of a --> it can be a
    if (*(str + x) == *a) {
      // Check others char to firgure out
      for (int y = 1; y < strlen(a); y++) {
        // If it's not a, print that char
        if (*(str + x + y) != *(a + y)) {
          isEqual = 0;
          printf("%c", *(str + x));
          break;
        }
      }

      //If it's a, print b and move pointer up corr to a
      if (isEqual) {
        printf("%s", b);
        x += strlen(a) - 1;
      }

    } else {
      // No sign of a, print that char
      printf("%c", *(str + x));
    }
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("Invalid syntax, shouldbe: ./hw1 'string' 'string' 'string'\n");
    return 1;
  }

  char str[100];
  replace(str, argv[1], argv[2], argv[3]);
  printf("\n");

  return 0;
}
