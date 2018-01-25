#include <stdio.h>

//A bill printer

int main()
{
  int ipod, ipad, discount = 0;
  float total;
  printf("\tPlease enter product's quantity:\n");
  printf("iPod: ");
  scanf("%d", &ipod);
  printf("iPad: ");
  scanf("%d", &ipad);
  //Error value
  if(ipod < 0 || ipad < 0) {
    printf("Please enter a positive value !");
    return 0;
  }
  //Ok
  total = ipod * 148 + ipad * 288;
  if((ipod > 3 && ipad > 2) || total > 1020) {
    printf("You will have a discount !!!\n");
    discount = 1;
  }

  printf("\n\tBKStore supermarket - Apple products:\n\n");
  printf("\t\tPrice\tQty\tTotal\n\n");
  printf("iPod\t\t$148\t%d\t$%d\n", ipod, ipod * 148);
  printf("iPad\t\t$288\t%d\t$%d\n", ipad, ipad * 288);
  printf("---------------------------------------\n");
  printf("Net payment\t\t\t$%.0f\n", total);

  if(discount == 1) {
    printf("Discount\t\t\t10%%\n");
    printf("You pay\t\t\t\t$%.1f\n", total * 0.1);
  }
  else printf("You pay\t\t\t\t$%.0f\n", total);
  printf("\n");

  return 0;
}
