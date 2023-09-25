#include <stdio.h>

int main() {
    double seedPrices[] = {0.05, 0.25, 0.70, 0.30};
    double salePrices[] = {0.50, 1.25, 3.00, 1.00};
    int quantities[] = {0, 0, 0, 0}; 
    double netProfit = 0.0;
    char c;

    while ((c = getchar()) != EOF && c != '\n') {
        switch (c) {
            case 'C':
                netProfit += salePrices[0] - seedPrices[0];
                quantities[0]++;
                break;
            case 'T':
                netProfit += salePrices[1] - seedPrices[1];
                quantities[1]++;
                break;
            case 'P':
                netProfit += salePrices[2] - seedPrices[2];
                quantities[2]++;
                break;
            case 'L':
                netProfit += salePrices[3] - seedPrices[3];
                quantities[3]++;
                break;
            case '#':
                break; 
            case '/':
                continue; 
            default:
                break;
        }
    }

    printf("Net profit: $%.2f\n", netProfit);

    return 0;
}
