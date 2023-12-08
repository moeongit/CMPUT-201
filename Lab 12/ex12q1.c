#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat; // Define NewFloat as an alias for 32-bit unsigned integer

// Function: Convert a string of binary digits to NewFloat
NewFloat bits_string_to_nfloat(char *s) {
    NewFloat result = 0; // Initialize result to zero
    for (; *s; s++) { // Loop through each character in the string
        result = (result << 1) | (*s - '0'); // Shift result left and add the new digit
    }
    return result; // Return the binary representation as NewFloat
}

// Function: Print the binary representation of a NewFloat
void nfloat_debug(NewFloat f){
    printf("%d ", (f >> 31) & 1); // Print the sign bit
    // &1 just isolates the rightmost bit
    // Print the exponent part
    for (int i = 30; i >= 26; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf(" ");
    
    // Print the mantissa part
    for (int i = 25; i >= 0; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf("\n"); // End the line after printing
}

// Function: Convert a standard float to a NewFloat
NewFloat float_to_nfloat(float f) {
    uint32_t floatBits; // Temporary variable to hold the binary representation of the float
    memcpy(&floatBits, &f, sizeof(float)); // Copy the float into the uint32_t
    // this is how we access the bits
    // Extract the sign, exponent, and mantissa from the float
    uint32_t sign = (floatBits >> 31) & 0x1;
    int32_t exponent = ((floatBits >> 23) & 0xFF) - 127 + 15; // Adjust the exponent
    uint32_t mantissa = (floatBits & 0x7FFFFF); // 23 bits all set to 1 except first

    // Normalize the exponent and mantissa for the NewFloat representation
    if (exponent >= 31) {
        exponent = 31; 
        mantissa = 0;
    } else if (exponent <= 0) {
        while (exponent < 0 && mantissa != 0) {
            mantissa >>= 1;
            exponent++;
        }
        if (exponent < 0) {
            exponent = 0;
        }
    }
    mantissa <<= 3; // Adjust the mantissa for the NewFloat format

    // Assemble and return the NewFloat
    NewFloat nf = (sign << 31) | ((exponent & 0x1F) << 26) | (mantissa & 0x03FFFFFF);
    return nf;
}

// Function: Print a NewFloat as a decimal number
void nfloat_print(NewFloat f) {
    int sign = (f >> 31) & 1; // Extract the sign
    int exponent = ((f >> 26) & 0x1F) - 15; // Extract and adjust the exponent
    uint32_t mantissa = f & 0x03FFFFFF; // Extract the mantissa

    // Handle special case of zero
    if (exponent == -15 && mantissa == 0) {
        if (sign) {
            printf("-0.0000000\n"); // Print negative zero
        } else {
            printf(" 0.0000000\n"); // Print positive zero
        }
        return;
    }

    // Convert the NewFloat to a decimal value
    double decimalValue = mantissa;
    if (exponent == -15) {
        decimalValue /= (1 << 25); // Handle denormalized numbers
    } else {
        decimalValue = (1 << 26) | mantissa; // Add the implicit leading 1 for normalized numbers
        if (exponent > 0) {
            while (exponent--) decimalValue *= 2; // Scale up for positive exponents
        } else {
            while (exponent++) decimalValue /= 2; // Scale down for negative exponents
        }
    }
    
    if (sign) {
        decimalValue = -decimalValue; // Apply the sign
    }

    decimalValue /= (1 << 26); // Normalize the value

    printf("%.7f\n", decimalValue); // Print the decimal value with 7 digits precision
}

// Function: Double the value of a NewFloat
NewFloat nfloat_double(NewFloat f) {
    if ((f & 0x7FFFFFFF) == 0) { // If f is zero or negative zero, return as is
        return f;
    }

    int exponent = (f >> 26) & 0x1F; // Extract the exponent, masks out all but last 5 bits
    if (exponent == 0) { // Handle denormalized numbers
        uint32_t mantissa = f & 0x03FFFFFF;
        mantissa <<= 1; // Double the mantissa
        if (mantissa & (1 << 26)) { // Check for mantissa overflow
            exponent++; // Increment exponent if overflow occurs
            mantissa &= 0x03FFFFFF; // Normalize mantissa
        }
        return (f & 0x80000000) | (exponent << 26) | mantissa; 
    } else if (exponent < 30) { // Normal case: simply increment the exponent
        exponent++;
        return (f & 0x80000000) | (exponent << 26) | (f & 0x03FFFFFF);
    } else { // Handle overflow to infinity
        return (f & 0x80000000) | (31 << 26); 
    }
}

// Function: Add two NewFloat numbers
NewFloat nfloat_add(NewFloat a, NewFloat b) {
    // Extract the sign and exponent of both numbers
    int sign_a = (a >> 31) & 1;
    int sign_b = (b >> 31) & 1;
    int exponent_a = (a >> 26) & 0x1F;
    int exponent_b = (b >> 26) & 0x1F;
    uint32_t mantissa_a = a & 0x03FFFFFF;
    uint32_t mantissa_b = b & 0x03FFFFFF;

    // Normalize mantissas if exponents are non-zero
    if (exponent_a != 0) mantissa_a |= 0x04000000;  //add an implicit leading 1
    if (exponent_b != 0) mantissa_b |= 0x04000000;

    // Align exponents by shifting the mantissa of the smaller exponent
    while (exponent_a < exponent_b) {
        mantissa_a >>= 1;
        exponent_a++;
    }
    while (exponent_b < exponent_a) {
        mantissa_b >>= 1;
        exponent_b++;
    }

    // Initialize variables for the result's sign and mantissa
    int resultSign;
    uint32_t resultMantissa;

    // Add or subtract mantissas based on their signs
    if (sign_a == sign_b) {
        resultMantissa = mantissa_a + mantissa_b;
        resultSign = sign_a; // Same sign for both numbers
    } else {
        // Different signs - perform subtraction
        if (mantissa_a >= mantissa_b) {
            resultMantissa = mantissa_a - mantissa_b;
            resultSign = sign_a; // Result takes sign of a
        } else {
            resultMantissa = mantissa_b - mantissa_a;
            resultSign = sign_b; // Result takes sign of b
        }
    }

    // Normalize the result
    int resultExponent = exponent_a;
    while (resultMantissa >= 0x08000000 && resultExponent < 31) {
        resultMantissa >>= 1;
        resultExponent++;
    }

    // Further normalization if needed
    while (resultExponent > 0 && !(resultMantissa & 0x04000000) && resultExponent < 31) {
        resultMantissa <<= 1;
        resultExponent--;
    }

    // Handle overflow to infinity
    if (resultExponent >= 31) {
        resultMantissa = 0;
        resultExponent = 31;
    }

    // Adjust mantissa if exponent is non-zero
    if (resultExponent != 0) {
        resultMantissa &= 0x03FFFFFF;
    }

    // Reassemble the result NewFloat from its components
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
