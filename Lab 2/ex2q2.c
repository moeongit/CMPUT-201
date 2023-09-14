#include <stdio.h>

int main() {
    int cadAmount;
    
    printf("Enter CAD amount: ");
    if (scanf("%d", &cadAmount) != 1 || cadAmount < 0 || cadAmount >= 100000) {
        printf("Invalid input\n");
        return 1;
    }
    
    int usdAmount = (int)((cadAmount * 0.75) + 0.5); // Convert CAD to USD and round to nearest USD
    int usdBills[] = {100, 50, 20, 10, 5, 2, 1};
    int usdCount[7] = {0};
    
    printf("Converted USD amount: $%d\n", usdAmount);
    
    for (int i = 0; i < 7; i++) {
        usdCount[i] = usdAmount / usdBills[i];
        usdAmount %= usdBills[i];
        printf("$%d bills: %d\n", usdBills[i], usdCount[i]);
    }
    
    return 0;
}
