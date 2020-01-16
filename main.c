/*
 * Usman Farooqi
 * Comp 1400
 * NineGaps.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// the following function will take in a board (aka array), a row / col, an operator, an x, a counter, and a y
int Calc_row(int board[], int arr[], char operator[], int x, int c, int y){ // function for calculating row results
    int temp1;
    if(operator[c] == '+'){ // if addition
        temp1 = arr[x] + board[(x*3) + y]; // set temp 1 to first element of arry + 2nd and 3rd element
    }

    if(operator[c] == '-'){ // if subtraction
        temp1 = arr[x] - board[(x*3) + y]; // set temp 1 to first element of arry + 2nd and 3rd element
    }

    if(operator[c] == '*'){ // if multiplication
        temp1 = arr[x] * board[(x*3) + y]; // set temp 1 to first element of arry + 2nd and 3rd element
    }
    return temp1; // return temp 1
}

// the following function takes in a board (aka arry), row/col, operator, x, a counter, y
int Calc_col(int board[], int arr[], char operator[], int x, int c, int y){ // function to calculate the column results
    int temp1; // temporary variable
    if(operator[c] == '+'){ // if addition
        temp1 = arr[x] + board[(y*3) + x]; // set temp1 to the first element + the 2nd and 3rd col element
    }

    if(operator[c] == '-'){ // if subtraction
        temp1 = arr[x] - board[(y*3) + x]; // set temp1 to the first element + the 2nd and 3rd col element
    }

    if(operator[c] == '*'){ // if multiplication
        temp1 = arr[x] * board[(y*3) + x];  // set temp1 to the first element + the 2nd and 3rd col element
    }
    return temp1; // return temp1
}

int main(void) {
    bool playgame = true, check_Values; //booleans used for playgame and checking values
    int main_board[9]={1,2,3,4,5,6,7,8,9}; // an array that will be used as the main game board
    int missing_array[9]; // an array that will store all missing values
    int game_board[9]; // an array that will be the used as the game board (user sees this)
    int temp_board[9]; // an array that will used as board and update each time value is inputed
    int row[3] = {0}; // an array which is used to store row calculations
    int col[3] = {0}; // an array which is used to store column calculations
    int user_row[3] = {0}; // an array which is used to store user inputted row calculations
    int user_col[3] = {0}; // an array which is used to store user inputted column calculations
    char operators[12]; // an array that stores random operations
    int level, input; // this variable stores the level of difficulty and input from user
    int missing; // this is a variable that keep track of the number of missing values in the game board.
    int temp; // this is a temporary variable
    int rand_num, x, y, row_counter, column_counter; // random variables, indexes and counters


    srand(time(NULL));

    while(playgame){
        level=0;

        printf("Welcome to Nine-Gaps game!...\n");
        printf("*****************************\n");
        printf("      *****************      \n");
        printf("            *****            \n");
        printf("              *              \n");

        while (1){
            puts("Choose the level of difficulty (1-Beginner, 2-Intermediate, 3-Advanced, 4-Expert):");
            scanf("%d",&level);
            if(level < 1 || level > 4){
                puts("Invalid input");
            }
            else{
                if(level == 1){
                    puts("The level is Beginner");
                    break;
                }
                if(level == 2){
                    puts("The level is Intermediate");
                    break;
                }
                if(level == 3){
                    puts("The level is Advanced");
                    break;
                }
                if(level == 4){
                    puts("The level is Expert");
                    break;
                }
            }
        }
        // Part 1 Generate random main board by shuffling the main_board
        for(int k = 0; k < 9; k++){ //used swap idea from bubble sort
            x = rand() % 9; // generate a random number from 1 - 9
            y = rand() % 9; // generate a random number from 1 - 9

            // the following code will randomly take 2 numbers from the array and swaps them
            temp = main_board[x]; // set the current i index to a temporary variable
            main_board[x] = main_board[y]; // set the number in the i index to a random index from the array
            main_board[y] = temp; // set temp the empty index
        }
        // Part 2 Generate random operators ( + , - , x )
        for(int i = 0; i < 12; i ++){
            rand_num = rand() % 3 + 1; // generate a random number which can be 1, 2 or 3

            switch (rand_num){ // use switch statemnt with rand_num
                case 1: operators[i] = '+';
                    break;
                case 2: operators[i] = '-';
                    break;
                case 3: operators[i] = '*';
                    break;
            }
        }

        // Part 3 Calculate the row and column results
        for(int i = 0; i < 3; i ++){ // run i from 0 - 3
            row[i] = main_board[i*3];  // set the row values to mainboard i*3 so 0, 3, 6 index
            col[i] = main_board[i]; // set column to main board col indexes so 0, 1 and 2 going down
            for(int j = 1; j < 3; j ++){ // run j from 1 - 3, so 1 or 2
                row_counter = (i*2) + (j -1); // a counter used for row index in the operators array (goes from 0, 5)
                column_counter = (i+6) + (j-1)*3; // a counter used for column index in the operators goes from (6, 9), (7,10), (8,11)

                row[i] = Calc_row(main_board, row, operators, i, row_counter, j); //set the row result by calling function
                col[i] = Calc_col(main_board, col, operators, i, column_counter, j); // set the col results by calling function
            }
        }

        // Part 4 Initialize missing Array to 0
        for(int i = 0; i < 9; i ++){ // iterate through the missing array
            missing_array[i] = 0; // populate it with all zeros
        }

        // Part 5 Copy the main_board into game_board
        for(int i = 0; i < 9; i ++){
            game_board[i] = main_board[i]; // copy the main board into the game board by iterating though each element
        }

        // Based on the selected level, 3 or 5 or 7 board values will be hidden.
        int w =0; // initializing x to 0

        while (w < level*2+1){
            int r = rand() % 3;
            int c = rand() % 3;
            if (game_board[3*r+c]!='?'){
                missing_array[game_board[3*r+c]-1]= game_board[3*r+c]; // the hidden values will be added to the set of missing values
                game_board[3*r+c] = '?';
                w++;
            } // end of if
        } // end of while

        // Part 6 Copy game board into temporary board
        for(int i = 0; i < 9; i ++){
            temp_board[i] = game_board[i];
        }

        while(1){
            // Display the game board after each update

            printf("Game Board:\n");
            printf("---------------------------------------------------\n");
            for (int i=0;i<3;i++){
                if (i>0){                   // show the column opertors
                    for (int j=0;j<3;j++){
                        printf(" %c\t\t", operators[3*(i+1)+ j]);
                    }
                    printf("\n");
                }

                for (int j=0;j<3;j++){          // show the rows
                    if (game_board[(i*3)+j]!='?')
                        printf(" %d\t ", temp_board[(i*3)+j]);
                    else if (game_board[(i*3)+j]!=temp_board[(i*3)+j]){
                        printf(" %d?\t ", temp_board[(i*3)+j]);
                    }
                    else
                        printf(" ?\t ");

                    if (j<2)
                        printf(" %c\t", operators[(i*2) + j]);
                    else
                        printf("= %d", row[i]);       // show the rows results
                }
                printf("\n");
                if (i==2)
                    printf (" =\t\t =\t\t =\n");
            }
            for (int i=0;i<3;i++)               // show the columnar results
                printf(" %d\t\t", col[i]);
            printf("\n---------------------------------------------------\n");

            // Part 7- Display the missing values and update the missing_count variable
            missing = 0;
            printf("Missing values: ");
            for(int i = 0; i < 9; i ++){
                if(missing_array[i] > 0){ // find the value in the array that's not 0
                    printf("%d ",missing_array[i]); // display that value;
                    missing++;
                }
            }
            printf("\n");
            printf("Missing count: %d\n", missing);

            // 8- break if the missing values are empty      (COMPLETE THIS PART)
            if(missing == 0){
                break;
            }

            printf("Enter in a row (1 - 3), column (1 - 3), and value (1 - 9) :\n");
            int r, c, v;
            scanf("%d %d %d", &r, &c, &v);
            if (r==0 || c==0 || v==0)
                break;

            if (r < 1 || r > 3 || c < 1 || c > 3){
                puts("Invalid row and/or column numbers. Try again.");
                continue;
            }

            if (v < 1 || v > 9) {
                puts("Invalid value. Try again.");
                continue;
            }

            if (missing_array[v-1]<1) {
                puts("This value is already there. Try again.");
                continue;
            }

            // Part 9 If the value in cell is changeable change it else continue to the top of loop
            r -=1;
            c -=1;
            if(game_board[r * 3 + c] == '?'){ // use x*3 + y from problem 1, but subtract 1 since game_board starts from 1,1 and not 0,0
                if(missing_array[temp_board[r * 3 + c] - 1] == -1){
                    missing_array[temp_board[r * 3 + c] - 1] = temp_board[r *3 + c];

                }
                temp_board[r* 3 + c] = v; // update the value in the 1d temp board list
                missing_array[v - 1] = -1;
            }
            else{ // if the cell isn't changeable
                puts("Invalid can't change cell try again");
                continue;
            }
        }

        // Part 10 check the user results
        // the following for loops will calculate the gameboard results after the user as inputted all values
        for(int i = 0; i < 3; i ++){ // run i from 0 - 3
            user_row[i] = temp_board[i*3];  // set the user row values to gameboard i*3 so 0, 3, 6 index
            user_col[i] = temp_board[i];  // set the user row values to gameboard i*3 so 0, 3, 6 index

            for(int j = 1; j < 3; j ++){ // run j from 1 - 3, so 1 or 2
                row_counter = (i*2) + (j -1); // a counter used for row index in the operators array (goes from 0, 5)
                column_counter = (i+6) + (j-1)*3; // a counter used for column index in the operators goes from (6, 9), (7,10), (8,11)

                user_row[i] = Calc_row(temp_board, user_row, operators, i, row_counter, j);  //set the user row result by calling function
                user_col[i] = Calc_col(temp_board, user_col, operators, i, column_counter, j); // set the user col results by calling function
            }
        }

        // this will check all the elements in row/col and user row/ user col
        for(int i = 0; i < 3; i ++){
            if(row[i] != user_row[i] || col[i] != user_col[i]){ // if original row results / col results dont equal the user inputted
                check_Values = false; // set check values to false
            }
            else if(row[i] == user_row[i] && col[i] == user_col[i]){ // check if both row and column results match with the user inpuuted ones
                check_Values = true; // if they do then set it to true
            }
        }


        if(check_Values == true){ //if all values are correct
            puts("----Congratulations You Won the Game---");
        }
        else{
            puts("Sorry incorrect");
        }

        puts("***************************************");
        printf("----Do you want to play again?----\n      1.Yes        2.No      \n");
        puts("***************************************");
        scanf("%d", &input);

        if(input == 1){ // if the user enters yes
            continue; // go to top of game loop
        }

        else{
            puts("Good bye!!!");
            playgame = false; // say good bye, set playgame to false and end game
        }

    }

}
