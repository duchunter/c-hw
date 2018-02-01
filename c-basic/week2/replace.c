#include <stdio.h>
#include <string.h>

void replace(const char *str, const char *a, const char *b) {
  char *existA = strstr(str, a);
  if (existA == NULL) {
    printf("%s\n", str);
  } else {
    for (char *ptr = str; ptr != existA; ptr++) printf("%c", *ptr);
    printf("%s", b);
    replace(existA + strlen(a), a, b);
  }
}

int main(int argc, char const *argv[]) {
  // Check syntax
  if (argc != 4) {
    printf("Invalid syntax, shouldbe: ./replace 'string' 'string' 'string'\n");
    return 1;
  }

  replace(argv[1], argv[2], argv[3]);

  return 0;
}
