#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <windows.h>

void showInstructions();
void showGlobalBoard(char global_board_state[]);
void showLocalBoard(char local_board_state[]);

int anyLocalBoardChoice(char local_board_states[9][10], char player_sign, int *enemy_turn_pointer);
int nextLocalBoard(char local_board_states[9][10], char player_sign, int next_local, int *enemy_turn_pointer);

int generateRandomNumber(int max);

// (char (*local_board_state)[10] means a pointer that points to an array that has 10 characters
int editLocalBoard(char (*local_board_state)[10], char turn_sign, int *enemy_turn_pointer);
void checkLocalBoard(char local_board_state[], char global_board_state[]);

int main(){
    char player_sign = 'X';

    char global_board_state[] = {'1', '2', '3',
                                 '4', '5', '6',
                                 '7', '8', '9'};
                                  
    char local_board_states[9][10] = {{'1', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'2', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'3', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'4', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'5', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'6', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'7', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'8', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                                {'9', '1', '2', '3', '4', '5', '6', '7', '8', '9'}};

    int choose_any_local = 0;
    int do_while_flag = 0;
    int next_local = 0;
    int enemy_turn = 0;

    int *enemy_turn_pointer = &enemy_turn;

    showInstructions();

    do{
        printf("Global Board:\n\n");
        showGlobalBoard(global_board_state);

        if (choose_any_local == 0){
            if (enemy_turn == 0 && player_sign == 'X'){
                next_local = anyLocalBoardChoice(local_board_states, player_sign, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                enemy_turn = 0;
                player_sign = 'O';
            } else {
                next_local = anyLocalBoardChoice(local_board_states, player_sign, enemy_turn_pointer);

                Sleep(1500);
                system("cls");
                
                enemy_turn = 0;
                player_sign = 'X';
            }
            choose_any_local = 0;
        } else{
            if (enemy_turn == 0 && player_sign == 'X'){
                next_local = nextLocalBoard(local_board_states, player_sign, next_local, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                enemy_turn = 0;
                player_sign = 'O';
            } else {
                next_local = nextLocalBoard(local_board_states, player_sign, next_local, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                enemy_turn = 0;
                player_sign = 'X';
            }
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
    printf("\nLocal board %c:\n\n", local_board_state[0]);

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

int anyLocalBoardChoice(char local_board_states[9][10], char player_sign, int *enemy_turn_pointer){
    int local_board_choice = 0;
    int local_board_spot = 0;
    char (*current_local_board_pointer)[10];

    if (*enemy_turn_pointer == 0){
        printf("Choose a local TicTacToe spot. ");
        scanf("%d", &local_board_choice);
    } else {
        local_board_choice = generateRandomNumber(8) + 1;
    }    

    showLocalBoard(local_board_states[local_board_choice - 1]);

    // Ampersand sign '&' points to the entires array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[local_board_choice - 1];

    local_board_spot = editLocalBoard(current_local_board_pointer, player_sign, enemy_turn_pointer);

    // switch (local_board_choice){
    //     case 1:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '1', player_sign, enemy_turn_pointer);
    //         break;
    //     case 2:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '2', player_sign, enemy_turn_pointer);
    //         break;
    //     case 3:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '3', player_sign, enemy_turn_pointer);
    //         break;
    //     case 4:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '4', player_sign, enemy_turn_pointer);
    //         break;
    //     case 5:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '5', player_sign, enemy_turn_pointer);
    //         break;
    //     case 6:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '6', player_sign, enemy_turn_pointer);
    //         break;
    //     case 7:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '7', player_sign, enemy_turn_pointer);
    //         break;
    //     case 8:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '8', player_sign, enemy_turn_pointer);
    //         break;
    //     case 9:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '9', player_sign, enemy_turn_pointer);
    //         break;
    // }

    showLocalBoard(local_board_states[local_board_choice - 1]);

    return local_board_spot;

}

int nextLocalBoard(char local_board_states[9][10], char player_sign, int next_local, int *enemy_turn_pointer){
    int local_board_spot = 0;

    // Initialize a pointer that leads to an array that has 10 characters
    char (*current_local_board_pointer)[10];

    showLocalBoard(local_board_states[next_local - 1]);

    // Ampersand sign '&' points to the entires array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[next_local - 1];

    local_board_spot = editLocalBoard(current_local_board_pointer, player_sign, enemy_turn_pointer);

    // switch (next_local){
    //     case 1:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '1', player_sign, enemy_turn_pointer);
    //         break;
    //     case 2:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '2', player_sign, enemy_turn_pointer);
    //         break;
    //     case 3:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '3', player_sign, enemy_turn_pointer);
    //         break;
    //     case 4:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '4', player_sign, enemy_turn_pointer);
    //         break;
    //     case 5:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '5', player_sign, enemy_turn_pointer);
    //         break;
    //     case 6:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '6', player_sign, enemy_turn_pointer);
    //         break;
    //     case 7:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '7', player_sign, enemy_turn_pointer);
    //         break;
    //     case 8:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '8', player_sign, enemy_turn_pointer);
    //         break;
    //     case 9:
    //         local_board_spot = editLocalBoard(current_local_board_pointer, '9', player_sign, enemy_turn_pointer);
    //         break;
    // }

    showLocalBoard(local_board_states[next_local - 1]);

    return local_board_spot;
}

int generateRandomNumber(int max){
    srand(time(NULL));
    return rand() % max;
}

int editLocalBoard(char (*local_board_state)[10], char turn_sign, int *enemy_turn_pointer){
    int player_spot_choice = 0;

    do{
        if (*enemy_turn_pointer == 0){
            printf("Choose a spot to place %c.\n", turn_sign);
            scanf("%d", &player_spot_choice);
    
            if (*(*(local_board_state) + player_spot_choice) == 'X' || 
                *(*(local_board_state) + player_spot_choice) == 'O'){

                printf("That spot is already occupied. Choose another spot on the board. \n");
            }
        } else {
            player_spot_choice = generateRandomNumber(8) + 1;

            if (*(*(local_board_state) + player_spot_choice) != 'X' || 
                *(*(local_board_state) + player_spot_choice) != 'O'){

                break;
            }
        }

    }while (*(*(local_board_state) + player_spot_choice) == 'X' || 
            *(*(local_board_state) + player_spot_choice) == 'O');

    // The commented line of code below is wrong because this function is already given the ith array of the 2d array
    // It is just needed to get the position of the jth element.
    // For more understanding, check geeksforgeeks link

    // *(*(local_board_state + int_local_board_number - player_spot_choice) + player_spot_choice) = 'X';

    *(*(local_board_state) + player_spot_choice) = 'X';
    
    return player_spot_choice;
}

// void checkLocalBoard(char local_board_state[], char global_board_state[]){
//     if (local_board_state[0] == local_board_state[1] && local_board_state[1] == local_board_state[2]){
//         printf("");
//     } else if (local_board_state[0] == local_board_state[4] && local_board_state[1] == local_board_state[2]){

//     }

// }