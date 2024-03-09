#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

class TicTacToe {
public:

    TicTacToe() : boardState(3, std::vector<char>(3, ' ')), playerOne(' '), playerTwo(' '), currentPlayer(playerOne) {}

    // FUNCTIONS RELATED TO INPUT VALIDATION

    char validateCharInput(std::string message) {
        char playerInput;

        // Keep asking until valid input is received
        while (true) {
            std::cout << message << std::endl;
            std::cin >> playerInput;

            // Convert to uppercase for caseless comparison
            playerInput = std::toupper(playerInput);

            // Validate input
            if (playerInput == 'X' || playerInput == 'O') {
                return playerInput;
            }
            else {
                // Invalid input
                std::cout << "Invalid input! Please enter 'X' or 'O' only. Try again." << std::endl;
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    char validateYesNoInput(std::string message) {
        char playerInput;

        // Keep asking until valid input is received
        while (true) {
            std::cout << message << std::endl;
            std::cin >> playerInput;

            // Convert to uppercase for caseless comparison
            playerInput = std::toupper(playerInput);

            // Validate input
            if (playerInput == 'Y' || playerInput == 'N') {
                return playerInput;
            }
            else {
                // Invalid input
                std::cout << "Invalid input! Please enter 'Y' or 'N' only. Try again." << std::endl;
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    }

    int validateIntInput(std::string message) {
        char playerInput;

        // Keep asking until valid input is received
        while (true) {
            std::cout << message << std::endl;
            std::cin >> playerInput;

            // Validate input
            if (playerInput >= 1 && playerInput <= 3) {
                return playerInput;
            }
            else {
                // Invalid input
                std::cout << "Invalid input! Please enter a number between 1 and 3 only. Try again." << std::endl;
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }



    // FUNCTIONS RELATED TO GAMEPLAY

    char choosePlayerOne() {

        return validateCharInput("Should 'X' or 'O' go first?");

    }

    void initializePlayers() {

        playerOne = choosePlayerOne();

        if (playerOne == 'X') {
            playerTwo = 'O';
        }
        else {
            playerTwo = 'X';
        }

        currentPlayer = playerOne;

    }

    // Graphics and output
    void displayGameBoard() {
        std::string horizontalSeparator = " -----------\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << " ";
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << boardState[i][j] << " "; // Output the value of each cell in the game state
                if (j < 2) std::cout << "|";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << horizontalSeparator;
        }
    }

    void printPlayers() {
        std::cout << "Player One: " << playerOne << std::endl;
        std::cout << "Player Two: " << playerTwo << std::endl;
    }

    // Function to set the game state without default parameters
    void setGameState(int row, int col, char symbol) {
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3) { // Validates input
            boardState[row - 1][col - 1] = symbol; // Places symbol
        }
    }

    void getPlayerMove() {
        std::cout << "Player " << currentPlayer << ", choose a square! Matrix input rules apply." << std::endl;
        std::pair<int, int> playerInput;

        // Loop until valid input is received
        while (true) {
            std::cout << "Enter the row: ";
            while (!(std::cin >> playerInput.first)) {
                // Clear the error flag and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Prompt the user to enter a valid integer
                std::cout << "Invalid input! Please enter an integer: ";
            }

            std::cout << "Enter the column: ";
            while (!(std::cin >> playerInput.second)) {
                // Clear the error flag and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Prompt the user to enter a valid integer
                std::cout << "Invalid input! Please enter an integer: ";
            }


            // Check if the input is within valid range (1 to 3 for a 3x3 matrix)
            if (playerInput.first >= 1 && playerInput.first <= 3 &&
                playerInput.second >= 1 && playerInput.second <= 3) {
                // Simplify names
                int row = playerInput.first;
                int col = playerInput.second;
                // Check if the selected cell is empty
                if (boardState[row - 1][col - 1] == ' ') {
                    // Set the game state and break out of the loop
                    setGameState(row, col, currentPlayer);
                    break;
                }
                else {
                    // Cell is already occupied, prompt the player to choose again
                    std::cout << "Selected cell is already occupied! Choose another cell." << std::endl;
                }
            }
            else {
                // Invalid input, prompt the player again
                std::cout << "Invalid input! Row and column must be between 1 and 3." << std::endl;
            }
        }
    }

    void incrementPlayersTurn() {
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        }
        else {
            currentPlayer = 'X';
        }

    }

    void endGame() {
        displayGameBoard();
        std::cout << std::endl << "Thanks for playing!" << std::endl;
        system("pause");
        exit(0);
    }

    void checkForWin() {
        char winner = ' '; // Initialize the winner variable

        // Check row and column win conditions
        for (int i = 0; i < 3; ++i) {
            // Check horizontal win conditions
            if (boardState[i][0] == boardState[i][1] && boardState[i][1] == boardState[i][2] && boardState[i][0] != ' ') {
                winner = boardState[i][0]; // Set the winner
                break; // Exit the loop if a winner is found
            }

            // Check vertical win conditions
            if (boardState[0][i] == boardState[1][i] && boardState[1][i] == boardState[2][i] && boardState[0][i] != ' ') {
                winner = boardState[0][i]; // Set the winner
                break; // Exit the loop if a winner is found
            }
        }

        // Check diagonal win conditions
        if ((boardState[0][0] == boardState[1][1] && boardState[1][1] == boardState[2][2] && boardState[0][0] != ' ') ||
            (boardState[0][2] == boardState[1][1] && boardState[1][1] == boardState[2][0] && boardState[0][2] != ' ')) {
            winner = boardState[1][1]; // Set the winner
        }

        // Declare the winner if found
        if (winner != ' ') {
            std::cout << "Player " << winner << " has won!" << std::endl;
            endGame();
        }
    }

    void checkForCat() {
        // Loop through every square
        // If no square is empty, end game as cat

        bool catFound = true;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (boardState[i][j] == ' ') {
                    catFound = false;
                    break; // Stop looking for a cat, board isn't full
                }

            }
        }

        if (catFound == false) {
            return;

        }
        else {

            std::cout << "The game ends in a cat!" << std::endl;
            endGame();
        }

    }

    void gameLoop(TicTacToe& game) {
        bool validGameState = true;
        bool winningGameState = false;

        game.initializePlayers();
        game.printPlayers();

        while (validGameState && (!winningGameState)) {


            // Take first turn
            // Proceed through sequence of turns
            // Check for illegal moves
            // Check for winning moves
            // Check for a full board
            // Display results

            game.displayGameBoard();
            game.getPlayerMove();
            game.checkForWin();
            game.checkForCat();
            game.incrementPlayersTurn();

        }
    
    }



private:
    std::vector<std::vector<char>> boardState;
    char playerOne;
    char playerTwo;
    char currentPlayer;

};

int main() {
    TicTacToe ttt;
    ttt.gameLoop(ttt);

}