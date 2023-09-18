#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DiceRoll() {
    return rand() % 6 + 1;
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
    } else if (dice1 == 1 && dice2 == 2 && dice3 == 3) {
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
    srand(time(0)); 

    int Player1Life = 3;
    int Player2Life = 3;
    int Round = 1;  

    while (Player1Life > 0 && Player2Life > 0) {
        printf("Turn %d player 1: r\n", Round);

        int Player1Dice[3];
        for (int i = 0; i < 3; i++) {
            Player1Dice[i] = DiceRoll();
        }

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (Player1Dice[j] < Player1Dice[i]) {
                    int temporary = Player1Dice[i];
                    Player1Dice[i] = Player1Dice[j];
                    Player1Dice[j] = temporary;
                }
            }
        }

        int Player1Score = ScoreSystem(Player1Dice[0], Player1Dice[1], Player1Dice[2]);

        printf("You rolled: %d %d %d = %d points\n", Player1Dice[0], Player1Dice[1], Player1Dice[2], Player1Score);
        printf("Turn %d player 1: s\n", Round);
        printf("Turn %d player 2: r\n", Round);

        Round++;

        int Player2Dice[3];
        for (int i = 0; i < 3; i++) {
            Player2Dice[i] = DiceRoll();
        }

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (Player2Dice[j] < Player2Dice[i]) {
                    int temporary = Player2Dice[i];
                    Player2Dice[i] = Player2Dice[j];
                    Player2Dice[j] = temporary;
                }
            }
        }

        int Player2Score = ScoreSystem(Player2Dice[0], Player2Dice[1], Player2Dice[2]);

        printf("You rolled: %d %d %d = %d points\n", Player2Dice[0], Player2Dice[1], Player2Dice[2], Player2Score);
        printf("Turn %d player 2: s\n", Round);

        if (Player1Score > Player2Score) {
            Player2Life--;
            printf("Player 1 wins this Round with %d points\n", Player1Score);
        } 
        else if (Player2Score > Player1Score) {
            Player1Life--;
            printf("Player 2 wins this Round with %d points\n", Player2Score);
        } 
        else {
            printf("Both players tied this Round with %d points\n", Player1Score);
        }

        printf("Player 1 lives = %d\n", Player1Life);
        printf("Player 2 lives = %d\n\n", Player2Life);
    }

    if (Player1Life <= 0) {
        printf("Player 2 wins!\n");
    } else {
        printf("Player 1 wins!\n");
    }

    return 0;
}