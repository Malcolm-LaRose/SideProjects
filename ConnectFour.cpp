#include <iostream>
#include <vector>

// Future goals
// Make ConnectN
// Thoroughly check for bugs
// Integrate with tic tac toe into a bundle of games in one program
// Make winning move more apparent on final board
// 
//



class ConnectFour {
public:

	// Constructor
	ConnectFour()
		: rows(rows), cols(cols), boardState(rows, std::vector<char>(cols, ' ')),
		playerOne(' '), playerTwo(' '), currentPlayer(playerOne) {}

	// Main Loop
	void gameLoop(ConnectFour& game) {
		bool validGameState = true;
		bool winningGameState = false;

		//game.initPlayers();
		game.gameInit();
		game.printPlayers();

		while (validGameState && (!winningGameState)) {
			game.displayGameBoard();
			game.getPlayerMove();
			game.checkForWin();
			game.checkForFull();
			game.incrementTurn();
		}
	}

private:

	int rows;
	int cols;

	std::vector<std::vector<char>> boardState;
	char playerOne;
	char playerTwo;
	char currentPlayer;
	std::pair<int, int> lastPlayedPosition;

	// Define direction vectors for each of the eight possible directions
	const std::vector<std::pair<int, int>> directions = {
		{1, 1},   // ↘
		{1, 0},   // ↓
		{1, -1},  // ↙
		{0, -1},  // ←
		{-1, -1}, // ↖
		// {-1, 0},  // ↑ not necessary, will never find a solution above the last placed piece
		{-1, 1},  // ↗
		{0, 1}    // →
	};


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
		int playerInput;

		// Keep asking until valid input is received
		while (true) {
			std::cout << message << std::endl;
			std::cin >> playerInput;

			// Validate input
			if (playerInput >= lowBound && playerInput <= highBound) {
				return playerInput;
			}
			else {
				// Invalid input
				std::cout << "Invalid input! Please enter a number between " << lowBound << " and " << highBound << " only. Try again." << std::endl;
				// Clear input buffer
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

	// Gameplay and Graphics

	char choosePlayerOne() {
		return validateCharInput("Should X or O go first ? ");
	}

	void initPlayers() {

		playerOne = choosePlayerOne();

		if (playerOne == 'X') {
			playerTwo = 'O';
		}
		else {
			playerTwo = 'X';
		}
		currentPlayer = playerOne;
	}

	void initBoard() {
		rows = validateIntInput("Select a number of rows or press enter for default (6)", 4, 64);
		cols = validateIntInput("Select a number of columns or press enter for default (7)", 4, 64);

		boardState.resize(rows, std::vector<char>(cols, ' '));
	}

	void gameInit() {
		initPlayers();
		initBoard();
	}

	void displayGameBoard() {
		// Print column numbers
		std::cout << "   ";
		for (int j = 0; j < cols; ++j) {
			if (j < 8) {
				std::cout << "  " << j + 1 << " ";
			}
			else if (j == 8) {
				std::cout << "  " << j + 1 << "  ";
			}
			else {
				std::cout << " " << j + 1 << " ";
			}
		}
		std::cout << std::endl;

		// Print top border of the board
		std::cout << "   ";
		for (int k = 0; k < cols; ++k) {
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;

		// Loop through each row
		for (int i = 0; i < rows; ++i) {
			// Print row number
			if (i < 9) {
				std::cout << " " << i + 1 << " ";
			}
			else {
				std::cout << i + 1 << " ";
			}

			// Print cell contents and vertical borders
			for (int j = 0; j < cols; ++j) {
				std::cout << "| " << boardState[i][j] << " ";
			}
			std::cout << "|" << std::endl;

			// Print horizontal border between rows
			std::cout << "   ";
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
		// Place the tile starting at the bottom of the column


		int r = rows - 1;
		while (r >= 0) {
			if (boardState[r][column - 1] == ' ') {
				boardState[r][column - 1] = player;
				lastPlayedPosition.first = r;
				lastPlayedPosition.second = column - 1;
				break;
			}

			else {
				r--;
			}
		}
	}

	bool isColumnFull(int col) {
		for (int i = 0; i < rows; ++i) {
			if (boardState[i][col - 1] == ' ') {
				return false; // Column is not full, as there's an empty space
			}
		}
		return true; // Column is full, as no empty space was found
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

			if (playerChoice >= 1 && playerChoice <= cols) {
				int col = playerChoice;

				if (!isColumnFull(col)) // If the column isn't full (last slot is empty)
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


	bool checkForFull() {
		for (int i = 0; i < rows; i++) {

			for (int j = 0; j < cols; j++) {

				if (boardState[i][j] == ' ') {
					return false;
				}
			}
		}
		return true;
	}

	bool isInBounds(int row, int col) {
		return (row >= 0 && row < rows && col >= 0 && col < cols);
	}

	bool checkForTie() { // To account for other possible tie conditions (if any?)
		if (checkForFull()) {
			std::cout << "Game ends in a tie!" << std::endl;
			endGame();
		}
	}

	bool searchFour(int rowInc, int colInc) {
		int sameCount = 1; // If this equals four, report a win

		int newRow = lastPlayedPosition.first + rowInc;
		int newCol = lastPlayedPosition.second + colInc;

		while (((newRow - lastPlayedPosition.first) < 4) && ((newCol - lastPlayedPosition.second) < 4) && isInBounds(newRow, newCol)) {
			if (boardState[newRow][newCol] == currentPlayer) {
				sameCount++;
				if (sameCount == 4) {
					return true; // Found a win
				}
			}
			else {
				break; // Break the loop if symbols don't match
			}
			newRow += rowInc; // Move to the next position in the current direction
			newCol += colInc;
		}
		return false;
	}

	bool checkForWin() {
		char& winningPlayer = currentPlayer;
		bool isWinning = false;
		std::pair<int, int> winningDir;

		for (const auto& direction : directions) {
			isWinning = searchFour(direction.first, direction.second);
			if (isWinning) {
				winningDir.first = direction.first;
				winningDir.second = direction.second;
				std::cout << "Win detected in direction " << winningDir.first << winningDir.second << std::endl;
				return true;

			}
		}
		return isWinning;
	}
};


int main() {
	ConnectFour realGame;
	realGame.gameLoop(realGame);
	return 0;
}