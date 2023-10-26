#include <stdio.h>
#include <stdlib.h>

int main() {
    int NumOfAisles, SerialNum;
    char product, **aisles;

    scanf("%d", &NumOfAisles);

    aisles = malloc(NumOfAisles * sizeof(char*));
    int* aisleLengths = malloc(NumOfAisles * sizeof(int));

    for(int i = 0; i < NumOfAisles; i++) {
        aisles[i] = NULL;
        aisleLengths[i] = 0;
    }

    while (scanf("%d", &SerialNum) != EOF) {
        if (SerialNum == 0) {
            int index;

            scanf("%d", &index);

            if (aisles[index]) {
                printf("%s\n", aisles[index]);
                
            } else {
                printf("\n");
            }
        } else {
            getchar(); 
            product = getchar();

            int Aisleindex = SerialNum % NumOfAisles;
            int len = aisleLengths[Aisleindex];

            aisles[Aisleindex] = (char*)realloc(aisles[Aisleindex], (len + 2) * sizeof(char));
            aisles[Aisleindex][len] = product;
            aisles[Aisleindex][len + 1] = '\0';

            aisleLengths[Aisleindex]++; 
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