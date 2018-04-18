#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int memory;
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

int mustBeInt() {
  int n;
  while(!scanf("%d", &n) || n < 0) {
    while(getchar() != '\n');
    printf("Invalid input, enter again: ");
  }

  getchar();
  return n;
}

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

element newElement() {
    element data;
    printf("ID: ");
    data.id = mustBeInt();
    printf("Memory: ");
    data.memory = mustBeInt();
    return data;
}

node *newNode(element data) {
    node *new = (node *) malloc(sizeof(node));
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

element deleteFirst(doublelist *list) {
    movePtrByIndex(0, list);
    element data = list->now->data;
    deleteNode(list);
    return data;
}

void deleteList(doublelist *list) {
    node **root = &list->root;
    while (*root != NULL) {
        deleteFirst(list);
    }
}

void enqueue(element data, doublelist *q) {
    insertAtTail(newNode(data), q);
}

element dequeue(doublelist *q) {
    return deleteFirst(q);
}

element head(doublelist *q) {
  return q->root->data;
}

element tail(doublelist *q) {
  return q->tail->data;
}
