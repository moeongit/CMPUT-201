#include <stdio.h>
#include <stdlib.h>

int main() {
    int numAisles, serialCode;
    char product, **aisles;

    scanf("%d", &numAisles);

    aisles = (char**)malloc(numAisles * sizeof(char*));
    int* aisleLengths = (int*)malloc(numAisles * sizeof(int));

    for(int i = 0; i < numAisles; i++) {
        aisles[i] = NULL;
        aisleLengths[i] = 0;
    }

    while (1) {
        int readValue;
        if (scanf("%d", &readValue) == EOF) { 
            break;
        }

        if (readValue == 0) {
            int index;
            scanf("%d", &index);

            if (aisles[index]) {
                printf("%s\n", aisles[index]);
            } else {
                printf("\n");
            }
        } else {
            serialCode = readValue; 

            getchar(); 
            product = getchar();

            int index = serialCode % numAisles;
            int len = aisleLengths[index];

            aisles[index] = (char*)realloc(aisles[index], (len + 2) * sizeof(char));
            aisles[index][len] = product;
            aisles[index][len + 1] = '\0';

            aisleLengths[index]++; // Increment the length after adding a product
        }
    }

    // Free allocated memory.
    for(int i = 0; i < numAisles; i++) {
        if(aisles[i]) {
            free(aisles[i]);
        }
    }
    free(aisles);
    free(aisleLengths);

    return 0;
}
