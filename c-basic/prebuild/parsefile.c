#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80

int parseLine(FILE *f, char divider) {
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (fgets(line, MAX_LINE, f) == NULL) {
    return 0;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, divider)) != NULL) {
    *p_end = '\0';

    // Do sth with that string
    printf("%d: %s\n", l, p_start);
    l++;
    p_start = p_end + 1;
  }

  // Do sth with that string
  printf("%d: %s\n", l, p_start);
  l++;

  free(line);
  return l;
}

int main(int argc, char const *argv[]) {
  FILE *f = fopen("list.txt", "r");
  while (parseLine(f, '-') != 0);

  fclose(f);
  return 0;
}
