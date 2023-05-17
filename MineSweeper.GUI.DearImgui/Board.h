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
	Cell(ChessType type,Color _color) {
		this->chess = new Chess(type, _color);
		
	}
	~Cell() {

	}
	int getType() {
		return chess->Type;
	}
	int getColor() {
		return chess->color;
	}
	bool isEmpty;
	Chess* chess;
private:

};


class Board
{
public:
	Board();
	~Board() {

	}
	vector<pair<int, int>> getMoveablelist(int, int);
	Cell cell[BOARD_SIZE][BOARD_SIZE];

private:
	vector<Chess> w_chess;
	vector<Chess> b_chess;

	void Update();
	void ScanStraight(Chess);
	void ScanIncline(Chess);
	void ScanKnight(Chess);
	bool TestRange(int, int);

};

#endif // !BOARD_H