#pragma once
#include <vector>

enum ChessType
{
	Pawn, Knight, Bishop, Rook, Queen, King
};

//�W�¤U�� �դ���� Color=�e�i��V
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

	Chess();
	~Chess();


	void ClearMovelist();
	void AddMovelist(int, int);
	bool FindMovelist(int, int);

private:

};

