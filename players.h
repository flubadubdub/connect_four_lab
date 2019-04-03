#ifndef PLAYERS_H
#define PLAYERS_H

#ifndef GAME_H
#include "game.h"
#endif

class Game;

class Player{
public:
	virtual int getNextTurn(Game) = 0;
	virtual bool getPlayerType(Game) = 0;
};

class HumanPlayer : public Player {
public:
	int getNextTurn(Game);
	bool getPlayerType(Game);
};

class AiPlayer : public Player {
public:
	int getNextTurn(Game);
	bool getPlayerType(Game);
};

#endif