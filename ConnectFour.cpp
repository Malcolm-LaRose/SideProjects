#include <iostream>
#include <vector>


// Forward delcarations




class ConnectFour {
public:

	ConnectFour() : boardState(rows, std::vector<char>(cols, ' ')), playerOne(' '), playerTwo(' '), currentPlayer(playerOne) {}

	// Input handling

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

	int validateIntInput(std::string message, int lowBound, int highBound) {
		char playerInput;

		// Keep asking until valid input is received
		while (true) {
			std::cout << message << std::endl;
			std::cin >> playerInput;

			// Validate input
			if (playerInput >= 1 && playerInput <= 7) {
				return playerInput;
			}
			else {
				// Invalid input
				std::cout << "Invalid input! Please enter a number between " << lowBound <<" and " << highBound << " only. Try again." << std::endl;
				// Clear input buffer
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

	// Gameplay

	char choosePlayerOne() {
	
		return validateCharInput("Should X or O go first ? ");
	}

	void initPlayers() {
	
		playerOne = choosePlayerOne();

		if (playerOne == 'X') {
			playerTwo == 'O';
		}
		else {
			playerTwo = 'X';
		}

		currentPlayer = playerOne;

	}


	// Graphics and output
	void displayGameBoard() {
		// Print column numbers
		std::cout << "   ";
		for (int j = 0; j < cols; ++j) {
			std::cout << " " << j + 1 << "  ";
		}
		std::cout << std::endl;

		// Print top border of the board
		std::cout << "  ";
		for (int k = 0; k < cols; ++k) {
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;

		// Loop through each row
		for (int i = 0; i < rows; ++i) {
			// Print row number
			std::cout << i + 1 << " ";

			// Print cell contents and vertical borders
			for (int j = 0; j < cols; ++j) {
				std::cout << "| " << boardState[i][j] << " ";
			}
			std::cout << "|" << std::endl;

			// Print horizontal border between rows
			std::cout << "  ";
			for (int k = 0; k < cols; ++k) {
				std::cout << "+---";
			}
			std::cout << "+" << std::endl;
		}
	
	}
	
	void printPlayers() {
		std::cout << "Player One: " << playerOne << std::endl;
		std::cout << "Player Two: " << playerTwo << std::endl;
	}

	void setGameState(int column, char player) {
		// Place the tile at the top of the column

		int c = rows - 1;
		while (c >= 0) {
			if (boardState[c][column - 1] == ' ') {
				boardState[c][column - 1] = player;
				break;
			}

			else {
				c--;
			}	

		}



	}

	void getPlayerMove() {
		std::cout << "Player " << currentPlayer << ", choose a column!" << std::endl;
		int playerChoice;

		while (true)
		{
			while (!(std::cin >> playerChoice)) {
			
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// Prompt the user to enter a valid integer
				std::cout << "Invalid input! Please enter an integer: ";
			}

			if (playerChoice >= 1 && playerChoice <= 7) {
				int& col = playerChoice;

				if (boardState[0][cols - 1] == ' ') // If the column isn't full (last slot is empty)
				{
					setGameState(col, currentPlayer);
					break;
				}
				else {
					std::cout << "Selected column is already occupied! Select another column." << std::endl;
				}
			}
			else {
				std::cout << "Invalid input! Column must be between 1 and " << cols << std::endl;
			}

		}
	}

	void incrementTurn() {
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

	bool isColumnFull(int col) {
		int i = 0;

		while (i < rows) {
			if (boardState[i][col] == ' ') {
				return false;
			}
			else {
				i++;
			}

		}
		return true;

	}

	bool moveIsValid() {

		// Is cell occupied

		// Is column full
	

	}

	bool checkForWin() {

		// Horizontal 4

		// Vertical 4

		// Diagonal 4
	
	
	}

	bool checkForTie() {

		// Is board full?
		// Can handle as putting the top row in the bottom and clearing the rest or ending the game
	
	
	}

	void gameLoop(ConnectFour& game) {
		bool validGameState = true;
		bool winningGameState = false;

		game.initPlayers();
		game.printPlayers();

		while (validGameState && (!winningGameState)) {
			game.displayGameBoard();
			game.getPlayerMove();
			//game.checkForWin();
			//game.checkForTie();
			game.incrementTurn();
		}
	
// End of C4 class
	}


private:

	const int rows = 6;
	const int cols = 7;

	std::vector<std::vector<char>> boardState;
	char playerOne;
	char playerTwo;
	char currentPlayer;




};


int main() {
	ConnectFour realGame;

	// realGame.displayGameBoard(); // test statement
	realGame.gameLoop(realGame);

	return 0;
}