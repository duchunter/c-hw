#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define MAXT 50

                        //STRUCTURES
typedef struct {
  char name[30];
  int quantity;
  double price;
} Product;

typedef struct {
  int id;
  int qty;
  double total;
} pay;

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
//Force input value to be float
double mustBeDouble () {
  double n;
  while(!scanf("%lf", &n)) {
    clear();
    printf("Invalid input, enter again: ");
  }
  return n;
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
//Input Product
Product input () {
  Product p;
  printf("Product's name: ");
  scanf("%[^\n]s", p.name);
  getchar();
  printf("%s\n", p.name);
  printf("Enter quantity: ");
  while (1) {
    p.quantity = mustBeInt();
    if (p.quantity < 0)
      printf("Must be greater or equal 0, enter again: ");
    else break;
  }
  printf("%d\n", p.quantity);
  printf("Enter price: ");
  while (1) {
    p.price = mustBeDouble();
    if (p.price <= 0)
      printf("Must be greater than 0, enter again: ");
    else break;
  }
  printf("%f\n", p.price);
  clear();
  return p;
}
//Print products
void printPro (Product arr[], int l) {
  printf("%-3c %-30s %-8s %-4s\n", '#', "Product name", "Price", "Qty");
  for (int x = 0; x < l; x++) {
    printf("%-3d %-30s %-8.1f %-4d\n", x, arr[x].name, arr[x].price, arr[x].quantity);
  }
}
//lowercase
void lowercase (char *str1, char *str2) {
  int x;
  for (x = 0; x < strlen(str1); x++) {
    str2[x] = ('A' <= str1[x] && str1[x] <= 'Z') ? str1[x] - 'A' + 'a' : str1[x];
  }
  str2[x] = '\0';
}

                    // MAIN PROGRAM  //
int main() {
  Product proList[MAX];
  int n = 0;
  int choice, m, x;
  do {
    //Clear screen
    system("clear");
    //Display menu
    printf("\t\tBKMart\n\n");
    printf("1. Input product\n");
    printf("2. Insert product\n");
    printf("3. Product's info\n");
    printf("4. Search by name\n");
    printf("5. Product payment\n");
    printf("\n0. Exit\n");
    //Variables for all exercise that must be reset

    //Choose option and start
    printf("\nEnter your choice (0-5): ");
    choice = mustBeInt();
    clear();
    switch (choice) {
      //EX 1
      case 1:
        system("clear");
        printf("\t1. Input product\n\n");
        printf("Current: %d products\n", n);
        if (n == 10) {
          printf("Max capacity !!!, cannot insert !!!\n");
        }
        else {
          printf("How many products do you want to input?: ");
          while (1) {
            m = mustBeInt();
            if (m + n > 10)
              printf("Must be greater than 0 and less than %d, enter again: ", 10 - n);
            else break;
          }
          clear();
          for (x = 0; x < m; x++) {
            printf("\n- Product %d\n", n + x + 1);
            proList[n + x] = input();
          }
          n += m;
        }
        //Done
        wait();
        break;

      //EX 2
      case 2:
        system("clear");
        printf("\t2. Insert product\n\n");
        printf("Current: %d products\n", n);
        if (n == 10) {
          printf("Max capacity !!!, cannot insert !!!\n");
        }
        else {
          while (1) {
            printf("\n- Product %d\n", n + 1);
            proList[n] = input();
            n++;
            printf("Do you want to continue? (Y/y/N/n): ");
            int flag = 0;
            int valid = 0;
            while (!valid) {
              char c = getchar();
              clear();
              switch (c) {
                case 'y': case 'Y':
                  if (n == 10) {
                    printf("Max capacity, cannot insert !!!");
                    flag = 1;
                    valid = 1;
                  }
                  else {
                    flag = 0;
                    valid = 1;
                  }
                  break;

                case 'n': case 'N':
                  flag = 1;
                  valid = 1;
                  break;

                default:
                  valid = 0;
                  printf("Invalid, enter again: ");
              }
            }
            if (flag) break;
          }
        }
        //Done
        wait();
        break;

      //EX 3
      case 3:
        system("clear");
        printf("\t3. Product's info\n\n");
        printPro(proList, n);
        //Done
        wait();
        break;

      //EX 4
      case 4:
        system("clear");
        printf("\tSearch by name\n\n");
        char query[30], lower1[30], lower2[30];
        Product chosen[10];
        int p = 0;
        printf("Enter a name: ");
        scanf("%[^\n]s", query);
        clear();
        lowercase(query, lower1);
        for (x = 0; x < n; x++) {
          lowercase(proList[x].name, lower2);
          if (strcmp(lower1, lower2) == 0) {
            chosen[p] = proList[x];
            p++;
          }
        }
        printf("\nResults:\n\n");
        if (p == 0) printf("No product found\n");
        else printPro(chosen, p);
        //Done
        wait();
        break;

      //EX 5
      case 5:
        system("clear");
        printf("\tProduct payment\n\n");
        printPro(proList, n);
        pay payList[MAXT];
        int o = 0;
        double total;
        printf("\nHow many kinds of product do you want to buy: ");
        int t;
        while (1) {
          t = mustBeInt();
          if (t > n) printf("Too many\n");
          else if (t < 0) printf("Must be greater than 0\n");
          else break;
        }

        for (x = 0; x < t; x++) {
          printf("Enter product id: ");
          int id;
          while (1) {
            id = mustBeInt();
            if (id > n) printf("Too many\n");
            else if (id < 0) printf("Must be greater than 0\n");
            else break;
          }
          printf("Enter quantity: ");
          int qty;
          while (1) {
            qty = mustBeInt();
            if (qty < 0) printf("Must be greater than 0\n");
            else break;
          }
          if (qty > proList[id].quantity) {
            printf("Not enough product to sell\n");
            break;
          }
          else {
            payList[o].id = id;
            payList[o].qty = qty;
            payList[o].total = qty * proList[id].price;
            o++;
          }
        }
        printf("\nYour pay list\n");
        for (x = 0; x < o; x++) {
          total += payList[x].total;
          //proList[payList[x].id] -= payList[x].qty; 
          printf("%-4d %-4d %-10.2f\n", payList[x].id, payList[x].qty, payList[x].total);
        }
        printf("Total: %.2lf\n", total);
        //Done
        clear();
        wait();
        break;

    }
  } while(choice != 0);
  //Everything done
  system("clear");
  return 0;
}
