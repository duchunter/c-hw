#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "test.txt"
#define OUTPUT "wordcount.txt"
#define LINE 80

int main(int argc, char *argv[]) {
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
        while ((stop = strchr(start, ' ')) != NULL) {
            stop = '\0';
            printf("%s\n", start);
            start = stop + 1;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
