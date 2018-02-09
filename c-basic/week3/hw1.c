#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void crypto(FILE *target, int diff, int encrypt) {
  char newFile[100] = "";
  strcat(newFile, encrypt ? "encrypted.txt" : "decrypted.txt");
  // Open file
  FILE *fptr;

  if ((fptr = fopen(newFile, "w+")) == NULL) {
    printf("Cannot create %s\n", newFile);
    return;
  }

  // Scan each char in target file, transform and write to new file
  char ch;
  while ((ch = fgetc(target)) != EOF) {
    int move = 0;

    // Transform character
    if (isupper(ch) || islower(ch)) {
      move = diff - 26 * (diff / 26);
      if (move > 26) move -= 26;

      if (encrypt) {
        ch += move;
        if (!isupper(ch) && !islower(ch)) ch -= 26;
      } else {
        ch -= move;
        if (!isupper(ch) && !islower(ch)) ch += 26;
      }
    }

    // Write to new file
    fputc(ch, fptr);
  }

  // Done
  printf("File encrypted, open '%s' to see\n", newFile);
  fclose(fptr);
}

int main(int argc, char const *argv[]) {
  // Wrong syntax
  if (argc != 4) {
    printf("Invalid syntax, should be: ./crypto 'flag' 'filename' 'displacement'\n");
    return 1;
  }

  // Open target file
  FILE *target;
  if ((target = fopen(argv[2], "r")) == NULL) {
    printf("Cannot open target file\n");
    return 1;
  }

  // Choose action based on flag
  if (strcmp(argv[1], "-e") == 0) {
    // Encrypt file
    crypto(target, atoi(argv[3]), 1);
  } else if (strcmp(argv[1], "-d") == 0) {
    // Decrypt file
    crypto(target, atoi(argv[3]), 0);
  } else {
    // Invalid mode
    printf("Invalid mode '%s', should be '-e' or '-d'\n", argv[1]);
  }

  fclose(target);
  return 0;
}
