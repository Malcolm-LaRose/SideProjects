// First, rewrite tic tac toe to be graphics agnostic
	// That means that it doesn't choose a particular method of graphically displaying its data
	// All of the background logic remains the same
	// Make background logic modular
	// Apply background logic to SDL graphics


class Cell {
public:
    Cell() : row(0), col(0), state('e') {}

    Cell(int row, int col) : row(row), col(col), state(0) {} // Constructor that takes row and col

private:
    int row; // Top left origin
    int col; // Top left origin
    char state; // o,x,e --> empty state shows nothing in the Cell
};

class GameBoard {
public:
    
    void initGameBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                gameData[i][j] = Cell(i, j); // Construct Cell objects with row and col
            }
        }
    }

private:
    Cell gameData[3][3]; // Array of cells
};


class TicTacSDL {
public:

    TicTacSDL() : playerOne('x'), playerTwo('o'), currentPlayer(playerOne) {
		// Initialize GameBoard

	}

    // Start functions
    void initializeGame() {} // For now make player one X, later give an option
    
    // Loop functions
    void displayBoard() {} // Shown after init and after each gameBoard update
    void checkForWin() {}
    void checkForCat() {}
    void declareWinner() {}
    void incrementTurn() {}

    void gameLoop() {}

    // Cleanup
    void cleanUp() {}



private:
    GameBoard gameBoard; //  maybe need a ptr/ref
    char playerOne;
    char playerTwo;
    char currentPlayer = playerOne;


};

int main() {
    TicTacSDL TTSDL;


    return 0;
}