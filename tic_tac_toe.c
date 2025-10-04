#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variables
char **board;
int size;
FILE *logFile;

// Setup the board
void initBoard(int n) {
    size = n;
    board = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(char));
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
    }
    
// Open a logfile
    logFile = fopen("game_log.txt", "w");
    if (!logFile)
        printf("Warning:not open log file\n");
}
// Save board into a file
void logBoard() {
    if (!logFile) return;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(logFile, "%c ", board[i][j]);
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "------\n");
    fflush(logFile);
}

// Print the board on screen
void drawBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Check whether board is full
int isFull() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// making a move
void userMove(char sym) {
    int m, n;
    while (1) {
        printf("Enter row and column (1-%d): ", size);
        if (scanf("%d %d", &m, &n) != 2) {
            while (getchar() != '\n');
            printf("Invalid input \n");
            continue;
        }
        m--; n--;
        if (m >= 0 && m < size && n >= 0 && n < size && board[m][n] == ' ') {
            board[m][n] = sym;
            if (logFile) 
            fprintf(logFile, "%c played at row %d, column %d\n", sym, m+1, n+1);
            break;
        } else {
            printf("Invalid move. Try again!\n");
        }
    }
    logBoard();
}


