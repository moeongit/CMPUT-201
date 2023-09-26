#include <stdio.h>
#include <stdbool.h>

#define CarrotSalePrice 0.50
#define TurnipSalePrice 1.25
#define PumpkinSalePrice 3.00
#define LettuceSalePrice 1.00

#define CarrotPurchasePrice 0.05
#define TurnipPurchasePrice 0.25
#define PumpkinPurchasePrice 0.70
#define LettucePurchacePrice 0.30

double ProfitCalculation(char crop, bool is_sold) {
    double profit = 0.0;

    switch (crop) {
        case 'C': profit = is_sold ? CarrotSalePrice - CarrotPurchasePrice : -CarrotPurchasePrice; break;
        case 'T': profit = is_sold ? TurnipSalePrice - TurnipPurchasePrice : -TurnipPurchasePrice; break;
        case 'P': profit = is_sold ? PumpkinSalePrice - PumpkinPurchasePrice : -PumpkinPurchasePrice; break;
        case 'L': profit = is_sold ? LettuceSalePrice - LettucePurchacePrice : -LettucePurchacePrice; break;
    }
    return profit;
}

int main() {
    char choice;
    double NetProfit = 0.0;

    while ((choice = getchar()) != EOF && choice != '\n') {
        if (choice == '/' || choice == '#') {
            char NextCrop = getchar();
            NetProfit += ProfitCalculation(NextCrop, choice == '/');
        }
    }

    printf("Net profit: $%.2f\n", NetProfit);
    return 0;
}
