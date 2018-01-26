#include <stdio.h>
#include <stdlib.h>

void ex(int x, double precision) {
	double sum = 1, oldSum, denominator, absolute;
	int n = 1, i;

	do {
		oldSum = sum;

		// Calculate n!
		denominator = 1;
		for (i = 1; i <= n; i++) {
		    denominator *= i;
		}

		// Calculate x^n
    double power = 1;
    for (i = 0; i < n; i++) {
      power *= x;
    }

		sum += power / denominator;
		n++;

		// Calculate absolute diff
		absolute = sum > oldSum ? sum - oldSum : oldSum - sum;

	} while (absolute > precision);

	printf("e^x= %.10lf\n", sum);
}

int main(int argc, char const *argv[]) {
	if (argc < 2 || argc > 3) {
		// Just program name, no params
		printf("Invalid syntax, should be: ./hw3 'x' 'precision'(OPTIONAL)\n");
	} else if (argc == 2) {
		// No input precision, set to deault 0.0001
		ex(atoi(argv[1]), 0.0001);
	} else {
		// OK
		ex(atoi(argv[1]), atof(argv[2]));
	}

  return 0;
}
