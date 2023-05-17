#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H



#include "Board.h"
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	int getTurn();
	int isOver();
	int showWinner();
	void start();
	void start(int);


	vector<pair<int, int>> getMoveablelist(int y, int x);
private:
	Board* board;
	int turn;
	int winner;
	bool _over;

	Player player1;
	Player player2;
};


#endif // !GAMEMANAGER_H