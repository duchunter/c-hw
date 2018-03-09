#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    char name[20];
    char tel[11];
    char email[25];
} phoneAddr;

int main (int argc, char *argv[]) {
    /* EX1 copy file using block style
    if (argc != 3) {
        printf("Invalid syntax, should be ./tt 'source' 'dest' \n");
        return 1;
    }

    FILE *f1, *f2;
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return 1;
    }

    if ((f2 = fopen(argv[2], "w+")) == NULL) {
        printf("Cannot open %s\n", argv[2]);
        return 1;
    }

    char str[MAX + 1];
    int num;
    while (!feof(f1)) {
        num = fread(str, sizeof(char), MAX, f1);
        str[num * sizeof(char)] = '\0';
        printf("%s", str);
        fwrite(str, sizeof(char), num, f2);
    }

    fclose(f1);
    fclose(f2);


    /*EX2 phone book block style
    phoneAddr list[MAX];
    int x, n;
    printf("How many phone addresses do you want to add?: ");
    scanf("%d", &n);
    for (x = 0; x < n; x++) {
        phoneAddr phone;
        printf("- Phone %d:\n", x + 1);
        printf("Name: ");
        scanf("%s", phone.name);
        printf("Tel: ");
        scanf("%s", phone.tel);
        printf("Mail: ");
        scanf("%s", phone.email);

        list[x] = phone;
    }

    FILE *f;
    if ((f = fopen("test.bin", "w+b")) == NULL) {
        printf("Cannot open test.bin\n");
        return 1;
    }

    for (x = 0; x < n; x++) {
        fwrite(list, sizeof(phoneAddr), n, f);
    }

    fclose(f);

    if ((f = fopen("test.bin", "rb")) == NULL) {
        printf("Cannot open test.bin\n");
        return 1;
    }

    fread(list, sizeof(phoneAddr), n, f);
    for (x = 0; x < n; x++) {
        printf("%s-%s-%s\n", list[x].name, list[x].tel, list[x].email);
    }

    fclose(f);
*/

    /* EX3 locate and update data in specific index in a file
    FILE *f;
    if ((f = fopen("test.bin", "r+b")) == NULL) {
        printf("Cannot open test.bin\n");
        return 1;
    }

    int from, to, n, x;
    printf("Locate from: ");
    scanf("%d", &from);
    printf("To: ");
    scanf("%d", &to);

    n = to - from + 1;
    phoneAddr *list = (phoneAddr *) malloc(n * sizeof(phoneAddr));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fseek(f, (from - 1) * sizeof(phoneAddr), SEEK_SET);
    fread(list, sizeof(phoneAddr), n, f);

    for (x = 0; x < n; x++) {
        printf("%s-%s-%s\n", list[x].name, list[x].tel, list[x].email);
        printf("Enter new phone number: ");
        scanf("%s", list[x].tel);
    }

    fseek(f, (from - 1) * sizeof(phoneAddr), SEEK_SET);
    fwrite(list, sizeof(phoneAddr), n, f);

    fclose(f);
    free(list);
    */

    //* EX4 create file's header
    if (argc != 2) {
        printf("Syntax error, should be ./tt 'filename'\n");
        return 1;
    }

    FILE *f;
    if ((f = fopen(argv[1], "r+b")) == NULL) {
        printf("Cannot open %s", argv[1]);
        return 1;
    }

    char str[81];
    char *content = (char *) malloc(sizeof(char));
    int n = 0, m;

    while (!feof(f)) {
        m = fread(str, sizeof(char), 80, f);
        str[m * sizeof(char)] = '\0';
        n += m;
        content = realloc(content, (n + 1) * sizeof(char));
        strcat(content, str);
    }

    rewind(f);
    fprintf(f, "%d bytes - Duc - date\n%s", n * sizeof(char), content);

    free(content);
    fclose(f);

    return 0;
}
