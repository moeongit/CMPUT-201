#include <stdio.h>
#include <string.h>

#define MaxWordLength 11
#define MaxWords 20

int min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < c) return b;
    return c;
}

int levenshteinDistance(const char *a, const char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    int dp[len_a + 1][len_b + 1];

    for (int i = 0; i <= len_a; i++) dp[i][0] = i;
    for (int j = 0; j <= len_b; j++) dp[0][j] = j;

    for (int i = 1; i <= len_a; i++) {
        for (int j = 1; j <= len_b; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost);
        }
    }
    return dp[len_a][len_b];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char dictionary[MaxWords][MaxWordLength];

    for (int i = 0; i < n; i++) {
        scanf("%s", dictionary[i]);
    }

    getchar(); 

    char line[200]; 

    for (int i = 0; i < m; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; 
        }

        char *word = strtok(line, " \n"); 

        while (word != NULL) {
            int MinDistance = MaxWordLength, index = 0;
            for (int j = 0; j < n; j++) {
                int distance = levenshteinDistance(word, dictionary[j]);
                if (distance < MinDistance) {
                    MinDistance = distance;
                    index = j;
                }
            }
            
            printf("%s", dictionary[index]);
            word = strtok(NULL, " \n");

            if (word != NULL) {
                printf(" ");
            }
        }
        printf("\n"); 
    }
    return 0;
}
