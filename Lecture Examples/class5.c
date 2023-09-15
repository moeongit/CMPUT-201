#include <stdio.h>

int main(int argc, char **argv){

    int max = 0;
    int n = 10;
    int a[10] = {7, 5, 6, 8, 3, 2};

    printf("The storage size of variable 'max' is : %lu\n", sizeof(max));
    printf("The length of an array 'a' is: %d\n", n);
    printf("The storage size of array 'a' is : %lu\n", sizeof(a));

    for (int i = 0; i < n; i++){

        if (max < a[i]){
            max = a[i];
        }

    }


    printf("The maximum Integer is: %d\n", max);





}