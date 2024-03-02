#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>


void outputPaddedText(std::string inputText, int padding) {
    // Output the padding followed by the text
    std::cout << std::string(padding, ' ') << inputText << std::endl;
}


class gameData {
public:
    // Constructor to initialize with empty cells
    gameData() : board(3, std::vector<char>(3, ' ')), firstPlayer(' '), secondPlayer(' '), currentPlayer(firstPlayer) {}

    char validateInput(std::string message) {
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
    

    char choosePlayerOne() {
       
        return validateInput("Should 'X' or 'O' go first?");

    }


    void initializePlayers() {

        firstPlayer = choosePlayerOne();
        
        if (firstPlayer == 'X') {
            secondPlayer = 'O';
        }
        else {
            secondPlayer = 'X';
        }

        currentPlayer = firstPlayer;

    }

    void printPlayers() {
        std::cout << "Player One: " << firstPlayer << std::endl;
        std::cout << "Player Two: " << secondPlayer << std::endl;
    }


    // Function to set the game state without default parameters
    void setGameState(int row, int col, char symbol) {
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3) { // Validates input
            board[row - 1][col - 1] = symbol; // Places symbol
        }
    }

    // Function to display the game board
    void displayGameBoard() {
        std::string horizontalSeparator = " -----------\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << " ";
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << board[i][j] << " "; // Output the value of each cell in the game state
                if (j < 2) std::cout << "|";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << horizontalSeparator;
        }
    }

    void getPlayerMove() {
        std::cout << "Player " << currentPlayer << ", choose a square! Matrix input rules apply." << std::endl;
        std::pair<int, int> playerInput;

        // Loop until valid input is received
        while (true) {
            std::cout << "Enter the row: ";
            std::cin >> playerInput.first;

            std::cout << "Enter the column: ";
            std::cin >> playerInput.second;


            // Check if the input is within valid range (1 to 3 for a 3x3 matrix)
            if (playerInput.first >= 1 && playerInput.first <= 3 &&
                playerInput.second >= 1 && playerInput.second <= 3) {
                // Simplify names
                int row = playerInput.first;
                int col = playerInput.second;
                // Check if the selected cell is empty
                if (board[row - 1][col - 1] == ' ') {
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

    void checkForWin() {
        if (/*Win conditions*/ true) {
            // Declare a player a winner
            // Ask to play again? (maybe)

        }
        
    }

    void gameLoop() {
        bool validGameState = true;

        while (validGameState) {



        }
    
    }

/*std::string board =
    "   |   |   \n"
    "-----------\n"
    "   |   |   \n"
    "-----------\n"
    "   |   |   \n";*/


private:
    std::vector<std::vector<char>> board;
    char firstPlayer;
    char secondPlayer;
    char currentPlayer;

};


void outputNLines(int n) {

    int i = 0;
    while (i < n) {
        std::cout << '\n';
        i++;
    }

}

void TicTacToe() {

    /*outputNLines(2);
    outputCenteredText("Mal Tac Toe!");
    outputNLines(4);
    emptyGameBoard();*/

    gameData GameData;
    GameData.initializePlayers();
    GameData.printPlayers();

    // Take first turn
    // Proceed through sequence of turns
    // Check for illegal moves
    // Check for winning moves
    // Check for a full board
    // Display results


    bool validGameState = true;

    while (validGameState) {

        GameData.displayGameBoard();
        GameData.getPlayerMove();
        GameData.incrementPlayersTurn();

    }

}


int main()
{
    

    TicTacToe();



    return 0;
}
