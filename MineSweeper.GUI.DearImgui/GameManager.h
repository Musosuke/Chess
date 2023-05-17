#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H



#include "Board.h"
#include "ViewManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	Board* board;

	int getTurn();
	int isOver();
	int showWinner();
	void start();
	void start(int);
	void UpdateFrame();

	vector<pair<int, int>> getMoveablelist(int y, int x);


private:
	ViewManager view;
	int turn;
	int winner;
	bool _over;
};


#endif // !GAMEMANAGER_H