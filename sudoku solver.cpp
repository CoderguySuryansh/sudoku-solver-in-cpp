#include <iostream>
#include <vector>

using namespace std;

const int N = 9; // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != N - 1) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != N - 1) {
            cout << "------+-------+------" << endl;
        }
    }
}

// Function to check if a number can be placed in the current cell
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if the number already exists in the current row or column
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Find the first empty cell (cell with value 0)
    bool foundEmpty = false;
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) {
            break;
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (!foundEmpty) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            // Place the number in the current cell
            grid[row][col] = num;

            // Recursively solve the remaining part of the puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing the number doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed, backtrack to the previous cell
    return false;
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Sudoku Solution:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
