#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int n;
int l = 0;

typedef struct node {
  int first;
  int second;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *now;
  node *prev;
} linkedList;

node *newNode(int first, int second) {
  node *new = (node *) malloc(sizeof(node));
  new->first = first;
  new->second = second;
  new->next = NULL;
  return new;
}

void addHead(linkedList *list, node *new) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  new->next = *root;
  *root = new;
  *now = *root;
  *prev = *root;
}

void delNode(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*root == NULL) {
    printf("Nothing to delete\n");
    return;
  }

  if (*now == *root) {
    *root = (*root)->next;
    //free(*now);
    *now = NULL;
    *now = *root;
    *prev = *root;
  } else {
    (*prev)->next = (*now)->next;
    //free(*now);
    *now = NULL;
    *now = (*prev)->next;
  }
}

void printList(linkedList *list) {
  printf("* List:\n");
  node **root = &list->root;
  for (node *cur = *root; cur != NULL; cur = cur->next) {
    printf("%d/%d\n", cur->first, cur->second);
  }
}

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

void purge(linkedList *list, node *new) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  *now = *root;
  *prev = *root;
  while (*now != NULL) {
    if (new->first > (*now)->first && new->second > (*now)->second) {
      delNode(list);
      l -= 1;
    }

    else if (new->first < (*now)->first && new->second < (*now)->second) {
      return;
    }

    else {
      *now = (*now)->next;
      if ((*prev)->next != *now) {
        *prev = (*prev)->next;
      }
    }
  }

  addHead(list, new);
  l += 1;
}

int main(int argc, char const *argv[]) {
  linkedList list;
  list.root = list.now = list.prev = NULL;

  int x, a, b;
  scanf("%d", &n);

  for (x = 0; x < n; x++) {
    scanf("%d %d", &a, &b);
    purge(&list, newNode(a, b));
  }

  //printList(&list);
  delList(&list);
  printf("Total: %d\n", l);
  return 0;
}
