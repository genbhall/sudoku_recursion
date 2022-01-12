#include <iostream>
#include <cstdio>
#include <algorithm>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
  cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";
 
  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << endl;
  
  //check location in range - NOT OK
  cout << "Putting '1' into I0 is ";
  if (!make_move("I0", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << endl;
  
  //check lower case - SHOULD BE OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("i8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << endl;
  
  //check section not filled - SHOULD BE NOT OK
  cout << "Putting '1' into B1 is ";
  if (!make_move("B1", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << endl;
  
  //check input is char for a number - SHOULD BE NOT OK
  cout << "Putting 'a' into I8 is ";
  if (!make_move("I8", 'a', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << endl;
  
  
  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  //test failure by changing a board input to an invalid character
  load_board("easy.dat", board);
  board[0][0] = 'a';
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

 
  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  //run unsolvable puzzle to make sure board returns original array
  cout << "Testing unsolvable puzzle to make sure returns original array" << endl << endl;
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n\n";
    cout << "Original board display below: " << endl;
    display_board(board);
  }
  cout << '\n';

  cout << "=================== Question 5 ===================\n\n";

  //STEP 1 --------------------------------------------------------------------
  //first check whether solutions exist for each of the mystery items
  //using solver as per question 4

  cout << "First - check boards are solvable using function as per Question 4\n\n";
  
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution.\n";
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution.\n";
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution.\n";
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n'; 

  //STEP 2 --------------------------------------------------------------------
  //test number of recursions were required to solve mystery1 and mystery3
  //(the two boards with solutions)

  cout << "**********" << endl;
  cout << endl << "Second - for boards with solutions, check # of recursion calls on \n";
  cout << "base solver func (using recursion running through inputs 1-9 in order)." << endl << endl;
   
  //local variables tracking number of recurrences
  int tracer_1 = 0, tracer_2 = 0;

  //outputting number of recursions for mystery1
  load_board("mystery1.dat", board);
  if (solver_with_tracer(board, tracer_1)) {
    cout << "'mystery1' solved with " << tracer_1 << " recursions" << endl << endl;
  } else {
    cout << "No solution found for 'mystery1'." << endl;
  cout << '\n';
  }

  //outputting number of recursions for mystery3
  load_board("mystery3.dat", board);
  if (solver_with_tracer(board, tracer_2)) {
    cout << "'mystery3' solved with " << tracer_2 << " recursions" << endl << endl;
  } else {
    cout << "No solution found for 'mystery3'." << endl;
  cout << '\n';
  }


  //STEP 3---------------------------------------------------------------------
  //tests variation in order of input feed 1-9 per cell in puzzle

  cout << "**********" << endl;
  cout << endl << "Third - hypothesis that function_solver testing inputs ordered 1-9 are \n";
  cout << "biased towards solutions that start with low numbers. Hence adapted solver using \n";
  cout << "random ordered list of input characters 1-9 \n" << endl;

  //reset tracers
  tracer_1 = tracer_2 = 0;

  //create inputs character array from 1-9
  char inputs[9];
  for (int count = 0; count < 9; count++) {
    inputs[count] = '1' + count;
  }

  //testing for mystery1 -----------------------------

  int min1 = 200000, max1 = 0;
  int total1 = 0;
  
  for (int count = 1; count <= 100; count++) {

    int recursion_tracker = 0;

    random_shuffle(inputs, inputs+9);
    load_board("mystery1.dat", board);
    solver_with_tracer_randomised(board, recursion_tracker, inputs);

    total1 += recursion_tracker;

    if (recursion_tracker > max1) {
      max1 = recursion_tracker;
    }
    
    if (recursion_tracker < min1) {
      min1 = recursion_tracker;
    }
  }

  //testing for mystery3 -----------------------------

  int min3 = 2000000, max3 = 0;
  int total3 = 0;
  
  for (int count = 1; count <= 100; count++) {

    int recursion_tracker = 0;

    random_shuffle(inputs, inputs+9);
    load_board("mystery3.dat", board);
    solver_with_tracer_randomised(board, recursion_tracker, inputs);

    total3 += recursion_tracker;

    if (recursion_tracker > max3) {
      max3 = recursion_tracker;
    }
    
    if (recursion_tracker < min3) {
      min3 = recursion_tracker;
    }
  }

  cout << endl << "Average of 100 iterations for mystery1: " << total1/100 << endl;
  cout << "Average of 100 iterations for mystery3: " << total3/100 << endl;

  cout << endl << "Min-Max for Mystery1: " << min1 << " - " << max1 << endl;
  cout << "Min-Max for Mystery3: " << min3 << " - " << max3 << endl;

  
  //STEP 4---------------------------------------------------------------------
  //tests solving using human method of completing "only_option" squares first

  load_board("easy.dat", board);

  display_board(board);
  int iterations = 0;

  while (!is_complete(board)){
    iterations++;
    fill_all_definite_moves(board);
  }

  cout << "Number of iterations to solve 'easy' puzzle: " << iterations << endl;
  
  load_board("medium.dat", board);

  display_board(board);
  iterations = 0;

  while (!is_complete(board)){
    iterations++;
    fill_all_definite_moves(board);
  }

  cout << "Number of iterations to solve 'medium' puzzle: " << iterations << endl;

  //NB Mystery 1 and 3 are unsolvable using simple unique candidate deduction
  
  return 0;
}
