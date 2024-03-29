
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <windows.h>

void showInstructions();
void gameSettings(char *player_sign_pointer);

void showOnlyGlobalBoard(char global_board_state[]);
void showAllLocalBoards(char local_board_states[9][10]);

int anyLocalBoardChoice(char local_board_states[9][10], char global_board_state[], char turn_sign, int *enemy_turn_pointer);
int nextLocalBoard(char local_board_states[9][10], char global_board_state[], char turn_sign, int next_local, int *enemy_turn_pointer);

int checkIfGlobalIsOccupied(char global_board_state[], int choice);
int checkIfTie(char global_board_state[]);

int generateRandomNumber(int max);

// (char (*local_board_state)[10] means a pointer that points to an array that has 10 characters
int editLocalBoard(char (*local_board_state)[10], char turn_sign, int *enemy_turn_pointer);

int checkGlobalBoard(char global_board_state[], char turn_sign);
void checkLocalBoard(char global_board_state[], char local_board_state[], int local_board, char turn_sign);

void cleanUpBoard(char local_board_state[], char turn_sign);

int main(){
    srand(time(NULL));  // Load srand()

    // Initialize variables

    char global_board_state[] = {'1', '2', '3',
                                 '4', '5', '6',
                                 '7', '8', '9'};

    char local_board_states[9][10] = {{'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'9', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    char player_sign;
    int choose_any_local = 0, do_while_flag = 0, next_local = 0, enemy_turn = 0; 
    int global_only = 0, check_if_tie = 0, overall_winner = 0;

    int *enemy_turn_pointer = &enemy_turn;
    char *player_sign_pointer = &player_sign;

    showInstructions();
    gameSettings(player_sign_pointer);

    do{ 
        if (checkGlobalBoard(global_board_state, player_sign) == 1){
            overall_winner = 1;
            break;
        } else if (checkGlobalBoard(global_board_state, player_sign) == 2){
            overall_winner = 2;
            break;
        } else if (checkIfTie(global_board_state) == 1){
            check_if_tie = 1;
            break;
        }

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

                if (checkIfGlobalIsOccupied(global_board_state, next_local) == 0){
                    printf("Loading all local boards...");
                    Sleep(1000);
                    system("cls");

                    choose_any_local = 1;
                    global_only = 1;

                } else{
                    choose_any_local = 0;
                    global_only = 0;
                }

                enemy_turn = 1;
    
            } else {
                next_local = anyLocalBoardChoice(local_board_states, global_board_pointer, player_sign, enemy_turn_pointer);

                Sleep(1500);
                system("cls");

                if (checkIfGlobalIsOccupied(global_board_state, next_local) == 0){
                    printf("Loading all local boards...");
                    Sleep(1000);
                    system("cls");

                    choose_any_local = 1;
                    global_only = 1;
                } else{
                    choose_any_local = 0;
                    global_only = 0;
                }

                enemy_turn = 0;
            }

            if (player_sign == 'X'){
                player_sign = 'O';
            } else if (player_sign == 'O'){
                player_sign = 'X';
            }

        } else{
            if (enemy_turn == 0){
                if (global_board_state[next_local- 1] != 'X' && global_board_state[next_local - 1] != 'O'){
                    next_local = nextLocalBoard(local_board_states, global_board_state, player_sign, next_local, enemy_turn_pointer);
                    Sleep(2000);
                    system("cls");

                    if (checkIfGlobalIsOccupied(global_board_state, next_local) == 0){
                        printf("Loading all local boards...");
                        Sleep(1000);
                        system("cls");
                        // enemy_turn = 1;
                    } else{
                        choose_any_local = 0;
                        global_only = 0;
                    }

                    enemy_turn = 1;
                } else{
                    system("cls");
                    choose_any_local = 0;
                    global_only = 0;
                    // enemy_turn = 0;
                    enemy_turn = 1;
                }
        
            } else{
                if (global_board_state[next_local - 1] != 'X' && global_board_state[next_local - 1] != 'O'){
                    next_local = nextLocalBoard(local_board_states, global_board_state, player_sign, next_local, enemy_turn_pointer);
                    Sleep(2000);
                    system("cls");

                    if (checkIfGlobalIsOccupied(global_board_state, next_local) == 0){
                        printf("Loading all local boards...");
                        Sleep(1000);
                        system("cls");
                        // enemy_turn = 0;
                    } else{
                        choose_any_local = 0;
                        global_only = 0;
                    }

                    enemy_turn = 0;
                } else{
                    system("cls");
                    choose_any_local = 0;
                    global_only = 0;
                    // enemy_turn = 1;  
                    enemy_turn = 0;              
                }
            }

            if (player_sign == 'X'){
                player_sign = 'O';
            } else if (player_sign == 'O'){
                player_sign = 'X';
            }
        }

    } while (do_while_flag == 0);

    Sleep(1000);
    system("cls");

    printf("Global Board:\n\n");
    showOnlyGlobalBoard(global_board_state);

    // TODO: Use string padding in here later

    if (overall_winner == 1){
        printf("\n                                The winner is player \'X\'!\n");
    } else if (overall_winner == 2){
        printf("\n                                The winner is player \'O\'!\n");
    } else if (check_if_tie == 1){
        printf("\n                           Both players are tied until the very end!\n");
    }

    return 0;
}

