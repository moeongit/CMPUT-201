#include <stdio.h>
#include <stdlib.h>

// Define book prices
#define HARDCOVER_PRICE 15.0
#define SOFTCOVER_PRICE 12.0
#define EBOOK_PRICE 7.0

// Define coupon discounts
#define HARDCOVER_COUPON_DISCOUNT 5.0
#define SOFTCOVER_COUPON_DISCOUNT 10.0
#define MIXED_COUPON_DISCOUNT 20.0

// Define percentage discounts
#define MINIMUM_PERCENTAGE_DISCOUNT 0.03
#define EBOOK_PERCENTAGE_DISCOUNT 0.04
#define ORDER_OVER_75_PERCENTAGE_DISCOUNT 0.10
#define ORDER_OVER_150_PERCENTAGE_DISCOUNT 0.15

int main() {
    int hardcover_books, softcover_books, ebooks;

    // Input book quantities
    printf("How many hardcover books are you buying? ");
    if (scanf("%d", &hardcover_books) != 1 || hardcover_books < 0) {
        printf("Invalid input for hardcover books.\n");
        return 1;
    }

    printf("How many softcover books are you buying? ");
    if (scanf("%d", &softcover_books) != 1 || softcover_books < 0) {
        printf("Invalid input for softcover books.\n");
        return 1;
    }

    printf("How many ebooks are you buying? ");
    if (scanf("%d", &ebooks) != 1 || ebooks < 0) {
        printf("Invalid input for ebooks.\n");
        return 1;
    }

    // Calculate the total cost before discounts
    double total_cost = (hardcover_books * HARDCOVER_PRICE) +
                        (softcover_books * SOFTCOVER_PRICE) +
                        (ebooks * EBOOK_PRICE);

    // Apply coupon discounts
    if ((hardcover_books + softcover_books) >= 6) {
        total_cost -= MIXED_COUPON_DISCOUNT;
    } else if (hardcover_books >= 2) {
        total_cost -= HARDCOVER_COUPON_DISCOUNT;
    } else if (softcover_books >= 4) {
        total_cost -= SOFTCOVER_COUPON_DISCOUNT;
    }

    // Apply percentage discounts
    if (hardcover_books >= 1 && softcover_books >= 1 && ebooks >= 1) {
        total_cost *= (1.0 - MINIMUM_PERCENTAGE_DISCOUNT);
    }
    if (ebooks >= 3) {
        total_cost *= (1.0 - EBOOK_PERCENTAGE_DISCOUNT);
    }
    if (total_cost > 75.0) {
        total_cost *= (1.0 - ORDER_OVER_75_PERCENTAGE_DISCOUNT);
    }
    if (total_cost > 150.0) {
        total_cost *= (1.0 - ORDER_OVER_150_PERCENTAGE_DISCOUNT);
    }

    // Output the final total cost
    printf("Order total: $%.2lf\n", total_cost);

    return 0;
}
