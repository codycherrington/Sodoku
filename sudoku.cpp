#include <iostream>
#include <ctime>

using namespace std;

// Function to check if placing 'n' at position (x, y) in the row is valid
bool checkRow(int n, int board[][9], int x, int y) {

    // Iterate backwards from the current position (x, y) to check the row
    for (int i = x - 1; i >= 0; i--) {
        // If 'n' is found in the same row, return false
        if (n == board[i][y]) {
            return false;
        }
    }
    // If 'n' is not found in the same row, return true
    return true;
}

// Function to check if placing 'n' at position (x, y) in the column is valid
bool checkCol(int n, int board[][9], int x, int y) {

    // Iterate forwards from the current position (x, y) to check the column
    for (int i = y + 1; i < 9; i++) {
        // If 'n' is found in the same column, return false
        if (n == board[x][i]) {
            return false;
        }
    }
    // If 'n' is not found in the same column, return true
    return true;
}

// Function to check if placing 'n' at position (x, y) in the 3x3 box is valid
bool checkBox(int n, int board[][9], int x, int y) {

    // Calculate the starting position of the 3x3 box based on (x, y)
    int startX = (x / 3) * 3;
    int startY = (y / 3) * 3;
    // Iterate over the cells in the 3x3 box
    for (int i = startX; i < startX + 3; ++i) {
        for (int j = startY; j < startY + 3; ++j) {
            // If 'n' is found in the same box (excluding the current position), return false
            if (i != x && j != y && n == board[i][j]) {
                return false;
            }
        }
    }
    // If 'n' is not found in the same box, return true
    return true;
}

// Function to check if the user has won the game
bool checkWin(int solvedBoard[][9], int userBoard[][9]) {

    for (int y = 0; y < 9; ++y) { 
        for (int x = 0; x < 9; ++x) {
            // If any cell in the user board doesn't match the corresponding cell in the solved board, return false
            if (userBoard[x][y] != solvedBoard[x][y]) {
                return false; 
            }
        }
    }
    // If all cells match, return true
    return true; 
}

// Function to randomly fill the Sudoku board
void fillBoard(int board[][9]) {

    // Seed the random number generator
    srand(time(NULL));
    int y = 8;
    // Iterate over each row of the board
    while (y >= 0) {
        int x = 0;
        // Iterate over each column of the row
        while (x < 9) {
            // Generate a random number between 1 and 9
            int n = (rand() % 9) + 1;
            // Check if 'n' can be placed at position (x, y) based on row, column, and box constraints
            if (checkRow(n, board, x, y) == false) {
                // If 'n' violates the row constraint, decrement x to retry placing 'n' in the same row
                x--;
                continue;
            } 
            else if (checkCol(n, board, x, y) == false) {
                // If 'n' violates the column constraint, skip to the next column
                continue;
            }
            else if (checkBox(n, board, x, y) == false) {
                // If 'n' violates the box constraint, skip to the next column
                continue;
            }
            else {
                // If 'n' satisfies all constraints, place it at position (x, y)
                board[x][y] = n;
            }
            // Move to the next column
            x++;
        }
        // Move to the next row
        y--;
    }
}

