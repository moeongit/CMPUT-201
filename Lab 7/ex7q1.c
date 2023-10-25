#include <stdio.h>
#include <stdlib.h>

int main() {
    int NumOfAisles, SerialNum;
    char product, **aisles;

    scanf("%d", &NumOfAisles);

    aisles = (char**)malloc(NumOfAisles * sizeof(char*));
    int* aisleLengths = (int*)malloc(NumOfAisles * sizeof(int));

    for(int i = 0; i < NumOfAisles; i++) {
        aisles[i] = NULL;
        aisleLengths[i] = 0;
    }

    while (1) {
        int ValueNum;
        if (scanf("%d", &ValueNum) == EOF) { 
            break;
        }

        if (ValueNum == 0) {
            int index;

            scanf("%d", &index);

            if (aisles[index]) {
                printf("%s\n", aisles[index]);
                
            } else {
                printf("\n");
            }
        } else {
            SerialNum = ValueNum; 
            getchar(); 
            product = getchar();

            int index = SerialNum % NumOfAisles;
            int len = aisleLengths[index];

            aisles[index] = (char*)realloc(aisles[index], (len + 2) * sizeof(char));
            aisles[index][len] = product;
            aisles[index][len + 1] = '\0';

            aisleLengths[index]++; 
        }
    }

    for(int i = 0; i < NumOfAisles; i++) {
        if(aisles[i]) {
            free(aisles[i]);
        }
    }

    free(aisles);

    free(aisleLengths);

    return 0;
}