#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum {SUCCESS, FAIL};

void parse(double n, int *i, double *r) {
    *i = (int)n;
    *r = n - *i;
}

void replace(char *str, char c1, char c2) {
    if (str == NULL) return;

    while (*str != '\0') {
        if (*str == c1) *str = c2;
        str++;
    }
}

int main (int argc, char *argv[]) {
    /* EX1: split int and frac part of a double
    double n, r;
    int i;
    printf("Enter a real number: ");
    scanf("%lf", &n);
    parse(n, &i, &r);
    printf("Integer part: %d\nReal part: %lf\n", i, r);
    */

    /* EX2: replace char c1 by char c2 in a string
    char str[100], c1, c2;
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    printf("Enter character 1: ");
    c1 = getchar();
    getchar();
    printf("Enter character 2: ");
    c2 = getchar();
    getchar();
    replace(str, c1, c2);
    printf("New string is: %s", str);
    */

    /* EX3: solve ax^2 + bx + c using command line arg
    if (argc != 4) {
        printf("Invalid syntax, should be ./tt 'a' 'b' 'c'\n");
        return 1;
    }

    float a = atof(argv[1]);
    float b = atof(argv[2]);
    float c = atof(argv[3]);
    double delta = (b * b) - (4 * a * c);
    if (a == 0) {
        if (b == 0 && c != 0) {
            printf("Cannot solve\n");
        } else if (b == 0 && c == 0) {
            printf("Infinite solution\n");
        } else {
            printf("x = %f\n", -c / b);
        }
        return 0;
    }

    if (delta < 0) {
        printf("No solution\n");
    } else if (delta == 0) {
        printf("x1 = x2 = %f\n", -b / (2 * a));
    } else {
        printf("x1 = %f\n", (-b + sqrt(delta)) / (2 * a));
        printf("x2 = %f\n", (-b - sqrt(delta)) / (2 * a));
    }
    */

    /* EX4: open and close file
    FILE *fptr;
    char *filename = argv[1];
    int reval = SUCCESS;
    if (argc != 2) {
        printf("Invalid syntax\n");
        return 1;
    }

    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Cannot open %s\n", filename);
        reval = FAIL;
    } else {
        printf("The value of fptr: %p\n", fptr);
        printf("Ready to close file\n");
        fclose(fptr);
    }

    return reval;
    */

    /* EX5: copy file
    FILE *fptr1, *fptr2;
    if ((fptr1 = fopen("text.txt", "r")) == NULL) {
        printf("Cannot open source file\n");
        return 1;
    }

    if ((fptr2 = fopen("newtext.txt", "w+")) == NULL) {
        printf("Cannot open copy file");
        return 1;
    }

    char ch;
    printf("Copying file...\n");
    while ((ch = fgetc(fptr1)) != EOF) {
        fputc(ch, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);
    */

    /* EX6: a -> A and vice versa from a file*/
    FILE *fptr1, *fptr2;
    if ((fptr1 = fopen("text.txt", "r")) == NULL) {
        printf("Cannot open source file\n");
        return 1;
    }

    if ((fptr2 = fopen("newtext.txt", "w+")) == NULL) {
        printf("Cannot open copy file");
        return 1;
    }

    char ch;
    printf("Copying file and change letters...\n");
    while ((ch = fgetc(fptr1)) != EOF) {
        if ('a' <= ch && ch <= 'z') {
            fputc(ch - 'a' + 'A', fptr2);
        } else if ('A' <= ch && ch <= 'Z') {
            fputc(ch - 'A' + 'a', fptr2);
        } else {
            fputc(ch, fptr2);
        }

    }

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}