// Function to fill the user board based on the difficulty level
void fillUserBoard(int solvedBoard[][9], int userBoard[][9]) {

    // Copy the solved board to the user board
    for (int y = 8; y >= 0; --y) {
        for (int x = 0; x < 9; x++) {
            int n = solvedBoard[x][y];
            userBoard[x][y] = n;
        }
    }

    // Prompt the user to select the difficulty level
    int difficulty = 0;
    while (true) {

        //Main menu header
        cout << "            Main Menu      " << endl;
        cout << "     -----------------------" << endl;
        cout << "      Select your difficulty" << endl << endl;
        cout << "          1 for Easy" << endl; 
        cout << "          2 for Medium" << endl; 
        cout << "          3 for Hard" << endl;
        cout << "          0 to exit." << endl << endl;
        cout << "         Difficulty: "; 
        cin >> difficulty;

        // Validate the user input
        if (cin.fail()) {
            cout << endl << "       ***Invalid input***" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (difficulty == 0) {
            cout << endl << "       Thank you for playing!" << endl;
            cout << "    Written by Cody Cherrington." << endl << "               2024" << endl << endl << endl;
            exit(0);
        }

        if (difficulty != 1 && difficulty != 2 && difficulty != 3 && difficulty != 1998) {
            cout << endl << "       ***Invalid input***" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << endl << "     -----------------------" << endl;
        break;
    }

    // Determine the number of zeros to be added based on the difficulty level
    int numZeros;
    srand(time(NULL));
    if (difficulty == 1) {
        numZeros = rand() % 9 + 27;
    }
    if (difficulty == 2) {
        numZeros = rand() % 13 + 35;
    }
    if (difficulty == 3) {
        numZeros = rand() % 18 + 47;
    }
    if (difficulty == 1998) {
        numZeros = 1;
    }
    // Randomly replace cells with zeros to create the puzzle
    for (int i = 0; i < numZeros; ++i) {
        int x = rand() % 9;
        int y = rand() % 9;
        userBoard[x][y] = 0; 
    }
}

// Function to display the Sudoku board
void displayBoard(int board[][9], int& lives) {

    cout << endl;
    cout << "             x-value          " << endl;
    cout << "      1 2 3 | 4 5 6 | 7 8 9 " << endl;
    cout << "    +-------+-------+-------+" << endl;
    for (int y = 8; y >= 0; --y) {
        // Display the y-value on specific rows
        if (y == 8 || y == 1 || y == 0 || y == 7) {
            cout << "  " << y + 1 << " | ";
        }
        // Display "y-value" vertically
        if (y == 6) {
            cout << "y " << y + 1 << " | "; 
        }
        if (y == 5) {
            cout << "v " << y + 1 << " | "; 
        }
        if (y == 4) {
            cout << "a " << y + 1 << " | "; 
        } 
        if (y == 3) {
            cout << "l " << y + 1 << " | "; 
        }
        if (y == 2) {
            cout << "e " << y + 1 << " | ";
        }
        // Display the numbers in the Sudoku board
        for (int x = 0; x < 9; x++) {
            if (board[x][y] == 0) {
                cout << "  ";
            }
            else {
                cout << board[x][y] << " ";
            }
            // Display vertical lines to separate 3x3 boxes
            if (x == 2 || x == 5 || x == 8) {
                cout << "| ";
            }
        }
        cout << endl;
        // Display horizontal lines to separate 3x3 boxes and y-value rows
        if (y == 6) {
            cout << "| --+-------+-------+-------+" << endl;
        }
        if (y == 3) {
            cout << "u --+-------+-------+-------+" << endl;
        }
    }
    // Display remaining lives
    cout << "    +-------+-------+-------+" << endl;
    cout << "             Lives: " << lives << endl;
    cout << "            0 to exit" << endl;
}

// Function for user input and gameplay
void userInput(int userBoard[][9], int solvedBoard[][9]) {

    //Initialize values
    int x = 0;
    int y = 0;
    int n = 0;
    int lives = 3;

    // Display the initial state of the Sudoku board
    displayBoard(userBoard, lives);

    // Start time
    time_t start = time(NULL);
    
    while (true) {

        //Get x coordinate
        cout << endl << "Enter x value (1 through 9): ";
        cin >> x;

        if (x < 0 || x > 9) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cin.fail()) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (x == 0) {
            cout << endl;
            break;
        }

        //Get y coordinate
        cout << "Enter y value (1 through 9): ";
        cin >> y;

        if (y < 0 || y > 9) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cin.fail()) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (y == 0) {
            cout << endl;
            break;
        }

        // Check if the selected cell is already filled
        if (userBoard[x - 1][y - 1] > 0) {
            cout << endl << "   ***Cell already filled!***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        //Get number to enter in cell (x, y)
        cout << "Enter number (1 through 9): ";
        cin >> n;
        cout << endl;

        if (n < 0 || n > 9) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cin.fail()) {
            cout << endl << "     ***Invalid entry***" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (n == 0) {
            cout << endl;
            break;
        }

        // Check if the entered number matches the solution
        if (n != solvedBoard[x - 1][y - 1]) {
            lives--;
            if (lives == 0) {
                cout << "           Out of lives!" << endl << endl;
                break;
            }
            if (lives == 2) {
                cout << " Incorrect! You now have " << lives << " lives." << endl;
                displayBoard(userBoard, lives);
                continue;
            }
            if (lives == 1) {
                cout << " Incorrect! You now have " << lives << " life." << endl;
                displayBoard(userBoard, lives);
                continue;
            }
        }

        // Update the user board with the entered number
        cout << "       Position (" << x << "," << y << ") = " << n << endl;
        userBoard[x - 1][y - 1] = n;
        cout << endl << "     -----------------------" << endl;
        displayBoard(userBoard, lives);

        // Check if the user has won the game
        if (checkWin(solvedBoard, userBoard) == true) {

            // End time
            time_t end = time(NULL);
            int duration = difftime(end, start);

            int minutes = duration / 60;
            int seconds = duration % 60;

            cout << endl << "        Congratulations!!!" << endl << endl
                 << "     You solved the puzzle in " << endl << "     " << minutes << " minutes and "
                 << seconds % 60 << " seconds." << endl << endl;

            if (lives == 3) {
                cout << "    You had " << lives << " lives remaining." << endl << endl;
            }
            if (lives == 2) {
                cout << "    You had " << lives << " lives remaining." << endl << endl;
            }
            if (lives == 1) {
                cout << "    You had " << lives << " life remaining." << endl << endl;
            }
            break;
        }
    }
}

// Main function
int main() {

    cout << endl << endl << " Welcome to my Sudoku C++ Program!" << endl << endl;

    // Main game loop
    while (true) {

        // Initialize the solved board and user board
        int solvedBoard[9][9] = {0};
        int userBoard[9][9] = {0};
        //Initialize player choice to continue the game or not
        char choice = ' ';

        // Fill the solved board with random values
        fillBoard(solvedBoard);
        // Fill the user board based on the selected difficulty level
        fillUserBoard(solvedBoard, userBoard);
        // Start the game with user input
        userInput(userBoard, solvedBoard);

        // Ask the player if they want to play again
        while (true) {
            cout << "   Would you like to play again?" << endl << "   (Y/y for yes, N/n for no): ";
            cin >> choice;
            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << endl << "       ***Invalid input***" << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (cin.fail()) {
                cout << endl << "       ***Invalid input***" << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            else {
                break; 
            }
        }
        // Check the player's choice and continue or end the game accordingly
        if (choice == 'Y' || choice == 'y') {
            cout << endl << "     -----------------------" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 'N' || choice == 'n') {
            cout << endl << "       Thank you for playing!" << endl;
            cout << "    Written by Cody Cherrington." << endl << "               2024" << endl << endl << endl;
            break;
        }
    }
    
    return 0;
}
