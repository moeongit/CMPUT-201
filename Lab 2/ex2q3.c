#include <stdio.h>
#include <stdlib.h>

int main(){
    int hardcover, softcover, ebook;
    double total = 0.0;

    printf("How many hardcover books are you buying? ");
    scanf("%d", &hardcover);
    printf("How many softcover books are you buying? ");
    scanf("%d", &softcover);
    printf("How many ebooks are you buying? ");
    scanf("%d", &ebook);

    if (hardcover < 0 || softcover < 0 || ebook < 0){
        printf("Please enter Positive Integers.\n");
        return 1;
    }

    total = hardcover


    return 0;
}