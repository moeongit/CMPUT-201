#include <stdio.h>
#include <stdlib.h>

int main() {
    int Cad;

    printf("Enter CAD Amount: ");
    if (scanf("%d", &Cad) != 1 || Cad < 0 || Cad >= 100000) {
        printf("Please enter a Positive Integer less than 100,000.\n");
        return 1;
    }

    double USD = Cad * 0.75; 
    double round = USD - (int)USD;
    
    if (round >= 0.5) {
        USD = (int)USD + 1.0;
    } else {
        USD = (int)USD;
    }

    printf("Converted USD Amount: $%.0f\n", USD);  
    printf("$100 bills: %d\n", (int)(USD / 100));
    USD -= (int)(USD / 100) * 100;
    printf("$50 bills: %d\n", (int)(USD / 50));
    USD -= (int)(USD / 50) * 50;
    printf("$20 bills: %d\n", (int)(USD / 20));
    USD -= (int)(USD / 20) * 20;
    printf("$10 bills: %d\n", (int)(USD / 10));
    USD -= (int)(USD / 10) * 10;
    printf("$5 bills: %d\n", (int)(USD / 5));
    USD -= (int)(USD / 5) * 5;
    printf("$2 bills: %d\n", (int)(USD / 2));
    USD -= (int)(USD / 2) * 2;
    printf("$1 bills: %d\n", (int)USD);

    return 0;
}
