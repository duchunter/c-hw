#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT "phone.txt"
#define DAT "phone.dat"
#define OUTPUT "phoneDB.dat"
#define MAX_LINE 80
#define DIV '|'
#define BLOCK 10
#define PAGE 25

// Supporting functions
void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

// Initial data
typedef struct {
  char model[30];
  int memory;
  float size;
  int price;
  int count;
} element;

typedef struct node {
  element data;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *now;
  node *prev;
} linkedList;

element getData() {
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
  data.count = 0;
  return data;
}

// Moving
void movePtrByIndex(int i, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*root == NULL) return;
  *prev = *root;
  *now = *root;
  for (int x = 0; x != i; x++) {
    if ((*now)->next == NULL) break;
    *now = (*now)->next;
    if ((*prev)->next != *now) *prev = (*prev)->next;
  }
}

void movePtrByData(char *model, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*root == NULL) return;
  *prev = *root;
  for (*now = *root; *now != NULL; *now = (*now)->next) {
      if (strcmp((*now)->data.model, model) == 0) break;
      *prev = *now;
  }
}

// Adding
node *newNode(element data, int count) {
  node *new = (node *) malloc(sizeof(node));
  data.count = count;
  new->data = data;
  new->next = NULL;
  return new;
}

void addHead(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  new->next = *root;
  *root = new;
  *now = *root;
  *prev = *root;
}

void addAfter(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;
  node *temp;

  if (*root == NULL) {
    *root = new;
    *prev = *root;
    *now = *root;

  } else {
    if (*now == NULL) {
      *now = *root;
      *prev = *root;
    }

    temp = (*now)->next;
    (*now)->next = new;
    new->next = temp;
    *prev = *now;
    *now = new;
  }
}

void addBefore(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*now == *prev) {
    addHead(new, list);
    *now = *root;
    *prev = *root;

  } else {
    (*prev)->next = new;
    new->next = *now;
    *now = new;
  }
}

void insertAt(int i, linkedList *list) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  if (i == 0) {
    addHead(newNode(getData(), 0), list);
  } else {
    movePtrByIndex(i - 1, list);
    addAfter(newNode(getData(), 0), list);
  }
}

// Printing
void printNode(node *cur) {
  printf(
    "%d - %-30s\t%d GB\t%.2f\"\t%.d VND\n",
    cur->data.count, cur->data.model, cur->data.memory,
    cur->data.size, cur->data.price
  );
}

void printList(linkedList *list) {
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

void printNodeByData(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  char model[30];
  printf("Enter model: ");
  scanf("%[^\n]", model);
  getchar();

  movePtrByData(model, list);
  if (*now == NULL) {
      printf("No data found\n");
      *now = *root;
      *prev = *root;
  } else {
      printNode(*now);
  }
}

// Deleting
void delList(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  for (node *cur = *root; cur != NULL; cur = cur-> next) {
    free(cur);
  }

  *root = NULL;
  *now = NULL;
}

void delNode(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*now == *root) {
    *root = (*root)->next;
    free(*now);
  } else {
    (*prev)->next = (*now)->next;
    free(*now);
  }

  *now = *root;
  *prev = *root;
}

void delHead(linkedList *list) {
  movePtrByIndex(0, list);
  delNode(list);
}

void delAt(int i, linkedList *list) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  movePtrByIndex(i, list);
  delNode(list);
}

void delByData(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  char model[30];
  printf("Enter model: ");
  scanf("%[^\n]", model);
  getchar();

  movePtrByData(model, list);
  if (*now == NULL) {
      printf("No data found\n");
      *now = *root;
      *prev = *root;
  } else {
      delNode(list);
  }
}

// Sorting and mixin
void *reverseList(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  node *cur, *before;
  cur = before = NULL;
  while (*root != NULL) {
      cur = *root;
      *root = (*root)->next;
      cur->next = before;
      before = cur;
  }

  *root = before;
  printf("Done\n");
}


// File
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

void importTextList(char *filename, linkedList *list) {
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
    addHead(newNode(temp, 0), list);
  }

  printf("Done\n");
  fclose(f);
}

void importDatList(char *filename, linkedList *list) {
  delList(list);
  FILE *f;
  if ((f = fopen(filename, "rb")) == NULL) {
    printf("Cannot open %s\n", filename);
    return;
  }

  element data[1];
  while (!feof(f)) {
    int n = fread(data, sizeof(element), 1, f);
    if (n != 0) addAfter(newNode(data[0], 0), list);
  }

  fclose(f);
}

void exportDatList(char *filename, linkedList *list) {
  node **root = &list->root;

  FILE *f;
  if ((f = fopen(filename, "w+b")) == NULL) {
    printf("Cannot open %s\n", filename);
    return;
  }

  node *cur;
  for (cur = *root; cur != NULL; cur = cur->next) {
    fwrite(cur, sizeof(element), 1, f);
  }

  fclose(f);
}

