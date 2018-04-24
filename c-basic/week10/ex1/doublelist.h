#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PAGE 25
#define MAX_LINE 80
#define DIV '|'

// Supporting functions
void wait() {
    printf("\nEnter anything to return to menu: ");
    getchar();
}

typedef struct {
    char model[30];
    int memory;
    float size;
    int price;
    int count;
} element;

typedef struct node {
    element data;
    struct node *prev;
    struct node *next;
} node;

typedef struct {
    node *root;
    node *tail;
    node *now;
} doublelist;

int isEmpty(doublelist *list) {
    return list->root == NULL;
}

void movePtrByIndex(int index, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (index < 0) {
      *now = *tail;
      for (int x = -1; x > index; x--) {
          *now = (*now)->prev;
          if ((*now)->prev == NULL) break;
      }
    } else {
      *now = *root;
      for (int x = 0; x < index; x++) {
          *now = (*now)->next;
          if ((*now)->next == NULL) break;
      }
    }
}

void movePtrByData(char *model, doublelist *list) {
  node **root = &list->root;
  node **now = &list->now;

  if (*root == NULL) return;
  for (*now = *root; *now != NULL; *now = (*now)->next) {
      if (strcmp((*now)->data.model, model) == 0) break;
  }
}

element newElement() {
    element data;
    printf("Model: ");
    scanf("%[^\n]", data.model);
    printf("Memory: ");
    scanf("%d", &data.memory);
    printf("Size: ");
    scanf("%f", &data.size);
    printf("Price: ");
    scanf("%d", &data.price);
    getchar();
    return data;
}

node *newNode(element data, int count) {
    node *new = (node *) malloc(sizeof(node));
    data.count = count;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insertAtTail(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (*root == NULL) {
        *root = new;
        *now = *root;
        *tail = *root;
    } else {
        (*tail)->next = new;
        new->prev = *tail;
        *tail = new;
    }
}

void insertAtHead(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (*root == NULL) {
        *root = new;
        *now = *root;
        *tail = *root;
    } else {
        new->next = *root;
        (*root)->prev = new;
        *root = new;
    }
}

void insertAfter(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (*root == NULL) {
        *root = new;
        *now = *root;
        *tail = *root;
    } else if (*now == *tail) {
        insertAtTail(new, list);
        *now = *tail;
    } else {
        new->next = (*now)->next;
        new->prev = *now;
        (*now)->next->prev = new;
        (*now)->next = new;
        *now = (*now)->next;
    }
}

void insertBefore(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (*root == NULL) {
        *root = new;
        *now = *root;
        *tail = *root;
    } else if (*now == *root) {
        insertAtHead(new, list);
        *now = *root;
    } else {
        new->next = *now;
        new->prev = (*now)->prev;
        (*now)->prev->next = new;
        (*now)->prev = new;
        *now = (*now)->prev;
    }
}

void insertByIndex(doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    if (index == 0) {
        insertAtHead(newNode(newElement(), 0), list);
    } else {
        if (index > 0) { index -= 1; }
        movePtrByIndex(index, list);
        insertAfter(newNode(newElement(), 0), list);
    }
}

void deleteNode(doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;
    node **tail = &list->tail;

    if (*now == *root && *now == *tail) {
      *root = *tail = NULL;
      free(*now);
    } else if (*now == *root) {
        *root = (*root)->next;
        free(*now);
    } else if (*now == *tail) {
        *tail = (*tail)->prev;
        free(*now);
    } else {
        (*now)->prev->next = (*now)->next;
        if ((*now)->next != NULL) {
          (*now)->next->prev = (*now)->prev;
        }

        free(*now);
    }

    *now = *root;
}

void deleteFirst(doublelist *list) {
    movePtrByIndex(0, list);
    deleteNode(list);
}

void deleteLast(doublelist *list) {
    movePtrByIndex(-1, list);
    deleteNode(list);
}

void deleteList(doublelist *list) {
    node **root = &list->root;
    while (*root != NULL) {
        deleteFirst(list);
    }
}

void printNode(node *cur) {
    printf(
        "%d - %-30s\t%d GB\t%.2f\"\t%.d VND\n",
        cur->data.count, cur->data.model, cur->data.memory,
        cur->data.size, cur->data.price
        );
}

void printListFromRoot(doublelist *list) {
    node **root = &list->root;
    int page = 0;
    for (node *cur = *root; cur != NULL; cur = cur->next) {
        printNode(cur);
        page++;
        if (page >= PAGE) {
            printf("\n(Press ENTER to see next page)\n");
            getchar();
            system("clear");
            page = 0;
        }
    }
}

void printListFromTail(doublelist *list) {
    node **tail = &list->tail;
    int page = 0;
    for (node *cur = *tail; cur != NULL; cur = cur->prev) {
        printNode(cur);
        page++;
        if (page >= PAGE) {
            printf("\n(Press ENTER to see next page)\n");
            getchar();
            system("clear");
            page = 0;
        }
    }
}

element parseLine(FILE *read) {
  element data;
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (line == NULL) {
    printf("Memory allocation failed\n");
    data.price = -1;
    return data;
  }

  if (fgets(line, MAX_LINE, read) == NULL) {
    data.price = -1;
    return data;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with the string p_start
    switch (l) {
      case 0:
        strcpy(data.model, p_start);
        break;
      case 1:
        data.memory = atoi(p_start);
        break;
      case 2:
        data.size = atof(p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  data.price = atoi(p_start);

  // Done
  free(line);
  return data;
}

void importTextList(char *filename, doublelist *list) {
  FILE *f;
  if ((f = fopen(filename, "r")) == NULL) {
    printf("Cannot open %s\n", filename);
    return;
  }

  // Parse line in file to get data
  element temp;
  while (1) {
    temp = parseLine(f);

    // Break if end of file
    if (temp.price == -1) {
      break;
    }

    // Add to list
    insertAtHead(newNode(temp, 0), list);
  }

  printf("Done\n");
  fclose(f);
}

void importDatList(char *filename, doublelist *list) {
    FILE *f;
    if ((f = fopen(filename, "rb")) == NULL) {
        printf("Cannot open %s\n", filename);
        return;
    }

    element data[1];
    while (!feof(f)) {
        int n = fread(data, sizeof(element), 1, f);
        if (n != 0) insertAfter(newNode(data[0], 0), list);
    }

    fclose(f);
}

void printList(doublelist *list) {
    node **root = &list->root;

    int page = 0;
    for (node *cur = *root; cur != NULL; cur = cur->next) {
        printNode(cur);
        page++;
        if (page >= PAGE) {
            printf("\n(Press ENTER to see next page)\n");
            getchar();
            system("clear");
            page = 0;
        }
    }
}

// Bubble sort
void sortByCount(doublelist *list) {
  node **root = &list->root;
  element temp;
  int flag = 0;
  while (flag != 1) {
    flag = 1;
    for (node *cur = *root; cur != NULL; cur = cur->next) {
      if (cur->next != NULL) {
        if (cur->data.count < cur->next->data.count) {
          temp = cur->data;
          cur->data = cur->next->data;
          cur->next->data = temp;
          flag = 0;
        }
      }
    }
  }

  printf("Done\n");
}
