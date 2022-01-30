// Sudoku using recursion and backtracking - rewritten into C from Python
// Source: https://www.youtube.com/watch?v=tvP_FZ-D9Ng
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sudoku.h"

// Locator function
// Finds the next empty square on the board
int* findEmpty(int board[9][9] ) {
    int* coordinates = malloc(2 * sizeof(int));
    coordinates[0] = -1;
    coordinates[1] = -1;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == 0) {
                coordinates[0] = r;
                coordinates[1] = c;
                return coordinates;
            }
        }
    }
    return coordinates;
}

// Validation function
int isValid(int board[9][9] , int guess, int row, int col) {

    // Condition 1 - There can only be 1 copy of each number in 1 row
    int rowVals[9];
    for (int i = 0; i < 9; i++) {
        rowVals[i] = board[row][i];
    } 
    for (int i = 0; i < 9; i++) {
        if (guess == rowVals[i]) {
            return 0;
        }
    }

    // Condition 2 - There can only be 1 copy of each number in 1 column
    int colVals[9];
    for (int i = 0; i < 9; i++) {
        colVals[i] = board[i][col];
    }
    for (int i = 0; i < 9; i++) {
        if (guess == colVals[i]) {
            return 0;
        }
    }

    // Condition 3 - Each 3x3 square can only contain 1 copy of each number
    int rowStart = floor(row/3) * 3;
    int colStart = floor(col/3) * 3;
    for (int r = rowStart; r < rowStart + 3; r++) {
        for (int c = colStart; c < colStart + 3; c++) {
            if (board[r][c] == guess) {
                return 0;
            }
        }
    }

    // Else
    return 1;
}

// Bruteforce solving function with backtracking and recursion
int bruteSolve(int board[9][9]) {
    int row;
    int col;

    int* coor = findEmpty(board); // Retrieve next empty square

    row = coor[0];
    col = coor[1];

    free(coor);

    if (row == -1) {    // If there are no empty squares, the board is solved
        return 1;
    }

    for (int guess = 1; guess < 10; guess++) { //Iterate through each number 
        if (isValid(board, guess, row, col)) {  // Check if number is valid 
            board[row][col] = guess;    
            
            // Recursion: Continue on that one guess until we fail or find a solution
            if (bruteSolve(board)) {
                return 1;
            }
        }
        // If no solution is found, we reset aka backtrack and try another value
        board[row][col] = 0;   
    }

    //After looping through all numbers and no solution is found -> UNSOLVABLE board
    return 0;
}

// Helper function for displaying the board
void showBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        printf("[");
        for (int j = 0; j < 9; j++) {
            printf("%i,", board[i][j]);
        }
        printf("]\n");
    }
}

int main(int argc, char **argv) {
    int board[9][9] = {
        {0,0,0,5,2,0,0,0,7},
        {0,0,0,0,0,3,0,6,0},
        {0,1,0,0,6,7,0,4,0},
        {0,7,0,4,3,5,0,0,6},
        {0,0,9,0,7,0,8,5,0},
        {0,0,6,0,8,0,4,7,3},
        {5,9,0,6,1,0,0,3,4},
        {0,6,4,0,0,0,0,1,9},
        {1,0,2,7,0,0,6,0,5}
    };
    printf("Original board:\n");
    showBoard(board);
    int* coor = findEmpty(board);
    if (bruteSolve(board)) {
        printf("Solved board:\n");
        showBoard(board);
    } else {
        printf("Unsolvable board");
    }
    return 0;
}