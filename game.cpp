#include "game.h"
#include <iostream>

//constructor which takes the players of the game as arguments
Game::Game(Player &pOne, Player &pTwo) {
	playerOne = &pOne;
	playerTwo = &pTwo;

	//set up the gameBoard
	gameBoard = new BoardField*[BoardHeight];
	for (int i = 0; i < BoardHeight; i++) {
		gameBoard[i] = new BoardField[BoardWidth];
	}
	//fill the gameBoard as Empty
	for (int i = 0; i < BoardHeight; i++) {
		for (int j = 0; j < BoardWidth; j++) {
			gameBoard[i][j] = Empty;
		}
	}
}


//Publicly overrides the ()-operator. Returns the state of the board at 
//the given coordinate. The top left element has coordinate(0,0). Returns
//Empty if the coordinate is out of range of the board.
BoardField Game::operator()(int x, int y) const {
	if ((x >= 0 && x < BoardWidth) && (y >= 0 && y < BoardHeight))
		return gameBoard[y][x];
	return Empty;
}

//A public function which returns the current state of the game.
GameState Game::getState() {
	return gameState;
}

//A public function which returns true if the game is still running, 
//or false if the game concluded with either a draw or a player winning.
bool Game::isRunning() {
	if (gameState == P1Won || gameState == P2Won || gameState == Draw)
		return false;
	return true;
}

//A public function which returns true if the passed move is valid
//within the current state of the gameboard. For example, the function
//will return false if a HumanPlayer inputs a number that isn't between
// 1 and 7, or if an AiPlayer attempts to input a token in an already
// full column.
bool Game::isValidMove(int attemptedPlay) {
	//check that the attemptedPlay is between 1 and 7
	if (attemptedPlay < 0 || attemptedPlay > 6)
		return false;
	//check that the column attemptedPlay is trying to add to isn't full.
	if (gameBoard[0][attemptedPlay] != Empty)
		return false;
	//if neither of those cases, return true
	return true;
}


void Game::nextTurn() {
	//increment turn counter
	turnCounter++;
	//there are 7*6=42 slots in the game's board. if the number of turns
	//exceeds that, the game must have resulted in a draw.
	if (!(turnCounter <= 42)) {
		gameState = Draw;
		return;
	}

	int nextMove;
	//if turnCounter is odd, this is player 1's turn. if even, it is player 2's.
	if (turnCounter % 2 != 0) {
		//get input from first player while checking if input is valid. if
		//input is invalid, prompt player to try again.
		nextMove = playerOne->getNextTurn(*this);
		while (!isValidMove(nextMove)) {
			if(playerOne->getPlayerType(*this))
				std::cout << "Invalid move. Try again.\n";
			nextMove = playerOne->getNextTurn(*this);
		}
		if (!playerOne->getPlayerType(*this))
			std::cout << "AI drops a token in slot " << nextMove + 1 << ".\n";
	}
	else {
		nextMove = playerTwo->getNextTurn(*this);
		while (!isValidMove(nextMove)) {
			if (playerTwo->getPlayerType(*this))
				std::cout << "Invalid move. Try again.\n";
			nextMove = playerTwo->getNextTurn(*this);
		}
		if(!playerTwo->getPlayerType(*this))
			std::cout << "AI drops a token in slot " << nextMove + 1 << ".\n";
	}
	//add the player's specified move to the gameBoard, checking each space
	//within the column from the top down. 
	for (int i = 0; i < BoardHeight; i++) {
		if (i == BoardHeight - 1 || gameBoard[i + 1][nextMove] != Empty) {
			if (turnCounter % 2 != 0)
				gameBoard[i][nextMove] = Player1;
			else
				gameBoard[i][nextMove] = Player2;

			break;
		}
	}

	//after a play, check if there is a win state
	for (int i = 0; i < BoardHeight; i++) {
		for (int j = 0; j < BoardWidth; j++) {
			if (gameBoard[i][j] == Empty)
				continue;

			//vertical (downward from current) win
			if (i <= 2) {
				//for playerOne
				if (gameBoard[i][j] == Player1 && gameBoard[i + 1][j] == Player1
					&& gameBoard[i + 2][j] == Player1 && gameBoard[i + 3][j] == Player1)
					gameState = P1Won;
				//for playerTwo
				if (gameBoard[i][j] == Player2 && gameBoard[i + 1][j] == Player2
					&& gameBoard[i + 2][j] == Player2 && gameBoard[i + 3][j] == Player2)
					gameState = P2Won;
			}
			//diagonal (downward and rightward) win
			if (i <= 2 && j <= 3) {
				//for playerOne
				if (gameBoard[i][j] == Player1 && gameBoard[i + 1][j + 1] == Player1
					&& gameBoard[i + 2][j + 2] == Player1 && gameBoard[i + 3][j + 3] == Player1)
					gameState = P1Won;
				//for playerTwo
				if (gameBoard[i][j] == Player2 && gameBoard[i + 1][j + 1] == Player2
					&& gameBoard[i + 2][j + 2] == Player2 && gameBoard[i + 3][j + 3] == Player2)
					gameState = P2Won;
			}
			//diagonal (downward and leftward) win
			if (i <= 2 && j >= 3) {
				//for playerOne
				if (gameBoard[i][j] == Player1 && gameBoard[i + 1][j - 1] == Player1
					&& gameBoard[i + 2][j - 2] == Player1 && gameBoard[i + 3][j - 3] == Player1)
					gameState = P1Won;
				//for playerTwo
				if (gameBoard[i][j] == Player2 && gameBoard[i + 1][j - 1] == Player2
					&& gameBoard[i + 2][j - 2] == Player2 && gameBoard[i + 3][j - 3] == Player2)
					gameState = P2Won;
			}
			//horizontal (rightward) win
			if (j <= 3) {
				//for playerOne
				if (gameBoard[i][j] == Player1 && gameBoard[i][j + 1] == Player1
					&& gameBoard[i][j + 2] == Player1 && gameBoard[i][j + 3] == Player1)
					gameState = P1Won;
				//for playerTwo
				if (gameBoard[i][j] == Player2 && gameBoard[i][j + 1] == Player2
					&& gameBoard[i][j + 2] == Player2 && gameBoard[i][j + 3] == Player2)
					gameState = P2Won;
			}
		}
	}
	//if gameState is not a win or draw, change from one turn to the other
	if (!(gameState == P1Won || gameState == P2Won || gameState == Draw)) {
		if (gameState == TurnP1)
			gameState = TurnP2;
		else
			gameState = TurnP1;
	}
}