#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *left;
  struct Node *right;
} Node;

Node *newNode(int val) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->val = val;
  return new;
}

void addNode(Node **root, int x) {
  if (*root == NULL) {
    *root = newNode(x);
    return;
  }

  if ((*root)->val > x) {
    addNode(&((*root)->left), x);
  } else {
    addNode(&((*root)->right), x);
  }
}

void addLeft(Node **root, int x) {
    if (*root == NULL) {
        *root = newNode(x);
        return;
    }

    addLeft(&(*root)->left, x);
}

void addRight(Node **root, int x) {
    if (*root == NULL) {
        *root = newNode(x);
        return;
    }

    addRight(&(*root)->right, x);
}

void preOrder(Node *root) {
  if (root == NULL) return;
  printf("Node %c\n", root->val);
  preOrder(root->left);
  preOrder(root->right);
}

Node *findNode(Node *root, int x) {
  if (root == NULL) return NULL;
  if (root->val == x) return root;
  Node *temp = findNode(root->left, x);
  return temp ? temp : findNode(root->right, x);
}

Node *parent(Node *root, int x) {
  if (root == NULL) return NULL;
  if (
    (root->left && root->left->val == x)
    || (root->right && root->right->val == x)
  ) {
    return root;
  }

  Node *temp = parent(root->left, x);
  return temp ? temp : parent(root->right, x);
}

Node *sibling(Node *root, int x) {
  Node *dad = parent(root, x);
  return (dad->left && dad->left->val == x) ? dad->right : dad->left;
}

void delTree(Node **root) {
  if (*root == NULL) return;
  Node *right = (*root)->right;
  Node *left = (*root)->left;
  free(*root);
  *root = NULL;
  delTree(&right);
  delTree(&left);
}

int path(Node *root, int x, int arr[], int l) {
  if (root == NULL) return 0;
  if (root->val == x) {
    arr[l] = x;
    return 1;
  }

  if (path(root->left, x, arr, l + 1) || path(root->right, x, arr, l + 1)) {
    arr[l] = root->val;
    return 1;
  }
}

void print_path(Node *root, int x) {
  int arr[100];
  if (path(root, x, arr, 0)) {
    for (int n = 0; arr[n] != x; n++) {
      printf("%d\n", arr[n]);
    }
    printf("%d\n", x);
  } else {
    printf("Not found\n");
  }
}

int ancestor(Node *root, int x, int y) {
  Node *old = findNode(root, x);
  if (old == NULL) return 0;
  int arr[100];
  return path(old, y, arr, 0);
}

int nbNode(Node *root) {
    if (root == NULL) return 0;
    return 1 + nbNode(root->left) + nbNode(root->right);
}

int main(int argc, char const *argv[]) {
  Node *root = NULL;
  /*
  root = newNode('+');
  addLeft(&root, '!');
  addLeft(&root, 'a');
  addRight(&root, '/');
  addRight(&root, 'd');
  addLeft(&root->right, '-');
  addLeft(&root->right, 'b');
  addRight(&root->right->left, 'c');
  /*/
  int arr[] = {5, 2, 8, 1, 4, 7, 9, 3, 6, 10};
  for (int x = 0; x < 10; x++) {
    addNode(&root, arr[x]);
  }//

  //print_path(root, 10);
  //printf("%d\n", ancestor(root, 8, 10));
  //delTree(&root);
  preOrder(root);
  printf("%s\n", findNode(root, 3) ? "Found" : "Not found");
  //Node *sib = sibling(root, 7);
  //if (sib == NULL) printf("Not found\n");
  //else printf("Found %d\n", sib->val);
  return 0;
}
