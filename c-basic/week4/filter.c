#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORBIDEN "badwords.txt"
#define DIV ','
#define MAX_LINE 80

int parseLine(FILE *f, char **words, int l) {
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (fgets(line, MAX_LINE, f) == NULL) {
    return 0;
  }

  int n = l;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with that string
    words = realloc(words, (n + 1) * sizeof(char *));
    words[n] = (char *) malloc((strlen(p_start) + 1) * sizeof(char));
    strcpy(words[n], p_start);
    n++;
    p_start = p_end + 1;
  }

  // Do sth with that string
  *(p_start + strlen(p_start) - 1) = '\0';
  words = realloc(words, (n + 1) * sizeof(char *));
  words[n] = (char *) malloc((strlen(p_start) + 1) * sizeof(char));
  strcpy(words[n], p_start);
  n++;

  free(line);
  return n;
}

void replace(char *line, char *word, char hide) {
  char *ptr = NULL;
  while ((ptr = strstr(line, word)) != NULL) {
    for (int x = 0; x < strlen(word); x++) {
      *(ptr + x) = hide;
    }
  }
}

int main(int argc, char const *argv[]) {
  // Check syntax
  if (argc != 3) {
    printf("%d\n", argc);
    printf("Invalid syntax, should be ./filter 'filename' 'character'\n");
    return 1;
  }

  // Openfile
  FILE *src, *badfile;
  if ((src = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 1;
  }

  if ((badfile = fopen(FORBIDEN, "r")) == NULL) {
    printf("Cannot open %s\n", FORBIDEN);
    return 1;
  }

  // Import words
  char **words = (char **) malloc(sizeof(char *));
  int l = 0;
  while (1) {
    int n = parseLine(badfile, words, l);
    if (n == 0) break;
    l += n;
  }

  fclose(badfile);

  // Replace word
  char line[MAX_LINE];
  while (fgets(line, MAX_LINE, src) != NULL) {
    for (int x = 0; x < l - 1; x++) {
      replace(line, words[x], argv[2][0]);
    }

    printf("%s", line);
  }

  fclose(src);
  return 0;
}
