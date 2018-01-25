#include<stdio.h>

//Bill printer

int main()
{
    //Input
    char ISBN[64], Title[64];
    int Qty, Price, Total;
    float youPay;
    printf("Enter quantity: ");
    scanf("%d",&Qty);
    printf("Enter ISBN: ");
    scanf("%s",ISBN);
    printf("Enter title: ");
    scanf("%s",Title);
    printf("Enter price: ");
    scanf("%d",&Price);
    Total = Qty * Price;
    youPay = Total * 104/100;
    //Output
    printf("\nBK Book Store\n\n");
    printf("Qty\tISBN\tTitle\tPrice\tTotal\n");
    printf("_____________________________________\n");
    printf("%d\t%s\t%s\t%d\t%d\n\n",Qty,ISBN,Title,Price,Total);
    printf("VAT = 4%%\n");
    printf("You pay: %.0f VND\n",youPay);

    return 0;
}
