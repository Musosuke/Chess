#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H



#include "Board.h"
#include "ViewManager.h"
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	Board* board;
	bool isSelecting;

	int getTurn();
	int isOver();
	int showWinner();
	void start();
	void start(int);
	void UpdateFrame();
	bool click(int, int);
	void nextTurn();
	int gameover(int);
	bool isPromotion();
	void selectedType(int);

	vector<pair<int, int>> getMoveablelist(int y, int x);
	bool isMoveable(int y, int x);


private:
	ViewManager view;
	int turn;
	int winner;
	bool _over;
	bool promotion;

	int selected_X, selected_Y;

	Player player1;
	Player player2;
};


#endif // !GAMEMANAGER_H