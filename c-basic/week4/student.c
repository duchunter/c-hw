#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define SOURCE "list.txt"
#define DEST "result.txt"
#define DIV '\t'

typedef struct {
  int number;
  char id[30];
  char name[30];
  char phone[30];
  float mark;
} student;

student parseLine(FILE *read, FILE *write) {
  student stu;
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (fgets(line, MAX_LINE, read) == NULL) {
    stu.number = -1;
    return stu;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with the string p_start
    switch (l) {
      case 0:
        stu.number = atoi(p_start);
        break;
      case 1:
        strcpy(stu.id, p_start);
        break;
      case 2:
        strcpy(stu.name, p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  strcpy(stu.phone, p_start);

  // Input mark
  printf("%d - %s - Mark: ", stu.number, stu.name);
  scanf("%f", &stu.mark);

  // Write to destination file
  fprintf(
    write,
    "%d%c%s%c%s%c%s%c%.2f\n",
    stu.number, DIV, stu.id, DIV, stu.name, DIV, stu.phone, DIV, stu.mark
  );

  free(line);
  return stu;
}


int main(int argc, char const *argv[]) {
  // Open file
  FILE *src, *dest;
  if ((src = fopen(SOURCE, "r")) == NULL) {
    printf("Cannot open %s\n", SOURCE);
    return 1;
  }

  if ((dest = fopen(DEST, "w+")) == NULL) {
    printf("Cannot create %s\n", DEST);
    return 1;
  }

  while (parseLine(src, dest).number != -1);

  fclose(src);
  fclose(dest);
  return 0;
}
