#include <stdio.h>

// Car paking fee printer

int main() {
  char type;
  float hour, regular, overtime = 0, maxRegular;
  float regularFee, overtimeFee, fee;
  printf("Please enter:\n");
  printf("- Vehicle type (c/C-car, b/B-bus, t/T-truck): ");
  scanf("%c", &type);
  printf("- Time: ");
  scanf("%f", &hour);

  if(hour < 0){
    printf("Invalid input\n");
    return 0;
  }

  printf("\nParking Fee\nVEHICLE TYPE: ");

  switch (type) {
    case 'c': case 'C':           //Car
      printf("CAR\n");
      maxRegular = 2;
      if(hour > maxRegular) {
        regular = maxRegular;
        overtime = hour - maxRegular;
      }
      else regular = hour;
      regularFee = 0.7;
      overtimeFee = 2.5;
      break;

    case 'b': case 'B':            //Bus
    printf("BUS\n");
      maxRegular = 2;
      if(hour > maxRegular) {
        regular = maxRegular;
        overtime = hour - maxRegular;
      }
      else regular = hour;
      regularFee = 1.5;
      overtimeFee = 2;
      break;

      case 't': case 'T':            //Truck
      printf("TRUCK\n");
        maxRegular = 1;
        if(hour > maxRegular) {
          regular = maxRegular;
          overtime = hour - maxRegular;
        }
        else regular = hour;
        regularFee = 2.5;
        overtimeFee = 3.25;
        break;

      default:
        printf("Invalid input\n");
        return 0;
  }

  printf("TIME: %.1f\n", hour);
  printf("REGULAR FEE: %.1f * %.1f = %.1f\n", regular, regularFee, regular*regularFee);
  printf("OVERTIME   : %.1f * %.1f = %.1f\n", overtime, overtimeFee, overtime*overtimeFee);
  printf("TOTAL      : %.1f\n", regular*regularFee + overtime*overtimeFee);
  printf("Thank you\n\n");

  return 0;
}
