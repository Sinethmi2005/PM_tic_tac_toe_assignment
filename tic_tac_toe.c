#include <stdio.h>
#include <stdlib.h> //standard library
#include <string.h>
#include <time.h> //use to random timing stuff

// Setup the game board
    char **init_Board(int n, FILE **logFile) {
    char **board = malloc(n * sizeof(char *));
     for (int i = 0; i < n; i++) {
        board[i] = malloc(n * sizeof(char));
        for (int j = 0; j < n; j++)
            board[i][j] = ' ';
    }
// Opens a log file
    *logFile = fopen("game_log.txt", "w");
    if (!*logFile)
        printf("Warning:not open log file\n");

    return board;
}

// Print the game board on screen
void draw_board(char **board, int size) {
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
int is_Full(char **board, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// Save board into log file
   void log_board(char **board, int size, FILE *logFile) {
    if (!logFile) return;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(logFile, "%c ", board[i][j]);
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "------\n");
    fflush(logFile); //make sure everything written to the file
}

// clean up memory and close the log file
void free_board(char **board, int size, FILE *logFile) {
    for (int i = 0; i < size; i++) free(board[i]);
    free(board);
    if (logFile) 
    fclose(logFile);
}

// player move
void user_move(char **board, int size, char sym, FILE *logFile) {
    int row, col;
    while (1) { //loop until give a valid move
        printf("Enter a row and a column (1-%d): ", size);
        if (scanf("%d %d", &row, &col) != 2) {
            while (getchar() != '\n'); //to clear bad input
            printf("Invalid input \n");
            continue;
        }
        row--; col--;
        if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ') {
            board[row][col] = sym;
            if (logFile) 
            fprintf(logFile, "%c placed at row %d, column %d\n", sym, row+1, col+1);
            break;
        } else {
            printf("Invalid move.Try again!\n");
        }
    }
    log_board(board, size, logFile); //saves the entire board
}

// Computer move
void computer_move(char **board, int size, char sym, FILE *logFile) {
    int row, col;

    do {
        row = rand() % size;
        col = rand() % size;
    } while (board[row][col] != ' ');

    board[row][col] = sym;
    printf("Computer placed at (%d,%d)\n", row + 1, col + 1);

    if (logFile)
        fprintf(logFile, "Computer %c -> (%d,%d)\n", sym, row + 1, col + 1);

    log_board(board, size, logFile);
}

// Main game
int main() {
    int size, mode;
    FILE *logFile;
    char symbol[3] = {'X', 'O', 'Z'};
    char name[3][20];
    int isComputer[3] = {0, 0, 0}; //check whether a human or computer

    printf("   Welcome to Tic Tac Toe\n");
    printf("___LET'S PLAY TIC_TAC_TOE!___");
    printf("\n");
    printf("\nEnter the board size (3–10): ");
    scanf("%d", &size);
    if (size < 3 || size > 10) size = 3;
    char **board = init_Board(size, &logFile); //set up the board with empty spaces

    printf("Select mode:\n1. User vs User\n2. User vs Computer\n3. 3 Players\nSelect a choice: ");
    scanf("%d", &mode);    
    printf("\n");

//set up the players based on game mode you choose
    if (mode == 1) {
        printf("Enter Player 1 name: "); scanf("%s", name[0]);
        printf("Enter Player 2 name: "); scanf("%s", name[1]);
        
    } else if (mode == 2) {
        printf("Enter Your name: "); scanf("%s", name[0]);
        strcpy(name[1], "Computer");
        isComputer[1] = 1;
        
    } else if (mode == 3) {
        for (int i = 0; i < 3; i++) {
            printf("Enter Player %d name: ", i + 1); scanf("%s", name[i]);
            printf("Is player %d a computer?\n (1 = Yes, 0 = No): ", i + 1); scanf("%d", &isComputer[i]);
        }
        if (isComputer[0] && isComputer[1] && isComputer[2]) {
            printf("At least one player should be a human!\n");
            free_board(board, size, logFile);
            return 1;
        }
    }
    
//main game loop
    int chance = 0; //(chance 0 = player 1,chance 1 = player 2,chance 2 = player 3)
    while (1) {
        draw_board(board, size);
        printf("%s's chance (%c)\n", name[chance], symbol[chance]);

        if (isComputer[chance])
            computer_move(board, size, symbol[chance], logFile);
        else
            user_move(board, size, symbol[chance], logFile);

// Check if player won
        int win = 0;
        char sym = symbol[chance]; //get current player's symbol

// Checking columns
    for (int j = 0; j < size && win==0; j++) {
            int match = 1;
            for (int i = 0; i < size; i++) {
                if (board[i][j] != sym) {
                    match = 0;
                    break;
                }
            }
            if (match) { 
                win = 1;
                break;
                }
        }
        
// Checking rows
        for (int i = 0; i < size; i++) {
            int match = 1;
            for (int j = 0; j < size; j++) {
                if (board[i][j] != sym) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                win = 1;
            break; 
            }
        }

// Checking diagonals
        int diagonal1 = 1, diagonal2 = 1;
        for (int i = 0; i < size; i++) {
            if (board[i][i] != sym) diagonal1 = 0;
            if (board[i][size - i - 1] != sym) diagonal2 = 0;
        }
        if (diagonal1 ==1 || diagonal2 ==1) 
        win = 1;

        if (win) {
            draw_board(board, size);
            printf("%s is the winner!\n", name[chance]);
            break;
        }

        if (is_Full(board, size)) {
            draw_board(board, size);
            printf("It's a draw!\n");
            break;
        }

       if (mode == 3) {
          chance = (chance + 1) % 3;
}
        else {
           chance = 1 -chance ;
}
    }
    
    printf("-------------------------------\n");
    printf("__Thanks for playing__\n");
    free_board(board, size, logFile);//release the memory
    return 0;
}
