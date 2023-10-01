#include <stdio.h>
#include <stdlib.h>

void bubbleSort(double arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                double temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int num;
    scanf("%d", &num); 

    double boxes[num];
    for (int i = 0; i < num; i++) {
        scanf("%lf", &boxes[i]);  
    }

    bubbleSort(boxes, num);
    
    double truckWeight;
    while (scanf("%lf", &truckWeight) != EOF) {  
        double currentWeight = 0;
        int boxCount = 0;
        for (int i = 0; i < num; i++) {
            if (currentWeight + boxes[i] <= truckWeight) {
                currentWeight += boxes[i];
                boxCount++;
            } else {
                break;  
            }
        }
        printf("%d\n", boxCount);  
    }

    return 0;
}
