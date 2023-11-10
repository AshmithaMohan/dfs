#include <stdio.h>
#include <stdlib.h>

// Recursive function for finding valid queen placements on the chess board
void place_next_queen(int queens[8], int column_j, int column[8],
                      int diagonal_up[15], int diagonal_down[15]) {
  for (int row_i = 0; row_i < 8; ++row_i) {
    // Check if a queen can be placed on the current square
    if (column[row_i] &
        diagonal_up[7 + column_j - row_i] &
        diagonal_down[column_j + row_i]) {

      // Place a queen on the chess board
      queens[column_j] = row_i;
      column[row_i] = 0;
      diagonal_up[7 + column_j - row_i] = 0;
      diagonal_down[column_j + row_i] = 0;
      ++column_j;

      if (column_j == 8) {
        // Chess board is full
        for (int row = 0; row < 8; ++row) {
          printf("%d ", queens[row] + 1);
        }
        printf("\n");
      } else {
        // Recursive call to find next queen placement on the chess board
        place_next_queen(queens, column_j, column, diagonal_up, diagonal_down);
        // Removes a queen from the chess board in the given column to backtrack
      }
      --column_j;
      diagonal_down[column_j + row_i] = 1;
      diagonal_up[7 + column_j - row_i] = 1;
      column[row_i] = 1;
    }
  }
}

int main() {
  // Parameters for solver
  int queens[8] = {0};
  int column_j = 0;
  int column[8];  // Attacks along a column
  int diagonal_up[15];  // Attacks along diagonals
  int diagonal_down[15];
  
  // Initialize chess board
  for(int index = 0; index < 8; ++index) {
    column[index] = 1;
    diagonal_up[index] = 1;
    diagonal_down[index] = 1;
  }
  
  for(int index = 8; index < 15; ++index) {
    diagonal_up[index] = 1;
    diagonal_down[index] = 1;
  }

  // Start solver algorithm
  place_next_queen(queens, column_j, column, diagonal_up, diagonal_down);

  return EXIT_SUCCESS;
}