#include <stdio.h>

int main() {
    int CAD;
    
    printf("Enter CAD amount: ");
    if (scanf("%d", &CAD) != 1 || CAD < 0 || CAD >= 100000) {
        printf("Invalid input. Please enter a Non-Negative Integer.\n");
        return 1;
    }
    
    int USD = (int)((CAD * 0.75) + 0.5); 
    
    printf("Converted USD amount: $%d\n", USD);
    printf("$100 bills: %d\n", USD / 100);
    USD %= 100;
    printf(" $50 bills: %d\n", USD / 50);
    USD %= 50;
    printf(" $20 bills: %d\n", USD / 20);
    USD %= 20;
    printf(" $10 bills: %d\n", USD / 10);
    USD %= 10;
    printf("  $5 bills: %d\n", USD / 5);
    USD %= 5;
    printf("  $2 bills: %d\n", USD / 2);
    USD %= 2;
    printf("  $1 bills: %d\n", USD);

    return 0;
}