#pragma once
#include <iostream>
#include "Chess.h"
#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8

class Cell
{
public:
	Cell() {

	}
	~Cell() {

	}
	bool isEmpty;
	Chess* chess;
private:

};


class Board
{
public:
	Board() {

	}
	~Board() {

	}
	vector<pair<int, int>> getMoveablelist(int, int);

private:
	vector<Chess> w_chess;
	vector<Chess> b_chess;
	Cell cell[BOARD_SIZE][BOARD_SIZE];

	void Update();
	void ScanStraight(Chess);
	void ScanIncline(Chess);
	void ScanKnight(Chess);
	bool TestRange(int, int);
};

#endif // !BOARD_H