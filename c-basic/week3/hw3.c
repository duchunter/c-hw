#include <stdio.h>
#include <string.h>

enum { MAX_LINE = 80, MAX_PAGE = 25 };

void mycat(FILE *source, int pageMode) {
  char line[MAX_LINE];
  int count = 0;
  while (fgets(line, MAX_LINE, source) != NULL) {
    printf("%s", line);
    count++;
    if (pageMode && (count % MAX_PAGE) == 0) {
      printf("(Press ENTER to see next page)\n");
      getchar();
    }
  }
}

int main(int argc, char const *argv[]) {
  // Invalid syntax
  if (argc != 2 && argc != 3) {
    printf("Invalid syntax, should be: ./mycat 'source' |-p|\n");
    return 1;
  }

  // Open source file
  FILE *source;
  if ((source = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open '%s'\n", argv[1]);
    return 1;
  }

  if (argv[2]) {
    // Page mode
    if (strcmp(argv[2], "-p") != 0) {
      printf("Invalid mode, should be -p\n");
      return 1;
    }
    mycat(source, 1);
  } else {
    // Normal mode
    mycat(source, 0);
  }

  //Done
  fclose(source);
  return 0;
}
