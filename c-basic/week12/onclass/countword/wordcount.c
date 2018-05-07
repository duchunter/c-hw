#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"

#define INPUT "test.txt"
#define OUTPUT "wordcount.txt"
#define LINE 80

int main(int argc, char *argv[]) {
    Node *root = NULL;
    FILE *in, *out;
    if ((in = fopen(INPUT, "r")) == NULL) {
        printf("Cannot open %s\n", INPUT);
        return -1;
    }

    if ((out = fopen(OUTPUT, "w+")) == NULL) {
        printf("Cannot open %s\n", OUTPUT);
        return -1;
    }

    char line[LINE], *start, *stop;
    while (fgets(line, LINE, in) != NULL) {
        start = line;
        stop = NULL;
        while ((stop = strstr(start, " ")) != NULL) {
            *stop = '\0';
            addNode(&root, start);
            start = stop + 1;
        }

        *(start + strlen(start) - 1) = '\0';
        addNode(&root, start);
    }

    inOrder(root, out);
    printf("Done\n");
    fclose(in);
    fclose(out);
    return 0;
}
