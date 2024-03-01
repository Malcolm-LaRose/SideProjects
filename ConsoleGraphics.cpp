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
    gameData() : board(3, std::vector<char>(3, ' ')), firstPlayer(' '), secondPlayer(' ') {}

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

    }

    void printPlayers() {
        std::cout << "Player One: " << firstPlayer << std::endl;
        std::cout << "Player Two: " << secondPlayer << std::endl;
    }

    // Function to set the game state
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
                std::cout << " " << board[i][j] << " "; // Adjust setw to 2 for proper spacing
                if (j < 2) std::cout << "|";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << horizontalSeparator;
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
    

};


void outputNLines(int n) {

    int i = 0;
    while (i < n) {
        std::cout << '\n';
        i++;
    }

}


int main()
{
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

    GameData.displayGameBoard();





    return 0;
}
