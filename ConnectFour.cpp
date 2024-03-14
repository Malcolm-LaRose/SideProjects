#include <iostream>
//#include <string>
#include <vector>


class ConnectFour {
public:

	ConnectFour() : boardState(rows, std::vector<char>(cols, ' ')), playerOne(' '), playerTwo(' '), currentPlayer(playerOne) {}


	// Graphics and output
	void displayGameBoard() {
		for (int i = 0; i < rows; ++i) {
			// Print top border of each row
			for (int k = 0; k < cols; ++k) {
				std::cout << "+---";
			}
			std::cout << "+" << std::endl;

			// Print cell content and vertical borders
			for (int j = 0; j < cols; ++j) {
				std::cout << "| " << boardState[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}

		// Print bottom border of the board
		for (int k = 0; k < cols; ++k) {
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;
	
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