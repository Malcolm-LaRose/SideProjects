#include <iostream>
//#include <string>
#include <vector>


class ConnectFour {
public:

	ConnectFour() : boardState(rows, std::vector<char>(cols, ' ')), playerOne(' '), playerTwo(' '), currentPlayer(playerOne) {}

	// Input handling

	char validateCharInput() {}

	char validateYesNoInput() {}

	int validateIntInput() {}

	// Gameplay

	char choosePlayerOne() {}

	void initPlayers() {}


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

			// Print cell content and vertical borders
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
	
	void printPlayers() {}

	void setGameState() {}

	void getPlayerMove() {}

	void incrementTurn() {}

	void endGame() {}

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
			game.checkForWin();
			game.checkForTie();
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
	ConnectFour testGame;

	testGame.displayGameBoard();

	return 0;
}