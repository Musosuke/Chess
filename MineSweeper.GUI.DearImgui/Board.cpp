#include "Board.h"

vector<pair<int, int>> Board::getMoveablelist(int y, int x) {
	return *cell[y][x].chess->Movelist;
}

void Board::Update() {
	for (int i = 0; i < w_chess.size(); i++)
	{
		ScanStraight(w_chess[i]);
		ScanIncline(w_chess[i]);
		ScanKnight(w_chess[i]);
	}
}

void Board::ScanStraight(Chess c) {
	if (c.Type == Pawn || c.Type == Rook || c.Type == Queen || c.Type == King) {
		switch (c.Type) {
		case Pawn: {
			for (int shift = 1; shift <= 2; shift++) {
				if (TestRange(c.position.first + c.color * shift, c.position.second))
				{
					c.AddMovelist(c.position.first + c.color * shift, c.position.second);
				}
				if (!c.firstMove)
					break;
			}
			break; }
		case King: {
			for (int dir = -1; dir < 1; dir += 2) {
				if (TestRange(c.position.first + c.color * dir, c.position.second))
				{
					c.AddMovelist(c.position.first + c.color * dir, c.position.second);
				}
				if (TestRange(c.position.first, c.position.second + c.color * dir))
				{
					c.AddMovelist(c.position.first, c.position.second + c.color * dir);
				}
			}
			break; }
		default: {
			//forward/backward dir
			for (int dir = -1; dir < 1; dir += 2) {
				//Y dir
				for (int shift = 1; shift < 8; shift++) {
					int y = c.position.first + c.color * dir * shift;
					int x = c.position.second;
					if (TestRange(y, x))
					{
						c.AddMovelist(y, x);
						if (!cell[y][x].isEmpty) {
							break;
						}
					}
					else
						break;
				}
				//X dir
				for (int shift = 1; shift < 8; shift++) {
					int y = c.position.first;
					int x = c.position.second + c.color * dir * shift;
					if (TestRange(y, x))
					{
						c.AddMovelist(y, x);
						if (!cell[y][x].isEmpty) {
							break;
						}
					}
					else
						break;
				}
			}
			break; }
		}
	}
	else
		return;
}

void Board::ScanIncline(Chess c) {
	if (c.Type == Queen || c.Type == Bishop) {

	}
	else
		return;
}

void Board::ScanKnight(Chess c) {
	if (c.Type == Knight) {

	}
	else
		return;

}

bool Board::TestRange(int y, int x) {
	return (y < 8 && y >= 0 && x <= 8 && x >= 0);
}