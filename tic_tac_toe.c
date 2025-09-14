#include <stdio.h>
#include <stdlib.h>

char** initialize_board(int n);
void display_board(char** board, int n);
int is_valid_move(char** board, int n, int row, int column);
int check_win(char** board, int n, char symbol);
int check_draw(char** board, int n);
void log_file(FILE* logfile, char** board, int n);
void computer_move(char** board, int n, int *row, int *column);

void Two_player_game(int n);
void User_vs_Computer_game(int n);
void Multiplayer_game(int n);

int main() {
    int n;
    int game_mode;

    printf("** Tic Tac Toe Game ***\n");

    printf("Enter board size n (3 <= n <= 10): ");
    scanf("%d", &n);
    if (n < 3 || n > 10) {
        printf("Invalid board size!\n");
        return 0;
    }

    printf("\n* Game Modes *\n");
    printf("1. Two players (User VS User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three players\n");
    printf("Select game mode: ");
    scanf("%d", &game_mode);
   
switch(game_mode){
    case 1: 
        Two_player_game(n);
        break;
    case 2: 
        User_vs_Computer_game(n);
        break;
    case 3: 
        Multiplayer_game(n);
        break;
    default: 
        printf("Invalid Mode try again!");
}

    return 0;
}
char** initialize_board(int n) {
    char* board = (char*)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    return board;
}
void display_board(char** board, int n) {
    printf("  ");
    for (int column = 0; column < n; column++) {
        printf(" %d ", column);
    }
    printf("\n");
    
    for (int row = 0; row < n; row++) {
        printf("%d ", row);
        for (int column = 0; column < n; column++) {
            printf("|%c", board[row][column]);
        }
        printf("|\n");
    }
}
void Two_player_game(int n){

}
void User_vs_Computer_game(int n){

}
void Multiplayer_game(int n){

}

return 0;
 
}

