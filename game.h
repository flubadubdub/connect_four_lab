#ifndef GAME_H
#define GAME_H

#ifndef PLAYERS_H
#include "players.h"
#endif

class Player;
enum BoardField { Empty, Player1, Player2 };
enum GameState { TurnP1, TurnP2, P1Won, P2Won, Draw };

class Game {
public:
	const int BoardWidth = 7;
	const int BoardHeight = 6;					//7 x 6 game board
	Game(Player&, Player&);						//constructor accepts references to 2 players
	BoardField operator()(int, int) const;		//overrides parentheses operator to return what is at a specified slot in the game board
	GameState getState();						//returns current GameState from enumerated list
	bool isRunning();							//returns true if no player has won or has forced a draw yet, false otherwise
	bool isValidMove(int);						//returns false if a player tries to make a move which does not follow the rules of the game, true otherwise
	void nextTurn();							//handles all logic concerning players' turns
	
private:
	Player* playerOne;							//pointer to first Player object
	Player* playerTwo;							//pointer to second Player object
	GameState gameState = TurnP1;				//initial gamestate is a turn for the first player
	BoardField** gameBoard;						//pointer to matrix which will serve as the gameboard
	int turnCounter = 0;						//tracks how many turns have passed in-game
};

#endif