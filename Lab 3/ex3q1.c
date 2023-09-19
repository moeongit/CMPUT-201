#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DiceRoll() {
    return rand() % 6 + 1;
}

void SortDice(int dice[]) {
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (dice[j] < dice[i]) {
                int temp = dice[i];
                dice[i] = dice[j];
                dice[j] = temp;
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
        int DiceList[3] = {dice1, dice2, dice3};

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (DiceList[j] < DiceList[i]) {
                    int temporary = DiceList[i];
                    DiceList[i] = DiceList[j];
                    DiceList[j] = temporary;
                }
            }
        }
        Score = DiceList[2] * 100 + DiceList[1] * 10 + DiceList[0];
    }

    return Score;
}

int main() {
    srand(time(NULL));

    int player1_lives = 3;
    int player2_lives = 3;
    int turn_count = 1;
    char user_input;
    int score1, score2;
    int dice[3];

    while (player1_lives > 0 && player2_lives > 0) {
        score1 = 0;

        // Player 1's turn
        for (int i = 0; i < 3; i++) {
            printf("Turn %d player 1: ", turn_count++);
            scanf(" %c", &user_input);

            if (user_input == 'r') {
                dice[0] = DiceRoll();
                dice[1] = DiceRoll();
                dice[2] = DiceRoll();
                SortDice(dice);
                score1 = ScoreSystem(dice[0], dice[1], dice[2]);
                printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], score1);
            } else if (user_input == 's') {
                break;
            }
        }

        turn_count = 1;

        score2 = 0;

        // Player 2's turn
        for (int i = 0; i < 3; i++) {
            printf("Turn %d player 2: ", turn_count++);
            scanf(" %c", &user_input);

            if (user_input == 'r') {
                dice[0] = DiceRoll();
                dice[1] = DiceRoll();
                dice[2] = DiceRoll();
                SortDice(dice);
                score2 = ScoreSystem(dice[0], dice[1], dice[2]);
                printf("You rolled: %d %d %d = %d points\n", dice[0], dice[1], dice[2], score2);
            } else if (user_input == 's') {
                break;
            }
        }

        // Reset turn counter for next round
        turn_count = 1;

        // Determine winner of the round
        if (score1 > score2) {
            printf("Player 1 wins this round with %d points\n", score1);
            player2_lives--;
        } else if (score2 > score1) {
            printf("Player 2 wins this round with %d points\n", score2);
            player1_lives--;
        } else {
            printf("Both players tied this round with %d points\n", score1);
        }

        printf("Player 1 lives = %d\n", player1_lives);
        printf("Player 2 lives = %d\n\n", player2_lives);
    }

    // Determine overall winner
    if (player1_lives == 0) {
        printf("\nPlayer 2 wins!\n");
    } else {
        printf("\nPlayer 1 wins!\n");
    }

    return 0;
}