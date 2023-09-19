#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DiceRoll() {
    return rand() % 6 + 1;
}

void DiceSorting(int dice[]) {
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (dice[j] < dice[i]) {
                int temporary = dice[i];
                dice[i] = dice[j];
                dice[j] = temporary;
            }
        }
    }
}

int ScoreSystem(int dice1, int dice2, int dice3) {
    int Score = 0;

    if (dice1 == dice2 && dice2 == dice3) {
        if (dice1 == 1) {
            Score = 999;
        } else if (dice1 == 2) {
            Score = 998;
        } else if (dice1 == 3) {
            Score = 997;
        } else if (dice1 == 4) {
            Score = 996;
        } else if (dice1 == 5) {
            Score = 995;
        } else if (dice1 == 6) {
            Score = 994;
        }
    } 
    else if (dice1 == 1 && dice2 == 2 && dice3 == 3) {
        Score = 993;
    } 
    else if (dice1 == 4 && dice2 == 5 && dice3 == 6) {
        Score = 1000;
    } 
    else {
        Score = dice3 * 100 + dice2 * 10 + dice1;
    }
    return Score;
}

int main() {
    srand(time(0));

    int Player1Life = 3;
    int Player2Life = 3;
    int Turn = 1;
    char user_input;
    int Score1, Score2;
    int dice[3];

    while (Player1Life > 0 && Player2Life > 0) {
        Score1 = 0;

        // Player 1's turn
        for (int i = 0; i < 3; i++) {
            printf("Turn %d player 1: ", Turn++);
            scanf(" %c", &user_input);

            if (user_input == 'r') {
                dice[0] = DiceRoll();
                dice[1] = DiceRoll();
                dice[2] = DiceRoll();
                DiceSorting(dice);
                Score1 = ScoreSystem(dice[0], dice[1], dice[2]);
                printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], Score1);
            } else if (user_input == 's') {
                break;
            }
        }

        Turn = 1;
        Score2 = 0;

        // Player 2's turn
        for (int i = 0; i < 3; i++) {
            printf("Turn %d player 2: ", Turn++);
            scanf(" %c", &user_input);

            if (user_input == 'r') {
                dice[0] = DiceRoll();
                dice[1] = DiceRoll();
                dice[2] = DiceRoll();
                DiceSorting(dice);
                Score2 = ScoreSystem(dice[0], dice[1], dice[2]);
                printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], Score2);
            } else if (user_input == 's') {
                break;
            }
        }

        Turn = 1;

        if (Score1 > Score2) {
            printf("Player 1 wins this round with %d points\n", Score1);
            Player2Life--;
        } else if (Score2 > Score1) {
            printf("Player 2 wins this round with %d points\n", Score2);
            Player1Life--;
        } else {
            printf("Both players tied this round with %d points\n", Score1);
        }

        printf("Player 1 lives = %d\n", Player1Life);
        printf("Player 2 lives = %d\n\n", Player2Life);
    }

    if (Player1Life == 0) {
        printf("Player 2 wins!\n");
    } else {
        printf("Player 1 wins!\n");
    }

    return 0;
}