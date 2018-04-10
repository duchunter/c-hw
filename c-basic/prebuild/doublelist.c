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
    node *now;
} doublelist;

int isEmpty(doublelist *list) {
    return list->root == NULL;
}

void movePtrByIndex(int index, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (index < 0) {
        printf("Index must be greater than 0");
        return;
    }

    *now = *root;
    for (int x = 0; x < index; x++) {
        *now = (*now)->next;
        if ((*now)->next == NULL) break;
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

void insertAfter(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*root == NULL) {
        *root = new;
        *now = *root;
    } else {
        new->next = (*now)->next;
        new->prev = *now;
        if ((*now)->next != NULL) (*now)->next->prev = new;
        (*now)->next = new;
        *now = (*now)->next;
    }
}

void insertAtHead(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*root == NULL) {
        *root = new;
        *now = *root;
    } else {
        new->next = *root;
        (*root)->prev = new;
        *root = new;
    }
}

void insertBefore(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*root == NULL) {
        *root = new;
        *now = *root;
    } else if (*now == *root) {
        insertAtHead(new, list);
        *now = *root;
    } else {
        new->next = *now;
        new->prev = (*now)->prev;
        if ((*now)->prev != NULL) (*now)->prev->next = new;
        (*now)->prev = new;
        *now = (*now)->prev;
    }
}

void insertAtTail(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*root == NULL) {
        *root = new;
        *now = *root;
    } else {
        node *temp;
        for (temp = *root; temp->next != NULL; temp = temp->next);
        temp->next = new;
        new->prev = temp;
    }
}

void insertByIndex(doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    if (index == 0) {
        insertAtHead(newNode(newElement()), list);
    } else {
        movePtrByIndex(index - 1, list);
        insertAfter(newNode(newElement()), list);
    }
}

void deleteNode(doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*now == *root) {
        *root = (*root)->next;
        free(*now);
    } else {
        (*now)->prev->next = (*now)->next;
        if ((*now)->next != NULL) (*now)->next->prev = (*now)->prev;
        free(*now);
    }

    *now = *root;
}

void deleteFirst(doublelist *list) {
    movePtrByIndex(0, list);
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

int main(int argc, char *argv[]) {
    doublelist list;
    list.root = list.now = NULL;
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
            printList(&list);
            wait();
            break;
        }
    } while (choice != 0);

    system("clear");
    deleteList(&list);
    return 0;
}
