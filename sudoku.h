#ifndef SUDOKU_H
#define SUDOKU_H

/*------------pre-supplied declarations--------------------*/

//loads board from filename to two dimensional character array in programme
void load_board(const char* filename, char board[9][9]);

//display's two dimensional character array in sudoku board format
void display_board(const char board[9][9]);


/*-----------coursework function declarations--------------*/

//takes in input of board array and returns boolean true iff ALL board positions
//are occupied by digits (i.e. the board is "complete");
bool is_complete(char board[9][9]);

//tests whether the target_input inputted in position index_pos on board is
//valid (true) or not (false)
bool make_move(const char index_pos[2], char target_input, char board[9][9]);

//boolean that outputs 2 dimensional board to a file with the name filename.
//true if file output successfully written, false if file output fails.
bool save_board(const char* filename, char board[9][9]);

//bool returns true if board solved and board input = solution
//bool returns false if board unsolvable and board input = original solution
bool solve_board(char board[9][9]);

//sudoku solver using recursion as per "solve_board" but with tracer reference variable to
//track recursions
bool solver_with_tracer(char board[9][9], int &tracer);

//sudoku solver as per 'solve_board' using recursion as tracer reference variable
//AND takes in array of inputs from [9] array, with flexibility to shuffle pre entry
bool solver_with_tracer_randomised(char board[9][9], int &tracer, char input_array[9]);

//cycles through board once starting at A1 and fills out any unique characters
void fill_all_definite_moves(char board[9][9]);

#endif
