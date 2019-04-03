#ifndef PLAYERS_H
#include "players.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <time.h>


int HumanPlayer::getNextTurn(Game g) {
	int nextPlay;
	std::cout << "In which row will you drop your token?\n";
	std::cin >> nextPlay;
	return nextPlay - 1;
}

//bool returns true if player is human, false if ai
bool HumanPlayer::getPlayerType(Game g) {
	return true;
}

int AiPlayer::getNextTurn(Game g) {
	static int srand(time(NULL));
	int nextPlay = (rand() % 7);
	return nextPlay;
}

//bool returns true if player is human, false if ai
bool AiPlayer::getPlayerType(Game g) {
	return false;
}