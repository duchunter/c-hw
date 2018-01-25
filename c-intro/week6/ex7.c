#include <stdio.h>

// A calculator

int main() {
  float a, b, c;
  char op;
  printf("Please enter |operand|operator|operand|: ");
  scanf("%f%c%f", &a, &op, &b);

  switch (op) {
    case '+':
      c = a + b;
      break;
    case '-':
      c = a - b;
      break;
    case '*':
      c = a * b;
      break;
    case '/':
      c = a / b;
      break;
    default:
      printf("Invalid operator\n");
      return 0;
  }

  printf("%.1f %c %.1f = %.1f\n", a, op, b, c);

  return 0;
}
