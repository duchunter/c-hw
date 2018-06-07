#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char domain[30];
    char ip[15];
    int blocked;
} element;

// Structure
typedef struct Node {
    element data;
    struct Node *left;
    struct Node *right;
} Node;

// New node
Node *newNode(element data) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->data = data;
  return new;
}

//Delete node
element deleteMin(Node **root) {
    element temp;
    if ((*root)->left == NULL) {
        temp = (*root)->data;
        *root = (*root)->right;
        return temp;
    }

    return deleteMin(&((*root)->left));
}
/*
void deleteNode(Node **root, int val) {
    if (*root == NULL) {
        printf("Nothing to delete\n");
        return;
    }

    if (val < (*root)->val) {
        return deleteNode(&(*root)->left, val);
    }

    if (val > (*root)->val) {
        return deleteNode(&(*root)->right, val);
    }

    if (((*root)->left == NULL) && ((*root)->right == NULL)) {
        *root = NULL;
        return;
    }

    if ((*root)->left == NULL) {
        *root = (*root)->right;
        return;
    }

    if ((*root)->right == NULL) {
        *root = (*root)->left;
        return;
    }

    (*root)->val = deleteMin(&(*root)->right);
}
*/
// Add new node
void addNode(Node **root, element data) {
  if (*root == NULL) {
    *root = newNode(data);
    return;
  }

  if (strcmp((*root)->data.domain, data.domain) > 0) {
    addNode(&((*root)->left), data);
  } else {
    addNode(&((*root)->right), data);
  }
}
/*
// Tree traversing
void preOrder(Node *root) {
  if (root == NULL) return;
  printf("Node %d\n", root->val);
  preOrder(root->left);
  preOrder(root->right);
}
*/
void inOrder(Node *root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%s (%s); ", root->data.domain, root->data.ip);
    inOrder(root->right);
}
/*
void postOrder(Node *root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("Node %d\n", root->val);
}
*/

// Find node
Node *findNodeByDomain(Node *root, char *domain) {
  if (root == NULL) return NULL;
  if (strcmp(root->data.domain, domain) == 0) return root;
  Node *temp = findNodeByDomain(root->left, domain);
  return temp ? temp : findNodeByDomain(root->right, domain);
}

Node *findNodeByIp(Node *root, char *ip) {
  if (root == NULL) return NULL;
  if (strcmp(root->data.ip, ip) == 0) return root;
  Node *temp = findNodeByIp(root->left, ip);
  return temp ? temp : findNodeByIp(root->right, ip);
}
/*
// Find depth of node
int depthNode(Node *root, int key) {
  if (root == NULL) return 0;
  if (root->val == key) return 1;
  int isFoundLeft = depthNode(root->left, key);
  int isFoundRight = depthNode(root->right, key);
  if (isFoundLeft) return 1 + isFoundLeft;
  if (isFoundRight) return 1 + isFoundRight;
}

// Find depth of tree
int depthTree(Node *root) {
  if (root == NULL) return 0;
  int depthLeft = 1 + depthTree(root->left);
  int depthRight = 1 + depthTree(root->right);
  return (depthLeft > depthRight) ? depthLeft : depthRight;
}

// Find parent of node
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

// Find sibling of node
Node *sibling(Node *root, int x) {
  Node *dad = parent(root, x);
  return (dad->left && dad->left->val == x) ? dad->right : dad->left;
}
*/
// Delete tree
void delTree(Node **root) {
  while (*root != NULL) {
    deleteMin(root);
  }
}
/*
// Find path to node
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

// Check if node is ancestor
int ancestor(Node *root, int x, int y) {
  Node *old = findNode(root, x);
  if (old == NULL) return 0;
  int arr[100];
  return path(old, y, arr, 0);
}

// prettyPrint
void padding(char ch, int n) {
    for (int i = 0; i < n; i++) {
        putchar(ch);
    }
}

void prettyPrint(Node *root, int level) {
    int i;
    if (root == NULL) {
        padding('\t', level);
        puts("-");
    } else {
        prettyPrint(root->right, level + 1);
        padding('\t', level);
        printf("%d\n", root->val);
        prettyPrint(root->left, level + 1);
    }
}

// Count lower/bigger
int lowerThan(Node *root, int key) {
  if (root == NULL) return 0;
  return (root->val < key)
         + lowerThan(root->left, key)
         + lowerThan(root->right, key);
}

int main(int argc, char const *argv[]) {
  Node *root = NULL;
  int arr[] = {5, 2, 8, 1, 4, 7, 9, 3, 6, 10};
  for (int x = 0; x < 10; x++) {
    addNode(&root, arr[x]);
  }

  //print_path(root, 10);
  //printf("%d\n", ancestor(root, 8, 10));
  //delTree(root);
  preOrder(root);
  deleteNode(&root, 7);
  printf("\n");
  //printf("Lower than 5: %d\n", lowerThan(root, 5));
  //preOrder(root);
  prettyPrint(root, 0);
  //printf("Depth of 4: %d\n", depthNode(root, 4));
  printf("Depth tree: %d\n", depthTree(root));
  //printf("%s\n", findNode(root, 3) ? "Found" : "Not found");
  //Node *sib = sibling(root, 7);
  //if (sib == NULL) printf("Not found\n");
  //else printf("Found %d\n", sib->val);
  return 0;
}
*/
