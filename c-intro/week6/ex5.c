#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// High/Low game

int main() {
  int min, max, random, num;

  printf("Please enter:\n");
  printf("- Minimum: ");
  scanf("%d", &min);
  printf("- Maximum: ");
  scanf("%d", &max);

  if (min >= max) {
    printf("Minimum must be smaller than maximum\n");
    return 0;
  }

  srand((unsigned)time(NULL));
  random = min + (rand() % (max - min + 1)); //Generate min -> max

  printf("Guess my number (between %d and %d): ", min, max);
  scanf("%d", &num);

  if(num < random)
    printf("Your guess was too small\n");
  else if(num > random)
    printf("Your guess was too big\n");
  else
    printf("That's correct !!!\n");

  printf("The correct number was %d\n", random);

  return 0;
}
