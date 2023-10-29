
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <windows.h>

void showInstructions();
void showOnlyGlobalBoard(char global_board_state[]);
void showGlobalAndLocal(char global_board_state[], char local_board_state[]);

int anyLocalBoardChoice(char local_board_states[9][10], char global_board_state[], char turn_sign, int *enemy_turn_pointer);
int nextLocalBoard(char local_board_states[9][10], char global_board_state[], char turn_sign, int next_local, int *enemy_turn_pointer);

int checkIfGlobalIsOccupied(char global_board_state[], int choice);

int generateRandomNumber(int max);

// (char (*local_board_state)[10] means a pointer that points to an array that has 10 characters
int editLocalBoard(char (*local_board_state)[10], char turn_sign, int *enemy_turn_pointer);
void checkLocalBoard(char global_board_state[], char local_board_state[], int local_board, char turn_sign);

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
    int global_only = 0;

    int *enemy_turn_pointer = &enemy_turn;

    showInstructions();

    do{ 
        if (global_only == 0){
            printf("Global Board:\n\n");
            showOnlyGlobalBoard(global_board_state);
        }
        
        if (choose_any_local == 0){

            char *global_board_pointer = global_board_state;

            if (enemy_turn == 0){
                next_local = anyLocalBoardChoice(local_board_states, global_board_pointer, player_sign, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                printf("Going to local board %d...", next_local);
                Sleep(1000);
                system("cls");

                enemy_turn = 0;
            } else {
                next_local = anyLocalBoardChoice(local_board_states, global_board_pointer, player_sign, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                printf("Going to local board %d...", next_local);
                Sleep(1000);
                system("cls");
                
                enemy_turn = 0;
            }

            if (player_sign == 'X'){
                player_sign = 'O';
            } else if (player_sign == 'O'){
                player_sign = 'X';
            }

            choose_any_local = 1;
        } else{
            if (enemy_turn == 0){
                next_local = nextLocalBoard(local_board_states, global_board_state, player_sign, next_local, enemy_turn_pointer);

                Sleep(2000);
                system("cls");

                printf("Going to local board %d...", next_local);
                Sleep(1000);
                system("cls");

                enemy_turn = 0;
            } else {
                next_local = nextLocalBoard(local_board_states, global_board_state, player_sign, next_local, enemy_turn_pointer);

                Sleep(2000);
                system("cls");

                printf("Going to local board %d...", next_local);
                Sleep(1000);
                system("cls");

                enemy_turn = 0;
            }

            if (player_sign == 'X'){
                player_sign = 'O';
            } else if (player_sign == 'O'){
                player_sign = 'X';
            }
        }

        global_only = 1;

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

void showOnlyGlobalBoard(char global_board_state[]){
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

void showGlobalAndLocal(char global_board_state[], char local_board_state[]){
    printf("\n\n           Global Board                             Local Board %c       \n\n", local_board_state[0]);
    printf("+---------|-----------|----------+     +---------|-----------|----------+\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");

    printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
            global_board_state[0], global_board_state[1], global_board_state[2],
            local_board_state[1], local_board_state[2], local_board_state[3]);

    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("+---------|-----------|----------+     +---------|-----------|----------+\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");

    printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
            global_board_state[3], global_board_state[4], global_board_state[5],
            local_board_state[4], local_board_state[5], local_board_state[6]);

    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("+---------|-----------|----------+     +---------|-----------|----------+\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");

    printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
            global_board_state[6], global_board_state[7], global_board_state[8],
            local_board_state[7], local_board_state[8], local_board_state[9]);

    printf("|         |           |          |     |         |           |          |\n");
    printf("|         |           |          |     |         |           |          |\n");
    printf("+---------|-----------|----------+     +---------|-----------|----------+\n\n");
}

int anyLocalBoardChoice(char local_board_states[9][10], char global_board_state[], char turn_sign, int *enemy_turn_pointer){
    int local_board_choice = 0;
    int local_board_spot = 0;
    char (*current_local_board_pointer)[10];

    while (1){
        if (*enemy_turn_pointer == 0){
            printf("Choose a local TicTacToe spot. ");
            scanf("%d", &local_board_choice);
        } else {
            local_board_choice = generateRandomNumber(8) + 1;
        }   

        if (checkIfGlobalIsOccupied(global_board_state, local_board_choice) == 0){
            break;
        } else if (*enemy_turn_pointer == 0){
            printf("That local board has already been won by %c. Find another local board.\n\n", turn_sign);
        }
    }
     

    showGlobalAndLocal(global_board_state, local_board_states[local_board_choice - 1]);

    // Ampersand sign '&' points to the entires array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[local_board_choice - 1];

    local_board_spot = editLocalBoard(current_local_board_pointer, turn_sign, enemy_turn_pointer);

    system("cls");

    printf("Changes made on local board %d (at spot %d):\n\n", local_board_choice, local_board_spot);

    Sleep(1000);

    showGlobalAndLocal(global_board_state, local_board_states[local_board_choice - 1]);

    checkLocalBoard(global_board_state, local_board_states[local_board_choice - 1], local_board_choice, turn_sign);

    return local_board_spot;

}

int nextLocalBoard(char local_board_states[9][10], char global_board_state[], char turn_sign, int next_local, int *enemy_turn_pointer){
    int local_board_spot = 0;

    // Initialize a pointer that leads to an array that has 10 characters
    char (*current_local_board_pointer)[10];

    showGlobalAndLocal(global_board_state, local_board_states[next_local - 1]);
    // showLocalBoard(local_board_states[next_local - 1]);

    // Ampersand sign '&' points to the entires array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[next_local - 1];

    local_board_spot = editLocalBoard(current_local_board_pointer, turn_sign, enemy_turn_pointer);

    system("cls");

    printf("Changes made on local board %d (at spot %d):\n", next_local, local_board_spot);

    Sleep(1000);

    showGlobalAndLocal(global_board_state, local_board_states[next_local - 1]);

    checkLocalBoard(global_board_state, local_board_states[next_local - 1], next_local, turn_sign);

    return local_board_spot;
}

int checkIfGlobalIsOccupied(char global_board_state[], int choice){
    if (global_board_state[choice - 1] == 'X' || global_board_state[choice] == 'O'){
        return 1;
    } else{
        return 0;
    }
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

    *(*(local_board_state) + player_spot_choice) = turn_sign;
    
    return player_spot_choice;
}

void checkLocalBoard(char global_board_state[], char local_board_state[], int local_board, char turn_sign){
    if (local_board_state[1] == local_board_state[2] && local_board_state[2] == local_board_state[3]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[4] == local_board_state[5] && local_board_state[5] == local_board_state[6]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[7] == local_board_state[8] && local_board_state[8] == local_board_state[9]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[1] == local_board_state[4] && local_board_state[4] == local_board_state[7]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[2] == local_board_state[5] && local_board_state[5] == local_board_state[8]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[3] == local_board_state[6] && local_board_state[6] == local_board_state[9]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[1] == local_board_state[5] && local_board_state[5] == local_board_state[9]){
        global_board_state[local_board - 1] = turn_sign;
    } else if (local_board_state[3] == local_board_state[5] && local_board_state[5] == local_board_state[7]){
        global_board_state[local_board - 1] = turn_sign;
    } 
}
