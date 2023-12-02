#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat;

NewFloat bits_string_to_nfloat(char *s) {
    NewFloat result = 0;
    for (; *s; s++) {
        result = (result << 1) | (*s - '0');
    }
    return result;
}



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


NewFloat float_to_nfloat(float f) { //part 2
    uint32_t floatBits;
    memcpy(&floatBits, &f, sizeof(float));

    uint32_t sign = (floatBits >> 31) & 0x1;

    int32_t exponent = ((floatBits >> 23) & 0xFF) - 127 + 15;

    uint32_t mantissa = (floatBits & 0x7FFFFF);

    if (exponent >= 31) {
        exponent = 31; 
        mantissa = 0; 
    } 
    else if (exponent <= 0) {
        while (exponent < 0 && mantissa != 0) {
            mantissa >>= 1; 
            exponent++;
        }
        if (exponent < 0) {
            exponent = 0; 
        }
    }
    mantissa <<= 3;

    NewFloat nf = (sign << 31) | ((exponent & 0x1F) << 26) | (mantissa & 0x03FFFFFF);
    return nf;
}



void nfloat_print(NewFloat f) { //part 3
    int sign = (f >> 31) & 1;

    int exponent = ((f >> 26) & 0x1F) - 15;

    uint32_t mantissa = f & 0x03FFFFFF;

    if (exponent == -15 && mantissa == 0) {
        printf("%c0.0000000\n", sign ? '-' : ' ');
        return;
    }

    double decimalValue = mantissa;
    if (exponent == -15) {
        decimalValue /= (1 << 25); 
    } else {
        decimalValue = (1 << 26) | mantissa;
        if (exponent > 0) {
            while (exponent--) decimalValue *= 2;
        } else {
            while (exponent++) decimalValue /= 2;
        }
    }
    
    if (sign) {
        decimalValue = -decimalValue;
    }

    decimalValue /= (1 << 26); 

    printf("%.7f\n", decimalValue);
}


NewFloat nfloat_double(NewFloat f) { //part 4
    if ((f & 0x7FFFFFFF) == 0) {
        return f; 
    }

    int exponent = (f >> 26) & 0x1F;
    if (exponent == 0) {
        uint32_t mantissa = f & 0x03FFFFFF;
        mantissa <<= 1; 
        if (mantissa & (1 << 26)) {
            exponent++;
            mantissa &= 0x03FFFFFF;
        }
        return (f & 0x80000000) | (exponent << 26) | mantissa; 
    } else if (exponent < 30) {
        exponent++;
        return (f & 0x80000000) | (exponent << 26) | (f & 0x03FFFFFF);
    } else {
        return (f & 0x80000000) | (31 << 26); 
    }
}

NewFloat nfloat_add(NewFloat a, NewFloat b) {
    int sign_a = (a >> 31) & 1;
    int sign_b = (b >> 31) & 1;
    int exponent_a = (a >> 26) & 0x1F;
    int exponent_b = (b >> 26) & 0x1F;
    uint32_t mantissa_a = a & 0x03FFFFFF;
    uint32_t mantissa_b = b & 0x03FFFFFF;

    if (exponent_a != 0) mantissa_a |= 0x04000000;
    if (exponent_b != 0) mantissa_b |= 0x04000000;

    while (exponent_a < exponent_b) {
        mantissa_a >>= 1;
        exponent_a++;
    }
    while (exponent_b < exponent_a) {
        mantissa_b >>= 1;
        exponent_b++;
    }

    int resultSign = 1;
    uint32_t resultMantissa;
    if (sign_a == sign_b) {
        resultMantissa = mantissa_a + mantissa_b;
        resultSign = sign_a;
    } else {
        if (mantissa_a >= mantissa_b) {
            resultMantissa = mantissa_a - mantissa_b;
            resultSign = sign_a;
        } else {
            resultMantissa = mantissa_b - mantissa_a;
            resultSign = sign_b;
        }
    }

    int resultExponent = exponent_a;
    while (resultMantissa >= 0x08000000 && resultExponent < 31) {
        resultMantissa >>= 1;
        resultExponent++;
    }

    while (resultExponent > 0 && !(resultMantissa & 0x04000000) && resultExponent < 31) {
        resultMantissa <<= 1;
        resultExponent--;
    }

    if (resultExponent >= 31) {
        resultMantissa = 0;
        resultExponent = 31;
    }

    if (resultExponent != 0) {
        resultMantissa &= 0x03FFFFFF;
    }

    NewFloat result = ((uint32_t)resultSign << 31) | ((resultExponent & 0x1F) << 26) | (resultMantissa);
    return result;
}

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
            n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        } else if (part_num == 2) {
            scanf("%f", &f1);
            n1 = float_to_nfloat(f1);
            nfloat_debug(n1);
        } else if (part_num == 3) {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_print(n1);
        } else {
            scanf("%s ", s1);

            if (s1[0] == 'd') {
                scanf("%f", &f1);
                n1 = float_to_nfloat(f1);
                n1 = nfloat_double(n1);
            } else {
                scanf("%f %f", &f1, &f2);
                n1 = float_to_nfloat(f1);
                n2 = float_to_nfloat(f2);
                n1 = nfloat_add(n1, n2);
            }

            nfloat_print(n1);
        }
    }
}
