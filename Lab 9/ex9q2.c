#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Reverse(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

char* StringAddition(char *num1, char *num2) {
    int Len1 = strlen(num1), Len2 = strlen(num2);
    int MaxLength = Len1 > Len2 ? Len1 : Len2;
    char *result = calloc(MaxLength + 2, sizeof(char)); 

    Reverse(num1);
    Reverse(num2);

    int carry = 0;

    for (int i = 0; i < MaxLength; i++) {
        int digit1 = i < Len1 ? num1[i] - '0' : 0;
        int digit2 = i < Len2 ? num2[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result[i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        result[MaxLength] = carry + '0';
    }

    Reverse(num1);
    Reverse(num2);
    Reverse(result);

    return result;
}

char* StringConcatenation(char *num1, char *num2) {
    char *result = malloc(strlen(num1) + strlen(num2) + 1);
    strcpy(result, num1);
    strcat(result, num2);
    return result;
}

char* StringRotation(char *num, int rotation) {
    int length = strlen(num);
    rotation = rotation % length; 
    char *result = malloc(length + 1);

    for (int i = 0; i < length; i++) {
        result[i] = num[(i + rotation) % length];
    }

    result[length] = '\0';

    if (result[0] == '0' && strcmp(result, "0") != 0) {
 
        int FirstNonZero = 0;
        while (result[FirstNonZero] == '0') {
            FirstNonZero++;
        }

        for (int i = FirstNonZero; i <= length; i++) {
            result[i - FirstNonZero] = result[i];
        }
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    char op[5], num1[10100], num2[10100];

    for (int i = 0; i < n; i++) {
        scanf("%s %s %s", num1, op, num2);

        if (strcmp(op, "+") == 0) {
            char *result = StringAddition(num1, num2);
            printf("%s\n", result);
            free(result);
        } 
        
        else if (strcmp(op, "@") == 0) {
            char *result = StringConcatenation(num1, num2);
            printf("%s\n", result);
            free(result);
        } 
        
        else if (strcmp(op, "rot") == 0) {
            int rotation = atoi(num2);
            char *result = StringRotation(num1, rotation);
            printf("%s\n", result);
            free(result);
        }
    }
    
    return 0;
}