void showInstructions(){
    printf("Welcome to Super TicTacToe!\n");
    printf("Super TicTacToe is not that different from the regular TicTacToe.\n");
    printf("Super TicTacToe adds another layer of difficulty by making the game have a \"global\"\n");
    printf("TicTacToe, and a \"local\" TicTacToe.\n\n");

    printf("Local TicTacToe: is played like a regular TicTacToe.\n");
    printf("Global TicTacToe: Local TicTacToes has to have a winner in order for a symbol\n");
    printf("to be placed in a spot in the Global TicTacToe.\n\n");
}

void gameSettings(char *player_sign_pointer){
    char preference;

    do{
        printf("Game settings:\n\n");
        printf("Do you want to be \'X\' or \'O\'?\n");
        printf("-----> ");

        scanf(" %c", &preference);

        if (preference != 'X' && preference != 'O'){
            printf("\nThe only choices are \'X\' and \'O\'. Your choice was %c. Try again.\n\n", preference);
        }

    } while (preference != 'X' && preference != 'O');

    printf("\n\n");

    *player_sign_pointer = preference;
}

void showOnlyGlobalBoard(char global_board_state[]){
    int left_pad_num = 30;
    char left_pad_str[] = "";

    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , global_board_state[0], global_board_state[1], global_board_state[2]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , global_board_state[3], global_board_state[4], global_board_state[5]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , global_board_state[6], global_board_state[7], global_board_state[8]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n\n", left_pad_num, left_pad_str);
}

void showAllLocalBoards(char local_board_states[9][10]){
    // lb_c means local board counter

    int lb_c = 0;
    
    while (lb_c < 9){
        printf("\n\n           Local Board %c                          Local Board %c                          Local Board %c \n\n", 
                local_board_states[lb_c][0], local_board_states[lb_c + 1][0], local_board_states[lb_c + 2][0]);


        printf("+---------|-----------|----------+     +---------|-----------|----------+     +---------|-----------|----------+\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");

        printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
                local_board_states[lb_c][1], local_board_states[lb_c][2], local_board_states[lb_c][3],
                local_board_states[lb_c + 1][1], local_board_states[lb_c + 1][2], local_board_states[lb_c + 1][3],
                local_board_states[lb_c + 2][1], local_board_states[lb_c + 2][2], local_board_states[lb_c + 2][3]);

        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("+---------|-----------|----------+     +---------|-----------|----------+     +---------|-----------|----------+\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");

        printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
                local_board_states[lb_c][4], local_board_states[lb_c][5], local_board_states[lb_c][6],
                local_board_states[lb_c + 1][4], local_board_states[lb_c + 1][5], local_board_states[lb_c + 1][6],
                local_board_states[lb_c + 2][4], local_board_states[lb_c + 2][5], local_board_states[lb_c + 2][6]);

        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("+---------|-----------|----------+     +---------|-----------|----------+     +---------|-----------|----------+\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");

        printf("|    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |     |    %c    |     %c     |     %c    |\n", 
                local_board_states[lb_c][7], local_board_states[lb_c][8], local_board_states[lb_c][9],
                local_board_states[lb_c + 1][7], local_board_states[lb_c + 1][8], local_board_states[lb_c + 1][9],
                local_board_states[lb_c + 2][7], local_board_states[lb_c + 2][8], local_board_states[lb_c + 2][9]);

        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("|         |           |          |     |         |           |          |     |         |           |          |\n");
        printf("+---------|-----------|----------+     +---------|-----------|----------+     +---------|-----------|----------+");

        lb_c += 3;
    }
}

