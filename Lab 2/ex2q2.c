#include <stdio.h>
#include <stdlib.h>

int main(){

    int Cad;

    printf("Enter CAD Amount: ");
    if (scanf("%d", &Cad) != 1 || Cad < 0 || Cad >= 100000){
        printf("Please enter a Positive Integer less than 100,000.\n");
        return 1;
    }

    int USD = (Cad * 0.75);

    printf("Converted USD Amount: $%d\n", USD);
    printf("$100 bills: %d\n", USD/100);
    USD %= 100;
    printf("$50 bills: %d\n", USD/50);
    USD %= 50;
    printf("$20 bills: %d\n", USD/20);
    USD %= 20;
    printf("$10 bills: %d\n", USD/10);
    USD %= 10;
    printf("$5 bills: %d\n", USD/5);
    USD %= 5;
    printf("$2 bills: %d\n", USD/2);
    USD %= 2;
    printf("$1 bills: %d\n", USD);
    
    return 0;
}