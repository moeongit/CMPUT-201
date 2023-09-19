#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 22;
    int Nums[n];
    int Max, Min;

    printf("Enter 22 integers: ");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &Nums[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    Min = Max = Nums[0];

    for (int i = 0; i < n - 2; i++) {
        if (Nums[i] > Max) {
            Max = Nums[i];
        }
        if (Nums[i] < Min) {
            Min = Nums[i];
        }
    }

    int x = Nums[n - 2];
    int y = Nums[n - 1];

    int Result = x * Max + y * Min;

    printf("x * Max + y * Min: %d\n", Result);

    return 0;
}