#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define modVal 1007

int max = 0;

// Structure
typedef struct Node {
  char key[1000];
  int count;
  struct Node *left;
  struct Node *right;
} Node;

// New node
Node *newNode(char *key) {
  Node *newN = (Node *) malloc(sizeof(Node));
  strcpy(newN->key, key);
  newN->count = 1;
  return newN;
}

// Add newN node
void addNode(Node **root, char *key) {
  if (*root == NULL) {
    (*root) = newNode(key);
    return;
  }

  int cmp = strcmp((*root)->key, key);

  if (cmp > 0) {
    addNode(&((*root)->left), key);
  }

  else if (cmp < 0) {
    addNode(&((*root)->right), key);
  }

  else {
    (*root)->count += 1;
  }

  return;
}

// Find max in tree
int preOrder(Node *root) {
  if (root == NULL) return 0;
  if (root->count > max) {
    max = root->count;
  }
  preOrder(root->left);
  preOrder(root->right);
}

// String hashing
int stringHashing(char *s) {
  int p = 31;
  int m = modVal;
  int hash_value = 0;
  int p_pow = 1;
  int length = strlen(s);
  for (int x = 0; x < length; x++) {
    hash_value = (hash_value + (s[x] + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

// Check existence
int isExist(int hash, int markTable[], int l) {
  for (int x = 0; x < l; x++) {
    if (markTable[x] == hash) {
      return x;
    }
  }

  return -1;
}

int main(int argc, char const *argv[]) {
  Node **hashTable = (Node **) malloc(modVal * sizeof(Node *));
  int markTable[modVal];
  int l = 0;
  max = 0;
  int hash, mark, x;
  char str[1000];


  FILE *f = fopen("./DICTIONARY/Test07/DICTIONARY.INP", "r");
  if (f == NULL) {
    printf("Cannot open test file\n");
    return -1;
  }


  fscanf(f, "%s", str);
  //scanf("%s", str);
  while (strcmp(str, "-1") != 0) {
    hash = stringHashing(str);
    mark = isExist(hash, markTable, l);
    if (mark == -1) {
      markTable[l] = hash;
      l += 1;
    }

    addNode(&hashTable[hash], str);

    fscanf(f, "%s", str);
    //scanf("%s", str);
  }

  for (x = 0; x < l; x++) {
    preOrder(hashTable[markTable[x]]);
  }

  printf("%d\n", max);
  fclose(f);
  free(hashTable);
  return 0;
}
