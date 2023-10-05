#include <stdio.h>

int main() {
    int n = 22;
    int nums[n];
    int max, min;

    printf("Enter 22 integers: ");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &nums[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    min = max = nums[0];

    for (int i = 0; i < n - 2; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
        if (nums[i] < min) {
            min = nums[i];
        }
    }

    int x = nums[n - 2];
    int y = nums[n - 1];

    int result = x * max + y * min;

    printf("x * max + y * min: %d\n", result);

    return 0;
}