#include <stdio.h>
#include <stdlib.h>

int m;
int count = 0;

int main(int argc, char const *argv[]) {
  scanf("%d", &m);
  int h, a, p, y, n, e, w, v, x, r;
  int sum, left;

  for (h = 1; h <= 9; h++) {
    for (a = 0; a <= 9; a++) {
      for (p = 0; p <= 9; p++) {
        sum = 10000 * h + 990 * a + 110 * p;
        if (sum > m + 1000 + 999 + 200) {
          for (v = 1; v <= 9; v++) {
            if (sum - 1000 * v > m + 999 + 200) {
              // Remember to add back
              sum -= 1000 * v;
              for (y = 1; y <= 9; y++) {
                if (sum - 999 * y > m + 200) {
                  // Remember to add back
                  sum -= 999 * y;

                  for (n = 1; n <= 9; n++) {
                    if (sum - 200 * n > m) {
                      // Remember to add back
                      sum -= 200 * n;

                      for (e = 0; e <= 9; e++) {
                        if (sum - 120 * e > m) {
                          // Remember to add back
                          sum -= 120 * e;

                          for (w = 0; w <= 9; w++) {
                            if (sum - w > m) {
                              // Remember to add back
                              sum -= w;

                              for (x = 0; x <= 9; x++) {
                                if (sum - x >= m) {
                                  // Remember to add back
                                  sum -= x;

                                  for (r = 0; r <= 9; r++) {
                                    if (sum - r == m) {
                                      count += 1;
                                      printf("%d\n", count);
                                    }
                                  }

                                  sum += x;
                                }
                              }

                              sum += w;
                            }
                          }

                          sum += 120 * e;
                        }
                      }

                      sum += 200 * n;
                    }
                  }

                  sum += 999 * y;
                }
              }

              sum += 1000 * v;
            }
          }
        }
      }
    }
  }

  printf("%d\n", count);
  return 0;
}
