#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  LINE = 80
};

char *sourceFile = "list.txt";
char *resultFile = "result.txt";

typedef struct {
  int number;
  char id[30];
  char name[30];
  char phone[30];
  double grade;
} student;

void getData(char *str, char *target) {
  printf("str: %s\n", str);
  char *ptr = strchr(str, '|');
  printf("ptr: %s\n", ptr);
  int length = ptr - str;
  strncpy(target, str, length);
  printf("target: %s\n", target);
}

int main(int argc, char const *argv[]) {
  // Open file
  FILE *source, *result;
  if ((source = fopen(sourceFile, "r")) == NULL) {
    printf("Cannot open %s\n", sourceFile);
    return 1;
  }

  if ((result = fopen(resultFile, "w+")) == NULL) {
    printf("Cannot create %s\n", resultFile);
    return 1;
  }

  // Save data into an array
  student *list = (student *) malloc(sizeof(student));
  int length = 0;
  char line[LINE + 1], data[30], *ptr;

  while (fgets(line, LINE, source) != NULL) {
    length++;
    ptr = line;

    // Get number
    getData(ptr, data);
    list[length - 1].number = atoi(data);
    ptr += strlen(data) + 1;

    // Get id
    getData(ptr, data);
    //list[length - 1].id = (char *) malloc(strlen(data) * sizeof(char));
    strcpy(list[length - 1].id, data);
    ptr += strlen(data) + 1;

    // Get name
    getData(ptr, data);
    //list[length - 1].name = (char *) malloc(strlen(data) * sizeof(char));
    strcpy(list[length - 1].name, data);
    ptr += strlen(data) + 1;

    // Get phone number
    getData(ptr, data);
    //list[length - 1].phone = (char *) malloc(strlen(data) * sizeof(char));
    strcpy(list[length - 1].phone, data);
    ptr += strlen(data) + 1;

    list = (student *) realloc(list, 1 + sizeof(student));
  }

  for (int x = 0; x < length; x++) {
    printf(
      "%d\t%s\t%s\t%s\n",
      list[x].number,
      list[x].id,
      list[x].name,
      list[x].phone
    );
  }

  fclose(source);
  fclose(result);
  free(list);
  return 0;
}
