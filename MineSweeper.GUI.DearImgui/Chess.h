﻿#pragma once
#include <vector>
#ifndef CHESS_H
#define CHESS_H




enum ChessType
{
	Pawn, Knight, Bishop, Rook, Queen, King
};

//上黑下白 白方先手 Color=前進方向
enum Color {
	Black = 1, White = -1
};

using namespace std;

class Chess
{
public:
	int color;
	int Type;
	bool firstMove;
	pair<int, int> position;
	vector<pair<int, int>>* Movelist;

	Chess() {

	}
	Chess(ChessType type,Color _color) {
		firstMove = true;
		Type = static_cast<int>(type);
		color = static_cast<int>(_color);
		Movelist = new vector<pair<int, int>>();
	}
	~Chess() {

	}


	void ClearMovelist();
	void AddMovelist(int, int);
	bool FindMovelist(int, int);

private:

};
#endif // !CHESS_H
