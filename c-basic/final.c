#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bintree.h"

#define MAX_LINE 80

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

int parseLine(FILE *f, char divider, Node **root) {
    char *line = (char *) malloc(MAX_LINE * sizeof(char));
    if (fgets(line, MAX_LINE, f) == NULL) {
        return 0;
    }

    element data;
    int l = 0;
    char *p_start = line;
    char *p_end = NULL;
    while ((p_end = strchr(p_start, divider)) != NULL) {
        *p_end = '\0';

        // Do sth with that string
        strcpy(data.domain, p_start);
        l++;
        p_start = p_end + 1;
    }

    // Do sth with that string
    p_start[strlen(p_start) - 1] = '\0';
    strcpy(data.ip, p_start);
    l++;

    free(line);
    data.blocked = 0;
    //printf("1\n");
    addNode(root, data);
    //printf("2\n");
    return l;
}

int ipcmp(char *ip1, char *ip2) {
    char *e1, *e2, str1[15], str2[15];
    e1 = strchr(ip1, '.');
    e2 = strchr(ip2, '.');
    if (e1 == NULL && e2 == NULL) {
      if (atoi(ip1) > atoi(ip2)) return 1;
      if (atoi(ip1) < atoi(ip2)) return -1;
      return 0;
    }

    strncpy(str1, ip1, (e1 - ip1) / sizeof(char));
    strncpy(str2, ip1, (e2 - ip2) / sizeof(char));
    if (atoi(str1) > atoi(str2)) return 1;
    if (atoi(str1) < atoi(str2)) return -1;
    return ipcmp(e1 + 1, e2 + 1);
}


                    // MAIN PROGRAM  //
int main() {
  int choice;
  Node *root = NULL, *temp, *root2 = NULL;
  char domain[30], *cut;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("1. Reading data\n");
    printf("2. IP lookup\n");
    printf("3. Block website\n");
    printf("4. IP sort\n");
    printf("\n5. Exit\n");
    //Variables for all exercise that must be reset

    //Choose option and start
    printf("\nEnter your choice (1-5): ");
    choice = mustBeInt();
    getchar();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        delTree(&root);
        //root = NULL;
        printf("\tReading data\n\n");
        FILE *ip;
        if ((ip = fopen("ip.txt", "r")) == NULL) {
            printf("Cannot open %s\n", "ip.txt");
        } else {
            while (parseLine(ip, ' ', &root) != 0);
            inOrder(root);
            printf("\n");
            fclose(ip);
        }
        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\tIP lookup\n\n");
        printf("Enter domain: ");
        scanf("%s", domain);
        if (strstr(domain, "www.") != NULL) {
            cut = &domain[4];
            strcpy(domain, cut);
        }

        getchar();
        temp = findNodeByDomain(root, domain);
        if (temp == NULL) {
            printf("This site can't be reached.\n");
        } else {
            if (temp->data.blocked) {
                printf("This site has been blocked\n");
            } else {
                printf("Redirecting to %s\n", temp->data.ip);
            }
        }
        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\tBlock website\n\n");
        FILE *block;
        if ((block = fopen("blockedip.txt", "r")) == NULL) {
            printf("Cannot open %s\n", "blockedip.txt");
        } else {
            while (fgets(domain, MAX_LINE, block) != NULL) {
                domain[strlen(domain) - 1] = '\0';
                char check = domain[strlen(domain) - 1];
                printf("%s\n", domain);
                if ('0' > check || check > '9') {
                    temp = findNodeByDomain(root, domain);
                    if (temp != NULL) {
                        temp->data.blocked = 1;
                    }
                } else {
                    temp = findNodeByIp(root, domain);
                    if (temp != NULL) {
                        temp->data.blocked = 1;
                    }
                }
            }

            printf("Enter domain: ");
            scanf("%s", domain);
            getchar();
            if (strstr(domain, "www.") != NULL) {
                cut = &domain[4];
                strcpy(domain, cut);
            }

            temp = findNodeByDomain(root, domain);
            if (temp == NULL) {
                printf("This site can't be reached.\n");
            } else {
                if (temp->data.blocked) {
                    printf("This site has been blocked\n");
                } else {
                    printf("Redirecting to %s\n", temp->data.ip);
                }
            }

            fclose(block);
        }

        //Done
        wait();
        break;

      //EX 4
      case 4:
        system("clear");
        printf("\tIP sort\n\n");
        printf("%d\n", ipcmp("11.1.1.1", "2.2.2.2"));
        //Done
        wait();
        break;
    }
  } while(choice != 5);

  //Everything done
  system("clear");
  return 0;
}
