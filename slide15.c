#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "hw3.h"

enum opt_command {NONE=0, LEFT=1, UP=2, RIGHT=3, DOWN=4, HELP=5, QUIT=6};


enum opt_command get_command(){
    // read key from the user with getchar()
    // return one of the named opt_command constants accordingly
    // use w, d, s, a for UP, RIGHT, DOWN, LEFT, respectively
    // use h for HELP and q for QUIT
    // for any other key, return NONE
    int c = getchar();
    while (c == '\n') {
        c = getchar();
    }

    switch (c) {
        case 'w':
            return UP;
        case 'd':
            return RIGHT;
        case 's':
            return DOWN;
        case 'a':
            return LEFT;
        case 'h':
            return HELP;
        case 'q':
            return QUIT;
        default:
            return NONE;
    }
}

char* board_new(){
    // a board is an array of characters of length 16
    // note: it is *not* a string, though similar to one
    // a new board should be allocated and filled in with
    // all characters in solved position

    char *board = malloc(16 * sizeof(char));
    char number[16] = {'1', '2', '3', '4', '5' ,'6' ,'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '_'};
    for (int i = 0; i < 16; i++) {
        board[i] = number[i];
    }
    return board;
    
}



int empty_cell(char *board){
    // return the index of the empty cell '_' in the board array

    for(int i = 0; i < 16; i++){
        if(board[i] == '_'){
            return i;
        }
    }
    return -1;
    
}


int up_neighbor(int i){
    // return the index of the "up neighbor" of the given index
    // return -1 if there is no up neighbor
    // ex: up_neighbor(4) --> 0 [note: corrected from 1]
    
    if (i - 4 >= 0){
        return i - 4;
    }else{
        return -1;
    }
}


int down_neighbor(int i){
    // return the index of the "down neighbor" of the given index
    // return -1 if there is no down neighbor
    // ex: down_neighbor(4) --> 8
    
    if (i + 4 < 16){
        return i + 4;
    }else{
        return -1;
    }
}

int left_neighbor(int i){
    // return the index of the "left neighbor" of the given index
    // return -1 if there is no left neighbor
    // ex: left_neighbor(4) --> -1
    
    if ((i % 4) == 0){
        return -1;
    }else{
        return i - 1;
    }
}


int right_neighbor(int i){
    // return the index of the "right neighbor" of the given index
    // return -1 if there is no right neighbor
    // ex: right_neighbor(4) --> 5
    
    if ((i+1) % 4 == 0){
        return -1;
    }else{
        return i + 1;
    }
}


void slide_left(char *board){
    // if it is possible to slide a tile left into the gap, slide it
    // otherwise, perform no action
    
    
    int empty = empty_cell(board);

    if(empty % 4 != 3)
    {
        char temp = board[empty + 1];
        board[empty + 1] = '_';
        board[empty] = temp;
    }
}

void slide_right(char *board){
    // if it is possible to slide a tile right into the gap, slide it
    // otherwise, perform no action
    
    int empty = empty_cell(board);

    if(empty % 4 != 0)
    {
        char temp = board[empty - 1];
        board[empty - 1] = '_';
        board[empty] = temp;
    }
    
}

void slide_up(char *board){
    // if it is possible to slide a tile up into the gap, slide it
    // otherwise, perform no action
    
    int empty = empty_cell(board);

    if(empty <= 11)
    {
        char temp = board[empty + 4];
        board[empty + 4] = '_';
        board[empty] = temp;
    }
     
}

void slide_down(char *board){
    // if it is possible to slide a tile down into the gap, slide it
    // otherwise, perform no action
    

    int empty = empty_cell(board);

    if(empty >= 4)
    {
        char temp = board[empty - 4];
        board[empty - 4] = '_';
        board[empty] = temp;
    }  
}

void shuffle(char *board, unsigned int n){
    // perform n moves at random to shuffle the board
    // the hw3 pdf has relevant details
    
    srand(time(NULL));

    for(int i = 0; i < n; i++){
        int move = rand() % 4;
        switch(move){
            case 0:
                //up
                slide_up(board);
                break;
            case 1:
                //down
                slide_down(board);
                break;
            case 2:
                //right
                slide_right(board);
                break;
            case 3:
                //left
                slide_left(board);
                break;
        }
    }
}

void show_board(char *board){
    // given a char-array board, print a 2D representation to stdout
    
    for(int i = 0; i < 16; ++i){
        printf("%c ", board[i]);
        if ((i+1) % 4 == 0){
            printf("\n");
        }
    }
    return;
}
int solved(char *board){
    // return 0 if the board is not in solved position
    // return nonzero if the board is in solved position
    
    char number[16] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '_'};
    for (int i = 0; i < 16; i++) {
        if (board[i] != number[i]) {
            return 0;
        }
    }
    return 1;
}


void display_help()
{
  printf("w: slide up (if possible)\n");
  printf("d: slide right (if possible)\n");
  printf("s: slide down (if possible)\n");
  printf("a: slide left (if possible)\n");
  printf("h: help\n");
  printf("q: quit\n");
  printf("\n");
}


int main(int argc, char *argv[])
{
    printf("Welcome to Slide-15!\n");
    printf("Here is your board:\n");
    char *pboard;
    pboard = board_new();
    shuffle(pboard, 100);
    show_board(pboard);
    printf("\n");


    printf("Your goal is to order the board.\n");
    printf("Here's how to move:\n");
    display_help();
    show_board(pboard);
    printf("\n");

    while(1){
        if (solved(pboard) == 1){
            printf("Congrats! You've solved Slide-15!\n");
            return 0;
        }
        printf("Enter your move(h for help):\n");

        enum opt_command command = get_command();

        switch(command) {
                case UP:
                    slide_up(pboard);
                    break;
                case RIGHT:
                    slide_right(pboard);
                    break;
                case DOWN:
                    slide_down(pboard);
                    break;
                case LEFT:
                    slide_left(pboard);
                    break;
                case HELP:
                    display_help();
                    break;
                case QUIT:
                    return 0;
                case NONE:
                    break;
        }
        show_board(pboard);
    }
}


