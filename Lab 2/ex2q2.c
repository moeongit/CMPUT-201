#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int Cad;

    printf("Enter CAD Amount: ");
    if (scanf("%d", &Cad) != 1 || Cad < 0 || Cad >= 100000) {
        printf("Please enter a Positive Integer less than 100,000.\n");
        return 1;
    }

    double USD = Cad * 0.75; 

    int roundedUSD = round(USD);

    printf("Converted USD Amount: $%d\n", roundedUSD);
    printf("$100 bills: %d\n", roundedUSD / 100);
    roundedUSD %= 100;
    printf("$50 bills: %d\n", roundedUSD / 50);
    roundedUSD %= 50;
    printf("$20 bills: %d\n", roundedUSD / 20);
    roundedUSD %= 20;
    printf("$10 bills: %d\n", roundedUSD / 10);
    roundedUSD %= 10;
    printf("$5 bills: %d\n", roundedUSD / 5);
    roundedUSD %= 5;
    printf("$2 bills: %d\n", roundedUSD / 2);
    roundedUSD %= 2;
    printf("$1 bills: %d\n", roundedUSD);

    return 0;
}
