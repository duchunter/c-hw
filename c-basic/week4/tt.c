#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum { LINE = 80, FILELINE = 200 };

typedef struct {
    double x;
    double y;
} point;

typedef struct {
    point center;
    double radius;
} circle;

int in_circle(point p, circle c) {
    return c.radius > sqrt(pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2));
}

char *mystrcat(char *str1, char *str2) {
    int len1, len2;
    char *result;

    len1 = strlen(str1);
    len2 = strlen(str2);

    result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    if (result == NULL) {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    strcpy(result, str1);
    strcpy(result + len1, str2);

    return result;
}

int main (int argc, char *argv[]) {
    /* Ex1: dynamic reverse array + Ex2: input more using realloc
    int i, n, m, *p;

    printf("How many numbers do you want to enter?: ");
    scanf("%d", &n);

    // Allocate memory
    p = (int *)malloc(n * sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Get the numbers from the user
    for (i = 0; i < n; i++) {
        printf("- Number %d: ", i + 1);
        scanf("%d", p + i);
    }

    // Display in reverse
    printf("Reverse array is: ");
    for (i = n - 1; i >= 0; i--) {
        printf("%d ", *(p + i));
    }

    printf("\n");

    // Ex2: ask for more number
    printf("How many numbers do you want to add more?: ");
    scanf("%d", &m);
    p = (int *)realloc(p, (m + n) * sizeof(int));
    for (i = n; i < m + n; i++) {
        printf("Additional number %d: ", i + 1);
        scanf("%d", p + i);
    }

    // Display in reverse
    printf("Reverse array is: ");
    for (i = m + n - 1; i >= 0; i--) {
        printf("%d ", *(p + i));
    }

    printf("\n");

    // Free the allocated space
    free(p);
    */
    /* Ex2-example
    char *str;

    // Initial allocation
    str = (char *)malloc(15);
    strcpy(str, "tutorialspoint");
    printf("String = %s, Address = %p\n", str, str);

    // Reallocating
    str = (char *)realloc(str, 25);
    strcat(str, ".com");
    printf("String = %s, Address = %p\n", str, str);

    free(str);
    */
    /* Ex3: my strcat
    if (argc != 3) {
        printf("Invalid syntax\n");
        return 1;
    }
    char *result = mystrcat(argv[1], argv[2]);
    if (result == NULL) return 1;
    printf("%s\n", result);
    */
    /*Ex4 in circle
    point p;
    circle c;
    printf("Enter a point:\n- x: ");
    scanf("%lf", &p.x);
    printf("- y: ");
    scanf("%lf", &p.y);
    printf("Enter a circle:\n- Center:\n\t+ x: ");
    scanf("%lf", &c.center.x);
    printf("\t+ y: ");
    scanf("%lf", &c.center.y);
    printf("- Radius: ");
    scanf("%lf", &c.radius);
    if (in_circle(p, c)) {
        printf("This point is in circle\n");
    } else {
        printf("This point is out of circle\n");
    }
    */
    /* Ex5: read file, print line length + line
    if (argc != 2) {
        printf("Invalid syntax\n");
        return 1;
    }

    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Cannot open '%s'", argv[1]);
        return 1;
    }

    char str[FILELINE][LINE + 4];
    int x = 0;
    while (fgets(str[x], LINE, fptr) != NULL) {
        x++;
    }

    fclose(fptr);
    if ((fptr = fopen(argv[1], "w")) == NULL) {
        printf("Cannot open '%s'", argv[1]);
        return 1;
    }

    for (int y = 0; y < x; y++) {
        fprintf(fptr, "%d\t%s", strlen(str[y]), str[y]);
    }
    fclose(fptr);
    */
    // Ex6: merge 2 file
    if (argc != 4) {
        printf("Invalid syntax\n");
        return 1;
    }

    FILE *f1, *f2, *f3;
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        printf("Cannot open %s", argv[1]);
        return 1;
    }

    if ((f2 = fopen(argv[2], "r")) == NULL) {
        printf("Cannot open %s", argv[2]);
        return 1;
    }

    if ((f3 = fopen(argv[3], "w+")) == NULL) {
        printf("Cannot open %s", argv[3]);
        return 1;
    }

    char buff1[LINE], buff2[LINE];
    int a, b;
    while (1) {
        if (a = fgets(buff1, LINE, f1) != NULL) fputs(buff1, f3);
        if (b = fgets(buff2, LINE, f2) != NULL) fputs(buff2, f3);
        if (!a && !b) break;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
