#pragma once
#include "Board.h"

class GameManeger
{
public:
	GameManeger();
	~GameManeger();
	vector<pair<int, int>> getMoveablelist(int y, int x);
private:
	Board* board;
};

GameManeger::GameManeger()
{
}

GameManeger::~GameManeger()
{
}