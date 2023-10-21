#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <windows.h>

void showInstructions();
void showGlobalBoard(char global_board_state[]);
void showLocalBoard(char local_board_state[]);

void anyLocalBoardChoice(char local_board_states[9][10], char player_sign);

// (char (*local_board_state)[10] means a pointer that points to an array that has 10 characters
void editLocalBoard(char (*local_board_state)[10], char char_local_board_number, char player_sign);
void checkLocalBoard(char local_board_state[], char global_board_state[]);

int main(){
    char player_sign = 'X';

    char global_board_state[] = {'1', '2', '3',
                                 '4', '5', '6',
                                 '7', '8', '9'};
                                  
    char local_board_states[9][10] = {{'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'2', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'9', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    int choose_any_local = 0;
    int location_of_target_spot = 0;
    int do_while_flag = 0;

    showInstructions();

    do{
        showGlobalBoard(global_board_state);

        if (choose_any_local == 0){
            anyLocalBoardChoice(local_board_states, player_sign);
            do_while_flag = 1;
            // checkLocalBoard(local_board_state[0], global_board_state);
            }
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

void showGlobalBoard(char global_board_state[]){
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", global_board_state[0], global_board_state[1], global_board_state[2]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", global_board_state[3], global_board_state[4], global_board_state[5]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n");
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("|    %c    |     %c     |     %c    |\n", global_board_state[6], global_board_state[7], global_board_state[8]);
    printf("|         |           |          |\n");
    printf("|         |           |          |\n");
    printf("+---------|-----------|----------+\n\n");
}

void showLocalBoard(char local_board_state[]){
    printf("Local board %c:\n\n", local_board_state[0]);

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

void anyLocalBoardChoice(char local_board_states[9][10], char player_sign){
    int local_board_choice = 0;
    char (*current_local_board_pointer)[10];

    printf("Choose a local TicTacToe spot. ");
    scanf("%d", &local_board_choice);

    if (local_board_choice == 1){
        showLocalBoard(local_board_states[local_board_choice - 1]);

        // Ampersand sign '&' points to the entires array, not the first element of the array.
        
        current_local_board_pointer = &local_board_states[0];
        editLocalBoard(current_local_board_pointer, '1', player_sign);

        showLocalBoard(local_board_states[local_board_choice - 1]);
    }

}

void editLocalBoard(char (*local_board_state)[10], char char_local_board_number, char player_sign){
    int player_spot_choice = 0;

    int int_local_board_number = char_local_board_number - '0'; 

    // int_local_board_number is subracted by 1 to match the 0 indexing of the local_board_state array
    int_local_board_number--;

    do{
        printf("Choose a spot to place %c.\n", player_sign);
        scanf("%d", &player_spot_choice);

        if (*(*(local_board_state + int_local_board_number) + player_spot_choice) == 'X' || 
            *(*(local_board_state + int_local_board_number) + player_spot_choice) == 'O'){

            printf("That spot is already occupied. Choose another spot on the board. \n");
        }

    }while (*(*(local_board_state + int_local_board_number) + player_spot_choice) == 'X' || 
            *(*(local_board_state + int_local_board_number) + player_spot_choice) == 'O');

    // Points to the jth element in a 2D Array
    // For more understanding, check geeksforgeeks link

    *(*(local_board_state + int_local_board_number) + player_spot_choice) = 'X';
}

// void checkLocalBoard(char local_board_state[], char global_board_state[]){
//     if (local_board_state[0] == local_board_state[1] && local_board_state[1] == local_board_state[2]){
//         printf("");
//     } else if (local_board_state[0] == local_board_state[4] && local_board_state[1] == local_board_state[2]){

//     }

// }