#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <windows.h>

void showInstructions();
void showGlobalBoard();
void showLocalBoard(char local_board_state[]);

int main(){
    char local_board_1_state[] = {'1',
                                  'O', 'O', 'O',
                                  ' ', 'X', ' ',
                                  ' ', ' ', ' '};

    int init_local_board_choice = 0;
    int do_while_flag = 0;

    showInstructions();

    do{
        showGlobalBoard();

        printf("Choose a local TicTacToe spot. ");
        scanf("%d", &init_local_board_choice);

        if (init_local_board_choice == 1)
            showLocalBoard(local_board_1_state);
            do_while_flag = 1;


    } while (do_while_flag == 0);
    


    return 0;
}

void showInstructions(){
    printf("Welcome to Super TicTacToe!\n");
    printf("Super TicTacToe is not that different from the regular TicTacToe.\n");
    printf("Super TicTacToe adds another layer of difficulty by making the game have a \"global\"\n");
    printf("TicTacToe, and a \"local\" TicTacToe.\n\n");

    printf("Local TicTacToe: is played like a regular TicTacToe.\n");
    printf("Global TicTacToe: Local TicTacToes has to have a winner in order for a symbol\n");
    printf("to be placed in a spot in the Global TicTacToe.\n\n\n");
}

void showGlobalBoard(){
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    1    |     2     |     3    |\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    4    |     5     |     6    |\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    7    |     8     |     9    |\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n\n");
}

void showLocalBoard(char local_board_state[]){
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", local_board_state[1], local_board_state[2], local_board_state[3]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", local_board_state[4], local_board_state[5], local_board_state[6]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", local_board_state[7], local_board_state[8], local_board_state[9]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n\n");
}