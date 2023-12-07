#include "ex8q1.h"

float *indexArray = NULL;
int *valueArray = NULL;
int CurLength = 0;

int BinarySearch(float targetIndex) {
    int low = 0, high = CurLength - 1, mid;
    
    while (low <= high) {
        mid = (low + high) / 2;

        if (indexArray[mid] == targetIndex) {
            return mid;
        }
        if (indexArray[mid] < targetIndex) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }
    return low;
}

void UpdateValue(float targetIndex, int newValue) {
    int pos = BinarySearch(targetIndex);
    
    if (pos < CurLength && indexArray[pos] == targetIndex) {
        valueArray[pos] = newValue;
    } 

    else {
        indexArray = realloc(indexArray, (CurLength + 1) * sizeof(float));
        valueArray = realloc(valueArray, (CurLength + 1) * sizeof(int));

        for (int i = CurLength; i > pos; i--) {
            indexArray[i] = indexArray[i - 1];
            valueArray[i] = valueArray[i - 1];
        }

        indexArray[pos] = targetIndex;
        valueArray[pos] = newValue;
        
        CurLength++;
    }
}

void displayValues() {
    printf("[");
    for (int i = 0; i < CurLength; i++) 
    {
        printf("%d", valueArray[i]);
        
        if (i != CurLength - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() 
{
    int is_print, value;
    float index;

    while (!feof(stdin)) {
        read_line(&is_print, &index, &value);
        
        if (is_print) {
            displayValues();
        } 
        else {
            UpdateValue(index, value);
        }
    }

    free(indexArray);
    free(valueArray);

    return 0;
}