void exportTextList(char *filename, linkedList *list) {
  node **root = &list->root;

  FILE *f;
  if ((f = fopen(filename, "w+")) == NULL) {
    printf("Cannot open %s\n", filename);
    return;
  }

  node *cur;
  for (cur = *root; cur != NULL; cur = cur->next) {
    fprintf(
      f,
      "%s%c%d%c%.1f%c%d\n",
      cur->data.model, DIV, cur->data.memory, DIV,
      cur->data.size, DIV, cur->data.price
    );
  }

  fclose(f);
}

// Action and export
void splitList(int n1, int n2, linkedList *list) {
  if (n1 < 0) {
    printf("Stating index must be greater than 0\n");
    wait();
    return;
  }

  node **root = &list->root;
  linkedList list1;
  list1.root = list1.now = list1.prev = NULL;

  linkedList list2;
  list2.root = list2.now = list2.prev = NULL;

  int x = 0;
  for (node *cur = *root; cur != NULL; cur = cur->next) {
    element temp = cur->data;
    if (x < n1 || x >= n1 + n2) {
      addAfter(newNode(temp, 0), &list1);
    } else {
      addAfter(newNode(temp, 0), &list2);
    }

    x++;
  }

  exportTextList("list1.txt", &list1);
  exportTextList("list2.txt", &list2);
  delList(&list1);
  delList(&list2);

  printf("Done\n");
  wait();
}

// Bubble sort
void sortByCount(linkedList *list) {
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

// MAIN
int main(int argc, char *argv[]) {
  linkedList list;
  list.root = list.now = list.prev = NULL;

  int choice, i;
  char model[30];
  element tempData;
  do {
    system("clear");
    printf("\tChoose your action:\n\n");
    printf("1. Import from dat (after)\n");
    printf("2. Print list\n3. Add new phone (before/after)\n");
    printf("4. Add at index\n5. Delete at index\n");
    printf("6. Delete current node\n7. Delete first node\n");
    printf("8. Search and update\n9. Split and export\n");
    printf("10. Reverse list\n11. Save to file\n");
    printf("12. Self organization search\n");
    printf("13. Import from text\n14. Sort by search count\n");

    printf("\n0. Exit\n\nYour choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        importDatList("phoneDB.dat", &list);
        wait();
        break;
      case 2:
        system("clear");
        printList(&list);
        wait();
        break;
      case 3:
        system("clear");
        printf("Where do you want to add?\n1. Before\n2. After\n");
        printf("\nYour choice: ");
        scanf("%d", &i);
        getchar();
        if (i == 1) {
          addBefore(newNode(getData(), 0), &list);
        } else if (i == 2) {
          addAfter(newNode(getData(), 0), &list);
        }
        else {
          printf("Invalid\n");
        }

        printf("Done\n");
        wait();
        break;
      case 4:
        system("clear");
        printf("Enter index: ");
        scanf("%d", &i);
        getchar();
        insertAt(i, &list);
        wait();
        break;
      case 5:
        system("clear");
        printf("Enter index: ");
        scanf("%d", &i);
        getchar();
        delAt(i, &list);
        wait();
        break;
      case 6:
        system("clear");
        delNode(&list);
        printf("Done\n");
        wait();
        break;
      case 7:
        system("clear");
        delHead(&list);
        printf("Done\n");
        wait();
        break;
      case 8:
        system("clear");
        printf("Enter model: ");
        scanf("%[^\n]", model);
        getchar();
        movePtrByData(model, &list);
        if (list.now == NULL) {
          list.now = list.root;
          printf("No model found\n");
        } else {
          printf("Enter new data:\n");
          element new = getData();
          list.now->data = new;
          printf("Done\n");
        }

        wait();
        break;
      case 9:
        system("clear");
        int n1, n2;
        printf("Enter starting index: ");
        scanf("%d", &n1);
        getchar();
        printf("Enter number of nodes: ");
        scanf("%d", &n2);
        getchar();
        splitList(n1, n2, &list);
        break;
      case 10:
        system("clear");
        reverseList(&list);
        wait();
        break;
      case 11:
        system("clear");
        exportDatList(OUTPUT, &list);
        printf("Done\n");
        wait();
        break;
      case 12:
          system("clear");
          printf("Enter model: ");
          scanf("%[^\n]", model);
          getchar();
          movePtrByData(model, &list);
          if (list.now == NULL) {
              printf("No model found\n");
              list.now = list.root;
          } else {
              printf("Model found, what's next?\n");
              printf("1. Move to front\n2. Transpose\n3. Search count\n");
              scanf("%d", &choice);
              getchar();
              tempData = list.now->data;
              list.now->data.count += 1;
              switch (choice) {
                case 1:
                    delNode(&list);
                    addHead(newNode(tempData, list.now->data.count), &list);
                    printf("Done\n");
                    break;
                case 2:
                    tempData = list.now->data;
                    list.now->data = list.prev->data;
                    list.prev->data = tempData;
                    printf("Done\n");
                    break;
                case 3:
                    sortByCount(&list);
                    break;
              }
          }

          wait();
          break;
      case 13:
          system("clear");
          delList(&list);
          importTextList("phone.txt", &list);
          wait();
          break;
      case 14:
          system("clear");
          sortByCount(&list);
          wait();
          break;
    }
  } while (choice != 0);

  system("clear");
  delList(&list);
  return 0;
}
