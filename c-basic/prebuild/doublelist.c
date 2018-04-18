#include <stdio.h>
#include <stdlib.h>

#define PAGE 25

// Supporting functions
void wait() {
    printf("\nEnter anything to return to menu: ");
    getchar();
}

typedef struct {
    int val;
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

element newElement() {
    element data;
    printf("Value: ");
    scanf("%d", &data.val);
    getchar();
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
        insertAtHead(newNode(newElement()), list);
    } else {
        if (index > 0) { index -= 1; }
        movePtrByIndex(index, list);
        insertAfter(newNode(newElement()), list);
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
    printf("%d\n", cur->data.val);
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

int main(int argc, char *argv[]) {
    doublelist list;
    list.root = list.now = list->tail = NULL;
    int choice, i;
    do {
        system("clear");
        printf("\tChoose your action:\n\n");
        printf("1. Check empty\n2. Insert after\n3. Insert before\n");
        printf("4. Insert at head\n5. Insert at tail\n6. Insert at index\n");
        printf("7. Delete first\n8. Delete current\n9. Delete list\n");
        printf("10. Print list\n\n0. Exit\n\nYour choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            system("clear");
            printf("Empty: %s\n", isEmpty(&list) ? "true" : "false");
            wait();
            break;
        case 2:
            system("clear");
            insertAfter(newNode(newElement()), &list);
            wait();
            break;
        case 3:
            system("clear");
            insertBefore(newNode(newElement()), &list);
            wait();
            break;
        case 4:
            system("clear");
            insertAtHead(newNode(newElement()), &list);
            wait();
            break;
        case 5:
            system("clear");
            insertAtTail(newNode(newElement()), &list);
            wait();
            break;
        case 6:
            system("clear");
            insertByIndex(&list);
            wait();
            break;
        case 7:
            system("clear");
            deleteFirst(&list);
            wait();
            break;
        case 8:
            system("clear");
            deleteNode(&list);
            wait();
            break;
        case 9:
            system("clear");
            deleteList(&list);
            wait();
            break;
        case 10:
            system("clear");
            printListFromRoot(&list);
            wait();
            break;
        }
    } while (choice != 0);

    system("clear");
    deleteList(&list);
    return 0;
}