void showOneLocalBoard(char local_board_state[]){
    int left_pad_num = 30;
    char left_pad_str[] = "";

    printf("%*sShowing changes on local board %c\n\n", left_pad_num, left_pad_str, local_board_state[0]);

    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , local_board_state[1], local_board_state[2], local_board_state[3]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , local_board_state[4], local_board_state[5], local_board_state[6]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|    %c    |     %c     |     %c    |\n", left_pad_num, left_pad_str , local_board_state[7], local_board_state[8], local_board_state[9]);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s|         |           |          |\n", left_pad_num, left_pad_str);
    printf("%*s+---------|-----------|----------+\n\n", left_pad_num, left_pad_str);
}

int anyLocalBoardChoice(char local_board_states[9][10], char global_board_state[], char turn_sign, int *enemy_turn_pointer){
    int local_board_choice = 0;
    int next_local_board_spot = 0;
    char (*current_local_board_pointer)[10];

    while (1){
        if (*enemy_turn_pointer == 0){
            printf("Choose a local TicTacToe spot. \n");
            printf("-----> ");
            scanf("%d", &local_board_choice);
        } else {
            local_board_choice = generateRandomNumber(8) + 1;
        }

        if (local_board_choice <= 0 || local_board_choice > 9){
            printf("The local board is only from 1 to 9. Your input was %d. Try again.\n\n", local_board_choice);
            continue;
        }   

        if (checkIfGlobalIsOccupied(global_board_state, local_board_choice) == 0){
            break;
        } else if (*enemy_turn_pointer == 0){
            printf("That local board has already been won by %c. Find another local board.\n\n", turn_sign);
        }
    }

    if (*enemy_turn_pointer == 1){
        printf("Player \'%c\' chose local board %d\n", turn_sign, local_board_choice);
        Sleep(1500);
    }

    showAllLocalBoards(local_board_states);

    // Ampersand sign '&' points to the entire array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[local_board_choice - 1];

    next_local_board_spot = editLocalBoard(current_local_board_pointer, turn_sign, enemy_turn_pointer);

    system("cls");

    printf("Changes made on local board %d (at spot %d):\n\n", local_board_choice, next_local_board_spot);

    Sleep(1000);

    showOneLocalBoard(local_board_states[local_board_choice - 1]);

    checkLocalBoard(global_board_state, local_board_states[local_board_choice - 1], local_board_choice, turn_sign);

    return next_local_board_spot;

}

int nextLocalBoard(char local_board_states[9][10], char global_board_state[], char turn_sign, int next_local, int *enemy_turn_pointer){
    int next_local_board_spot = 0;

    // Initialize a pointer that leads to an array that has 10 characters
    char (*current_local_board_pointer)[10];

    showAllLocalBoards(local_board_states);

    // Ampersand sign '&' points to the entires array, not the first element of the array.    
    current_local_board_pointer = &local_board_states[next_local - 1];

    next_local_board_spot = editLocalBoard(current_local_board_pointer, turn_sign, enemy_turn_pointer);

    system("cls");

    printf("Changes made on local board %d (at spot %d):\n\n", next_local, next_local_board_spot);

    Sleep(1000);

    showOneLocalBoard(local_board_states[next_local - 1]);

    checkLocalBoard(global_board_state, local_board_states[next_local - 1], next_local, turn_sign);

    return next_local_board_spot;
}

int checkIfGlobalIsOccupied(char global_board_state[], int choice){
    if (global_board_state[choice - 1] == 'X' || global_board_state[choice - 1] == 'O'){
        return 1;
    } else{
        return 0;
    }
}

int checkIfTie(char global_board_state[]){
    // Checks how many spots of the global board are filled
    int fill_count = 0;

    for (int i = 0; i < 9; i++){
        if (global_board_state[i] == 'X' || global_board_state[i] == 'O'){
            fill_count++;
        }
    }

    if (fill_count == 9){
        return 1;
    } else{
        return 0;
    }

}

int generateRandomNumber(int max){
    return rand() % max;
}

