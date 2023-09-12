#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int length, index = 0;
    
    // Prompt the user for the array length
    printf("Enter the length of the array: ");
    if (scanf("%d", &length) == 1) {
        if (length <= 0) {
            printf("Invalid array length\n");
            return 1;
        }
        
        int *array = (int *)malloc(length * sizeof(int));
        if (array == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        
        // Prompt the user for each array element
        for (int i = 0; i < length; i++) {
            printf("Enter element %d: ", i + 1);
            if (scanf("%d", &array[i]) != 1)
                exit(100);
            if (array[index] < array[i])
                index = i;
        }
        
        printf("The maximum element is %d\n", array[index]);
        
        // Don't forget to free the allocated memory when you're done.
        free(array);
    }
    
    return 0;
}
