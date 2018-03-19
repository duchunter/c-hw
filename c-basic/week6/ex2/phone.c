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

// SUPPORTING FUNCTIONS

//fflush
void clear () {
  while(getchar() != '\n');
}

//Wait for input to continue
void wait () {
  printf("\nEnter anything to return to menu: ");

  //Wait for user to enter anything
  getchar();
}

//Force input value to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n)) {
    clear();
    printf("Invalid input, enter again: ");
  }

  return n;
}

                      // INITIAL DATA
typedef struct {
  char model[30];
  int memory;
  float size;
  int price;
} phone;

typedef struct node {
    phone p;
    struct node *next;
} node;

node *root = NULL, *now = NULL;

                        // LIST FUNCTIONS

node *newNode(phone p) {
    node *new = (node *) malloc(sizeof(node));
    new->p = p;
    new->next = NULL;
    return new;
}

void addHead(node *new) {
    new->next = root;
    root = new;
}

void addAfter(node *new) {
    node *temp;
    if (root == NULL) {
        root = new;
    } else {
      if (now == NULL) now = root;
      temp = now->next;
      now->next = new;
      new->next = temp;
    }

    now = new;
}

void printNode(node *cur) {
  printf(
    "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
    cur->p.model, cur->p.memory, cur->p.size, cur->p.price
  );
}

void printList() {
  int page = 0;
  for (node *cur = root; cur != NULL; cur = cur->next) {
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

void exportList() {
  FILE *f;
  if ((f = fopen(OUTPUT, "w+b")) == NULL) {
    printf("Cannot open %s\n", OUTPUT);
    return;
  }

  node *cur;
  for (cur = root; cur != NULL; cur = cur->next) {
    fwrite(cur, sizeof(phone), 1, f);
  }

  printf("Done\n");
  fclose(f);
}

void delList() {
    for (node *cur = root; cur != NULL; cur = cur-> next) {
      free(cur);
    }

    root = NULL;
    now = NULL;
}

                    // OTHER FUNCTIONS

// Readfile text by line
phone parseLine(FILE *read) {
  phone ph;
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (line == NULL) {
    printf("Memory allocation failed\n");
    ph.price = -1;
    return ph;
  }

  if (fgets(line, MAX_LINE, read) == NULL) {
    ph.price = -1;
    return ph;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with the string p_start
    switch (l) {
      case 0:
        strcpy(ph.model, p_start);
        break;
      case 1:
        ph.memory = atoi(p_start);
        break;
      case 2:
        ph.size = atof(p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  ph.price = atoi(p_start);

  // Done
  free(line);
  return ph;
}

// Import from text
void importText() {
  FILE *text;
  if ((text = fopen(TEXT, "r")) == NULL) {
    printf("Cannot open %s\n", TEXT);
    return;
  }

  // Parse line in file to get data
  phone temp;
  while (1) {
    temp = parseLine(text);

    // Break if end of file
    if (temp.price == -1) {
      break;
    }

    // Add to list
    addHead(newNode(temp));
  }

  printf("Done\n");
  fclose(text);
}

// Import from dat
void importDat() {
  // Open file
  FILE *dat;
  if ((dat = fopen(DAT, "rb")) == NULL) {
    printf("Cannot open %s\n", DAT);
    return;
  }

  phone *block = (phone *) malloc(BLOCK * sizeof(phone));
  if (block == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  while (!feof(dat)) {
    int read = fread(block, sizeof(phone), BLOCK, dat);
    for (int x = 0; x < read; x++) {
      addAfter(newNode(block[x]));
    }
  }

  printf("Done\n");
  fclose(dat);
}

// Search by model
void searchModel() {
  char model[30];
  printf("Model: ");
  scanf("%[^\n]", model);
  getchar();
  for (node *cur = root; cur != NULL; cur = cur->next) {
    if (strcmp(model, cur->p.model) == 0) printNode(cur);
  }
}

// Search by price
void searchPrice() {
  printf("Price lower than: ");
  int price = mustBeInt();
  getchar();
  for (node *cur = root; cur != NULL; cur = cur->next) {
    if (cur->p.price <= price) printNode(cur);
  }
}

                      // MAIN

int main(int argc, char const *argv[]) {
  int choice;
  do {
    //Clear screen
    system("clear");

    //Display menu
    printf("\t\tPhone\n\n");
    printf("1. Import from text\n");
    printf("2. Import from dat\n");
    printf("3. Display list\n");
    printf("4. Search phone by model\n");
    printf("5. Search phone by price\n");
    printf("6. Export list\n");
    printf("\n0. Exit\n");

    //Choose option and start
    printf("\nEnter your choice (0-6): ");
    choice = mustBeInt();
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        printf("\tImport from text\n\n");
        importText();
        //Done
        wait();
        break;

      case 2:
        system("clear");
        printf("\tImport from dat\n\n");
        importDat();
        //Done
        wait();
        break;

      case 3:
        system("clear");
        printf("\tDisplay list\n\n");
        printList();
        //Done
        wait();
        break;

      case 4:
        system("clear");
        printf("\tSearch phone by model\n\n");
        searchModel();
        //Done
        wait();
        break;

      case 5:
        system("clear");
        printf("\tSearch phone by price\n\n");
        searchPrice();
        //Done
        wait();
        break;

      case 6:
        system("clear");
        printf("\tExport list\n\n");
        exportList();
        //Done
        wait();
        break;
    }
  } while(choice != 0);

  //Everything done
  delList();
  system("clear");
  return 0;
}
