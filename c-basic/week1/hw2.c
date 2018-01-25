#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Words library
char *article[] = {
  "the", "a", "one", "some", "any"
};
char *noun[] = {
  "boy", "girl", "dog", "town", "car"
};
char *verb[] = {
  "drove", "jumped", "ran", "walked", "skipped"
};
char *prep[] = {
  "to", "from", "over", "under", "on"
};

// Get a random number
int getRand() {
  return rand() % 5;
}

int main(int argc, char const *argv[]) {
  // Seeded to prevent same value each time calling rand()
  srand((unsigned)time(NULL));

  // Generate 10 sentences
  for (int x = 0; x < 10; x++) {
    char sentence[100] = "";
    strcat(sentence, article[getRand()]);
    strcat(sentence, " ");
    strcat(sentence, noun[getRand()]);
    strcat(sentence, " ");
    strcat(sentence, verb[getRand()]);
    strcat(sentence, " ");
    strcat(sentence, prep[getRand()]);
    strcat(sentence, " ");
    strcat(sentence, article[getRand()]);
    strcat(sentence, " ");
    strcat(sentence, noun[getRand()]);
    strcat(sentence, ".");

    // Uppercase the first letter
    sentence[0] = sentence[0] - 'a' + 'A';
    
    printf("%d.\t%s\n", x + 1, sentence);
  }

  return 0;
}
