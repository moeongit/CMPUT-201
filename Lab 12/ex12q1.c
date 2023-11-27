#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat;

void nfloat_debug(NewFloat f){ //part 1
    printf("%d ", (f >> 31) & 1);
    
    for (int i = 30; i >= 26; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf(" ");
    
    for (int i = 25; i >= 0; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf("\n");
}

NewFloat float_to_nfloat(float f); //part 2

void nfloat_print(NewFloat f); //part 3

NewFloat nfloat_double(NewFloat f); //part 4
NewFloat nfloat_add(NewFloat a, NewFloat b);


int main(void) {
    int part_num;
    char s1[40];
    float f1, f2;
    NewFloat n1, n2;

    // This will scan the input for you! Uncomment pieces once you implement
    // the functions for that part
    while (1) {
        int res = scanf(" p%d", &part_num);

        if (res != 1) {
            break;
        } else if (part_num == 1) {
            scanf("%s", s1);
            //n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        } else if (part_num == 2) {
            scanf("%f", &f1);
            //n1 = float_to_nfloat(f1);
            //nfloat_debug(n1);
        } else if (part_num == 3) {
            scanf("%s", s1);
            //n1 = bits_string_to_nfloat(s1);
            //nfloat_print(n1);
        } else {
            scanf("%s ", s1);

            if (s1[0] == 'd') {
                scanf("%f", &f1);
                //n1 = float_to_nfloat(f1);
                //n1 = nfloat_double(n1);
            } else {
                scanf("%f %f", &f1, &f2);
                //n1 = float_to_nfloat(f1);
                //n2 = float_to_nfloat(f2);
                //n1 = nfloat_add(n1, n2);
            }

            //nfloat_print(n1);
        }
    }
}
