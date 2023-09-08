#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 9;

bool isSafe(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + boxRowStart][j + boxColStart] == num)
                return false;

    return true;
}

void printBoard(int grid[N][N])
{

    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU!                                      |" << endl;
    cout << "\t\t\t|       Replace the zeros with numbers 1 - 9  to solve the puzzle.               |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (col == 3 || col == 6)
                cout << " | ";
            cout << grid[row][col] << " ";
        }
        if (row == 2 || row == 5)
        {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}


bool solveSudoku(int board[N][N], int row, int col)
{
    if (row == N - 1 && col == N)
        return true;
    if (col == N)
    {
        row++;
        col = 0;
    }
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;

            if (solveSudoku(board, row, col + 1))
                return true;

            board[row][col] = 0;
        }
    }
    return false;
}

bool isSolvedCompletely(int grid[N][N])
{
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}

void playGame(int board[N][N])
{
    int ch;
    int row, col, num;
    while (true)
    {
        printBoard(board);
        cout << endl << endl;
        cout << "Unable to solve? Enter -1 as row, col and num to view the solved sudoku." << endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;

        if (row == -1 || col == -1 || num == -1)
        {
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << endl;
            cout << "Better luck next time!!!" << endl;
            return;
        }
        if (isSolvedCompletely(board))
            break;
        row--;
        col--;
        if (!isSafe(board, row, col, num))
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = num;
    }
    bool solved = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
            {
                solved = false;
                break;
            }
        }
    }

    if (solved)
    {
        cout << "Congratulations! You have solved the puzzle." << endl;
        printBoard(board);
    }
    else
    {
        cout << "Puzzle not solved. Better luck next time." << endl;
    }

}

int main()
{

    system("title Sudoku");
    system("color E4");
    int board[N][N] =
    {
      {0, 0, 2, 8, 1, 0, 0, 4, 3},
      {4, 3, 0, 0, 0, 7, 1, 6, 0},
      {1, 0, 6, 4, 9, 0, 0, 2, 0},
      {0, 2, 7, 5, 3, 0, 8, 0, 0},
      {0, 9, 0, 1, 0, 4, 6, 0, 2},
      {8, 4, 0, 7, 0, 0, 0, 5, 9},
      {9, 0, 4, 0, 0, 5, 2, 0, 6},
      {0, 5, 0, 0, 2, 8, 4, 9, 0},
      {0, 6, 8, 0, 4, 1, 0, 0, 7}
    };

    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU!                                      |" << endl;
    cout << "\t\t\t|       Replace the zeros with numbers 1 - 9  to solve the puzzle.               |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    while (true)
    {

        int choice;
        cout << endl << endl;
        cout << "\t\t[1] Solve the Sudoku" << endl;
        cout << "\t\t[2] Unable to solve? View the solved Sudoku" << endl;
        cout << "\t\t[3] Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            playGame(board);
            break;
        case 2:
            if (solveSudoku(board, 0, 0))
            {
                cout << "Completely Solved Sudoku is: " << endl;
                cout << endl << endl;
                for (int row = 0; row < N; row++)
                {
                    for (int col = 0; col < N; col++)
                    {
                        if (col == 3 || col == 6)
                            cout << " | ";
                        cout << board[row][col] << " ";
                    }
                    if (row == 2 || row == 5)
                    {
                        cout << endl;
                        for (int i = 0; i < N; i++)
                            cout << "---";
                    }
                    cout << endl;
                }
                cout << endl;
                cout << "Better luck next time!!!" << endl;
            }
            else
                cout << "No solution found" << endl;
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice" << endl;
        }
        return 0;
    }
}