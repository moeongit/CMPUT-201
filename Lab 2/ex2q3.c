#include <stdio.h>

// Book prices
#define HardcoverPrice 15.0
#define SoftcoverPrice 12.0
#define EbookPrice 7.0

// Coupon Discounts
#define HardcoverCouponDiscount 5.0
#define SoftcoverCouponDiscount 10.0
#define MixedCouponDiscount 20.0

// Percentage Discounts
#define MinPercentageDiscount 0.03
#define EbookPercentageDiscount 0.04
#define OrderOver75PercentageDiscount 0.10
#define OrderOver150PercentageDiscount 0.15

int main(){
    int hardcoverbooks, softcoverbooks, ebooks;

    printf("How many hardcover books are you buying? ");
    if (scanf("%d", &hardcoverbooks) != 1 || hardcoverbooks < 0 || hardcoverbooks >= 100000){
        printf("Invalid input. Please enter a Non-Negative Integer less than 100,000.\n");
        return 1;
    }

    printf("How many softcover books are you buying? ");
    if (scanf("%d", &softcoverbooks) != 1 || softcoverbooks < 0 || softcoverbooks >= 100000){
        printf("Invalid input. Please enter a Non-Negative Integer less than 100,000.\n");
        return 1;
    }

    printf("How many ebooks are you buying? ");
    if (scanf("%d", &ebooks) != 1 || ebooks < 0 || ebooks >= 100000){
        printf("Invalid input. Please enter a Non-Negative Integer less than 100,000.\n");
        return 1;
    }

    // Total Cost
    double totalcost = (hardcoverbooks * HardcoverPrice) +
                        (softcoverbooks * SoftcoverPrice) +
                        (ebooks * EbookPrice);

    // Coupon Discounts
    if ((hardcoverbooks + softcoverbooks) >= 6){
        totalcost -= MixedCouponDiscount;
    }
    if (hardcoverbooks >= 2){
        totalcost -= HardcoverCouponDiscount;
    }
    if (softcoverbooks >= 4){
        totalcost -= SoftcoverCouponDiscount;
    }

    // Percentage Discounts
    double x, y, j, k;
    if ((hardcoverbooks >= 1) && (softcoverbooks >= 1) && (ebooks >= 1)) {
        x = totalcost * MinPercentageDiscount;
    }
    if (ebooks >= 3){
        y = totalcost * EbookPercentageDiscount;
    }
    if (totalcost > 75.0){
        j = totalcost * OrderOver75PercentageDiscount;
    }
    if (totalcost > 150.0){
        k = totalcost * OrderOver150PercentageDiscount;
    }
    totalcost -= x + y + j + k;

    // Final Total Cost
    printf("Order total: $%.2lf\n", totalcost);

    return 0;
}