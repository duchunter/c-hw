#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define SOURCE "list.txt"
#define DEST "result.txt"
#define DIV '\t'

typedef struct {
  int number;
  char *id;
  char *name;
  char *phone;
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
        stu.id = (char *) malloc((strlen(p_start) + 1) * sizeof(char));
        strcpy(stu.id, p_start);
        break;
      case 2:
        stu.name = (char *) malloc((strlen(p_start) + 1) * sizeof(char));
        strcpy(stu.name, p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  stu.phone = (char *) malloc((strlen(p_start) + 1) * sizeof(char));
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

  // Initial list
  int l = 0;
  student *list = (student *) malloc(sizeof(student));

  // Parse line in file to get data
  student temp;
  while (1) {
    temp = parseLine(src, dest);

    // Break if end of file
    if (temp.number == -1) {
      break;
    }

    // Increase length, realloc and add to list
    l++;
    list = (student *) realloc(list, l * sizeof(student));
    list[l - 1] = temp;
  }

  // Free data and close file
  for (int x = 0; x < l; x++) {
    free(list[x].id);
    free(list[x].name);
    free(list[x].phone);
  }

  free(list);
  fclose(src);
  fclose(dest);
  return 0;
}