int editLocalBoard(char (*local_board_state)[10], char turn_sign, int *enemy_turn_pointer){
    int player_spot_choice = 0;

    do{
        if (*enemy_turn_pointer == 0){
            printf("\n\nChoose a spot to place %c at local board %c.\n", turn_sign, *local_board_state[0]);
            printf("-----> ");
            scanf("%d", &player_spot_choice);
    
            if (*(*(local_board_state) + player_spot_choice) == 'X' && 
                *(*(local_board_state) + player_spot_choice) == 'O'){

                printf("That spot is already occupied. Choose another spot on the board. \n");
            } else if (player_spot_choice <= 0 || player_spot_choice > 9){
                printf("The spots are only from 1 to 9. Your input was %d. Try again.", player_spot_choice);
                continue;
            }  

        } else {
            player_spot_choice = generateRandomNumber(8) + 1;

            if (*(*(local_board_state) + player_spot_choice) != 'X' && 
                *(*(local_board_state) + player_spot_choice) != 'O'){

                break;
            }
        }

    }while (*(*(local_board_state) + player_spot_choice) == 'X' || 
            *(*(local_board_state) + player_spot_choice) == 'O' || 
            player_spot_choice <= 0 || player_spot_choice > 9);

    // The commented line of code below is wrong because this function is already given the ith array of the 2d array
    // It is just needed to get the position of the jth element.
    // For more understanding, check geeksforgeeks link

    // *(*(local_board_state + int_local_board_number - player_spot_choice) + player_spot_choice) = 'X';

    if (*enemy_turn_pointer == 1){
        printf("\n\nThe enemy chose to put \'%c\' at spot %d on local board %c.\n", turn_sign, player_spot_choice, (*local_board_state)[0]);
        Sleep(2500);
    }

    *(*(local_board_state) + player_spot_choice) = turn_sign;
    
    return player_spot_choice;
}

int checkGlobalBoard(char global_board_state[], char turn_sign){
    // 0 no one wins, 1 means player X wins, 2 means player O wins

    if ((global_board_state[0] == global_board_state[1] && global_board_state[1] == global_board_state[2]) ||
        (global_board_state[3] == global_board_state[4] && global_board_state[4] == global_board_state[5]) ||
        (global_board_state[6] == global_board_state[7] && global_board_state[7] == global_board_state[8]) ||
        (global_board_state[0] == global_board_state[3] && global_board_state[3] == global_board_state[6]) ||
        (global_board_state[1] == global_board_state[4] && global_board_state[4] == global_board_state[7]) ||
        (global_board_state[2] == global_board_state[5] && global_board_state[5] == global_board_state[8]) ||
        (global_board_state[0] == global_board_state[4] && global_board_state[4] == global_board_state[8]) ||
        (global_board_state[2] == global_board_state[4] && global_board_state[4] == global_board_state[6])){
        
        // The winner will be the one who had the previous turn
        if (turn_sign == 'O'){
            return 1;
        } else{
            return 2;
        }

    } else{
        return 0;
    }

}

void checkLocalBoard(char global_board_state[], char local_board_state[], int local_board, char turn_sign){
    if ((local_board_state[1] == local_board_state[2] && local_board_state[2] == local_board_state[3] && local_board_state[1] != ' ') ||
        (local_board_state[4] == local_board_state[5] && local_board_state[5] == local_board_state[6] && local_board_state[4] != ' ') ||
        (local_board_state[7] == local_board_state[8] && local_board_state[8] == local_board_state[9] && local_board_state[7] != ' ') ||
        (local_board_state[1] == local_board_state[4] && local_board_state[4] == local_board_state[7] && local_board_state[1] != ' ') ||
        (local_board_state[2] == local_board_state[5] && local_board_state[5] == local_board_state[8] && local_board_state[2] != ' ') ||
        (local_board_state[3] == local_board_state[6] && local_board_state[6] == local_board_state[9] && local_board_state[3] != ' ') ||
        (local_board_state[1] == local_board_state[5] && local_board_state[5] == local_board_state[9] && local_board_state[1] != ' ') ||
        (local_board_state[3] == local_board_state[5] && local_board_state[5] == local_board_state[7] && local_board_state[3] != ' ')){

        global_board_state[local_board - 1] = turn_sign;
        cleanUpBoard(local_board_state, turn_sign);

    } else {
        return ;
    }
}

void cleanUpBoard(char local_board_state[], char turn_sign){
    // Note: Local board starts at index 1 and ends at index 9

    for (int i = 1; i < 10; i++){
        local_board_state[i] = turn_sign;
    }
}