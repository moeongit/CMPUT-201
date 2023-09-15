#include <stdio.h>

int main() {
    int CAD;
    
    printf("Enter CAD amount: ");
    if (scanf("%d", &CAD) != 1 || CAD < 0 || CAD >= 100000) {
        printf("Invalid input. Enter a non-negative Integer.\n");
        return 1;
    }
    
    int usdAmount = (int)((CAD * 0.75) + 0.5); 
    int usdBills[] = {100, 50, 20, 10, 5, 2, 1};
    int usdCount[7] = {0}; // This array is so we can have the amount 
                          // of each type of bill written in the for loop
    
    printf("Converted USD amount: $%d\n", usdAmount);
    
    for (int i = 0; i < 7; i++) {
        usdCount[i] = usdAmount / usdBills[i];
        usdAmount %= usdBills[i];
        printf("$%d bills: %d\n", usdBills[i], usdCount[i]);
    }
    
    return 0;
}