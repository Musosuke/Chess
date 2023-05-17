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
		this->isEmpty = true;
	}
	Cell(ChessType type, Color _color) {
		this->chess = new Chess(type, _color);
		this->isEmpty = false;
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
	void Update();
	void MoveChess(int, int, int, int);
private:
	vector<Chess> w_chess;
	vector<Chess> b_chess;

	void ScanStraight(Chess);
	void ScanIncline(Chess);
	void ScanKnight(Chess);
	void ScanEnPassant(Chess);
	bool TestRange(int, int);


	void ScanCastle(Chess);
};

#endif // !BOARD_H