#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/*-----------------------------------------------------------------------------------------------*/

/* pre-supplied function to load a Sudoku board from a file into a 2-dim
array*/
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }

  //function aborts programme if specification is false - error message
  //issued, programme is terminated
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      //isdigit checks whether argument is a decimal digit character
      //therefore, will abort programme if not a . or decimal digit character
      
      board[row][n] = buffer[n];
      //fills the row with the 9 digits/'.'
      
    }
    row++;
    //new row up to the end
    
    in.getline(buffer,512);
    //gets characters from stream until delimiting character - i.e. '\n'
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
  //if not 9 rows, then abort programme
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
  //prints line dividers or column dividers where necessary
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    //terniary function - if i%3 >0,: otherwise |
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/*-------------------couresework function definitions--------------------------------------------*/

//QUESTION 1--------------------------------------------------------------------------------------

//FUNCTION DEFINITION for "is_complete"
//takes in input of board array and returns boolean true iff ALL board positions
//are occupied by digits (i.e. the board is "complete");
bool is_complete(char board[9][9]) {

  /*need to check if at least one of the characters in board is not equal
    to a char from 1-9, the board is NOT complete */
  
  bool check = true;

  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      if ((board[row][col] < '1') || (board[row][col] > '9')) {
	      check = false;
      }
    }
  }

  return check;
}

//QUESTION 2--------------------------------------------------------------------------------------

//internal supporting functions for "make_move"

//takes in index position as a 2 string char array, changes input placeholders targ.
//target_row + target_height to h and r of index of target (int 0-8)
void target_board_position(const char index_pos[2], int &target_row, int &target_col) {
  target_row = toupper(index_pos[0]) - 'A';         
  target_col = index_pos[1] - '1';
}

//check target row and target height are in range(i.e. between 0-8)
bool is_in_range(int target_row, int target_col) {
  if ((target_row >= 0) && (target_row < 9) && (target_col >=0) && (target_col < 9)) {
    return true;
  }
  return false;
}

//check target board position is empty
bool targ_is_empty(char target_position) {
  if ((target_position < '1') || (target_position > '9')) {
    return true;
  }
  return false;
}

//check input is a character for a number
bool input_is_num(char target_input) {
  if ((target_input > '0') && (target_input <= '9')) {
    return true;
  }
  return false;
}

//check input is unique in its row
bool char_unique_in_row(char target_input, int target_row, char board[9][9]) {
  for (int count = 0; count < 9; count++) {
    if (board[target_row][count] == target_input) {
      return false;
    }
  }
  return true;
}

//check input is unique in its column
bool char_unique_in_col(char target_input, int target_col, char board[9][9]) {
  for (int count = 0; count < 9; count++) {
    if (board[count][target_col] == target_input) {
      return false;
    }
  }
  return true;
}

//check input is unique in target subsquare
bool char_unique_in_subsquare(char target, int target_row, int target_col, char board[9][9]) {
  //reduce board grid to 3x3 for subsquare and identify subsquare of target
  int reduced_index_row = target_row/3;
  int reduced_index_col = target_col/3;

  //check target character not in individual squares within identified subsquare
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (board[reduced_index_row*3+row][reduced_index_col*3+col] == target) {
	      return false;
      }
    }
  }
  return true;
}

//FUNCTION DEFINITION FOR "make_move"
//tests whether the target_input inputted in position index_pos on board is
//valid (true) or not (false)
bool make_move(const char index_pos[2], char target_input, char board[9][9]) {
  
  int target_row, target_col;

  //convert characters to index board position
  target_board_position(index_pos, target_row, target_col);
  
  //rule testing - all must be true to return true
  if ((is_in_range(target_row, target_col)) &&
      (targ_is_empty(board[target_row][target_col])) &&
      (input_is_num(target_input)) &&
      (char_unique_in_row(target_input, target_row, board)) &&
      (char_unique_in_col(target_input, target_col, board)) &&
      (char_unique_in_subsquare(target_input, target_row, target_col, board))) {
    return true;
  }
  return false;
}

//QUESTION 3--------------------------------------------------------------------------------------

//FUNCTION DEFINITION for "save_board"
//boolean that outputs 2 dimensional board to a file with the name filename.
//true if file output successfully written, false if file output fails.
bool save_board(const char* filename, char board[9][9]) {

  ofstream out_stream;

  out_stream.open(filename);

  //if array contains valid characters then output to file - otherwise fail task (return false)
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == '.' || ((board[row][col] > '0') && (board[row][col] <= '9'))) {
	      out_stream.put(board[row][col]);
      } else {
	      return false;
      }
    }
    out_stream.put('\n');
  }

  out_stream.close();
  return true;
}

//QUESTION 4-------------------------------------------------------------------------------------

