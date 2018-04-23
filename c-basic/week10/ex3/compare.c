#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define WORD 20
#define MAX 30

typedef struct {
  int key;
  char word[WORD];
} element;

int parseLine(FILE *f, char divider, element *arr, int *l) {
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (fgets(line, MAX_LINE, f) == NULL) {
    return 0;
  }

  element newElement;
  newElement.word[0] = '\0';
  int x = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, divider)) != NULL) {
    *p_end = '\0';

    // Do sth with that string
    newElement.key = atoi(p_start);
    x++;
    p_start = p_end + 1;
  }

  // Do sth with that string
  strcpy(newElement.word, p_start);
  x++;

  arr[*l] = newElement;
  *l += 1;
  free(line);
  return x;
}

void sort(element *arr, int l){
  int flag = 0;
  element temp;
  while (flag != 1) {
    flag = 1;
    for (int x = 1; x < l; x++) {
      if (arr[x - 1].key > arr[x].key) {
        temp = arr[x];
        arr[x] = arr[x - 1];
        arr[x - 1] = temp;
        flag = 0;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Invalid syntax, should be ./compare 'list1' 'list2'\n");
    return -1;
  }

  FILE *f1, *f2;
  if ((f1 = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return - 1;
  }

  if ((f2 = fopen(argv[2], "r")) == NULL) {
    printf("Cannot open %s\n", argv[2]);
    return - 1;
  }

  element list1[MAX], list2[MAX];
  int l1, l2;
  l1 = l2 = 0;
  while (parseLine(f1, '-', list1, &l1) != 0);
  while (parseLine(f2, '-', list2, &l2) != 0);

  fclose(f1);
  fclose(f2);

  sort(list1, l1);
  sort(list2, l2);

  int i, j;
  i = j = 0;
  while (i < l1 && j < l2) {
    if (list1[i].key < list2[j].key) {
      printf("%d is not in list 2\n", list1[i].key);
      i++;
    } else if (list1[i].key == list2[j].key) {
      if (strcmp(list1[i].word, list2[j].word) != 0) {
        printf("Same key %d but different value\n", list1[i].key);
      }
      
      i++;
      j++;
    } else {
      printf("%d is not in list 1\n", list2[j].key);
      j++;
    }
  }

  for (; i < l1; i++) {
    printf("%d is not in list 2\n", list1[i].key);
  }

  for (; j < l2; j++) {
    printf("%d is not in list 1\n", list2[j].key);
  }

  return 0;
}