//FUNCTION DEFINITION FOR "solve_board"
//boolean takes board and attempts to find solution using recursion. If solved, returns true
//and solution is saved in board array. if no solution, return false and original board
bool solve_board(char board[9][9]) {
  
  //loops to go through all indices on board
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {

      //convert index into character form
      char index[2] = {static_cast<char>(row+'A'), static_cast<char>(col+'1')};

      //loops to test all potential inputs in clear positions
      if (board[row][col] == '.') {
	      for (char input = '1'; input <= '9'; input++) {

          //test that input is valid - if valid, add that input to board
          if (make_move(index, input, board)) {
            board[row][col] = input;

            //RECURSION HERE - solve_board move to next square to test an input
            if (solve_board(board)) {
              return true;

              //if no input is valid, clear that value - recursion will
              //move solver back a step
            } else {
              board[row][col] = '.';
            }
          }
        }
        //if test cycles through all inputs and still doesnt return output
        //means problem is unsolvable - return false
        return false;
      }
    } 
  }
  
  //if cycle through all indices and all valid, the board solved - return true 
  return true;
}

//QUESTION 5-------------------------------------------------------------------------------------

//FUNCTION DEFINITION FOR "solver_with_tracer"
//sudoku solver using recursion as per "solve_board" but with tracer reference variable to
//track recursions
bool solver_with_tracer(char board[9][9], int &tracer) {

  tracer++;
  
  //same as "solve_board" but with tracer variable
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {

      char index[2] = {static_cast<char>(row+'A'), static_cast<char>(col+'1')};
      
      if (board[row][col] == '.') {
	for (char input = '1'; input <= '9'; input++) {

	  if (make_move(index, input, board)) {
	    board[row][col] = input;

	    if (solver_with_tracer(board, tracer)) {
	      return true;

	    } else {
	      board[row][col] = '.';
	    }
	  }
	}
	return false;
      }
    }
  }
  return true;
}

//FUNCTION DEFINITION for "solver_with_tracer_randomised"
//sudoku solver as per 'solve_copy' using recursion as tracer reference variable
//AND takes in array of inputs from [9] array, with flexibility to shuffle pre entry
bool solver_with_tracer_randomised(char board[9][9], int &tracer, char input_array[9]) {
  
  tracer++;
  
  //same as "solve_board" but with tracer variable"
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {

      char index[2] = {static_cast<char>(row+'A'), static_cast<char>(col+'1')};
      
      if (board[row][col] == '.') {
	for (int count = 0; count < 9; count++) {

	  //take character from input_array which can be shuffled, vs going 1-9 as per solve_board
	  if (make_move(index, input_array[count], board)) {
	    board[row][col] = input_array[count];

	    if (solver_with_tracer_randomised(board, tracer, input_array)) {
	      return true;

	    } else {
	      board[row][col] = '.';
	    }
	  }
	}
	return false;
      }
    }
  }
  return true;
}

//attempt to solve board using "unique character" technique - i.e. start by filling out
//all spots where there is only 1 possibility for entry. This is hypothesised to be a
//more basic algorithm in line with how a human might approach the question

//supporting functions

//checks that input cannot be valid for anywhere else in the row of the target index
bool only_option_in_row(int target_row, int target_col, char input, char board[9][9]) {

  for (int count = 0; count < 9; count++) {
    
    //skip actual target input index
    if (count == target_col) {
      continue;
    }
    
    //convert index into char string
    char index[2] = {static_cast<char>(target_row+'A'),
		     static_cast<char>(count+'1')};

    if (make_move(index, input, board)) {
      return false;
    }
  }
  return true;
}

//checks that input cannot be valid for anywhere else in the col of the target index
bool only_option_in_col(int target_row, int target_col, char input, char board[9][9]) {

  for (int count = 0; count < 9; count++) {

    //skip actual target input index
    if (count == target_row) {
      continue;
    }
   
    //convert index into char string
    char index[2] = {static_cast<char>(count+'A'),
		     static_cast<char>(target_col+'1')};

    if (make_move(index, input, board)) {
      return false;
    }
  }
  return true;
}

//checks that input cannot be valid in anywhere else in the subsquare of the target
bool only_option_in_subsquare(int target_row, int target_col, char input, char board[9][9]) {

  int reduced_index_row = target_row/3;
  int reduced_index_col = target_col/3;

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {

      //convert index into char string
      char index[2] = {static_cast<char>(reduced_index_row*3+row+'A'),
		       static_cast<char>(reduced_index_col*3+col+'1')};

      //skip if target square
      if ((reduced_index_row*3+row == target_row) && (reduced_index_col*3+col == target_col)) {
	continue;
      }
      if (make_move(index, input, board)) {
	return false;
      }		      
    }
  }
  return true;
}

//returns true if input is unique to the target index - i.e. placing it anywhere else is invalid
bool only_move_possible(int target_row, int target_col, char input, char board[9][9]) {

  //convert index into char string
  char index[2] = {static_cast<char>(target_row+'A'),
		   static_cast<char>(target_col+'1')};

  //check valid move in target square and not valid anywhere else
  if ((make_move(index, input, board)) &&
      ((only_option_in_row(target_row, target_col, input, board)) ||
       (only_option_in_col(target_row, target_col, input, board)) ||
       (only_option_in_subsquare(target_row, target_col, input, board)))) {
    return true;
  }

  return false;
}

//FUNCTION DEFINITION for "fill_all_definite_moves"
//cycles through board once starting at A1 and fills out any unique characters 
void fill_all_definite_moves(char board[9][9]) {

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      for (char input = '1'; input <= '9'; input++) {
	      if (only_move_possible(row, col, input, board)) {
	        board[row][col] = input;
      	}
      }
    }
  }
}
	    
