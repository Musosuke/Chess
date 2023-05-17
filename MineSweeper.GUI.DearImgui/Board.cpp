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
		/*
		*   y,x
			+0+0 ~+7+7
			+0-0 ~+7-7
			-0+0 ~-7+7
			-0-0 ~-7-7
		*/
		for (int i = 0; i <= 7; ++i)
		{
			int y = c.position.first + i;
			int x = c.position.second + i;
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
		for (int i = 0; i <= 7; ++i)
		{
			int y = c.position.first + i;
			int x = c.position.second - i;
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
		for (int i = 0; i <= 7; ++i)
		{
			int y = c.position.first - i;
			int x = c.position.second + i;
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
		for (int i = 0; i <= 7; ++i)
		{
			int y = c.position.first - i;
			int x = c.position.second - i;
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
	else
		return;
}

void Board::ScanKnight(Chess c) {
	if (c.Type == Knight) {
		int y = c.position.first;
		int x = c.position.second;
		if (TestRange(y + 2, x + 1))
			c.AddMovelist(y + 2, x + 1);

		if (TestRange(y + 2, x - 1))
			c.AddMovelist(y + 2, x - 1);

		if (TestRange(y - 2, x + 1))
			c.AddMovelist(y - 2, x + 1);

		if (TestRange(y - 2, x - 1))
			c.AddMovelist(y - 2, x - 1);

		if (TestRange(y + 1, x + 2))
			c.AddMovelist(y + 1, x + 2);

		if (TestRange(y + 1, x - 2))
			c.AddMovelist(y + 1, x - 2);

		if (TestRange(y - 1, x + 2))
			c.AddMovelist(y - 1, x + 2);

		if (TestRange(y - 1, x - 2))
			c.AddMovelist(y - 1, x - 2);

	}
	else
		return;

}

bool Board::TestRange(int y, int x) {
	return (y < 8 && y >= 0 && x <= 8 && x >= 0);
}


Board::Board()
{
	/*
		cell
			00 07
			10 17 V

			60 67 V
			70 77
	*/
	Color playerColor;


	playerColor = Color::Black;
	cell[0][0] = Cell(ChessType::Rook, playerColor);
	cell[0][1] = Cell(ChessType::Knight, playerColor);
	cell[0][2] = Cell(ChessType::Bishop, playerColor);
	cell[0][3] = Cell(ChessType::Queen, playerColor);
	cell[0][4] = Cell(ChessType::King, playerColor);
	cell[0][5] = Cell(ChessType::Bishop, playerColor);
	cell[0][6] = Cell(ChessType::Knight, playerColor);
	cell[0][7] = Cell(ChessType::Rook, playerColor);

	for (int i = 0; i < 8; ++i) {
		cell[1][i] = Cell(ChessType::Pawn, Color::Black);
	}

	for (int i = 0; i < 8; ++i) {
		cell[6][i] = Cell(ChessType::Pawn, Color::White);
	}

	playerColor = Color::White;
	cell[7][0] = Cell(ChessType::Rook, playerColor);
	cell[7][1] = Cell(ChessType::Knight, playerColor);
	cell[7][2] = Cell(ChessType::Bishop, playerColor);
	cell[7][3] = Cell(ChessType::King, playerColor);
	cell[7][4] = Cell(ChessType::Queen, playerColor);
	cell[7][5] = Cell(ChessType::Bishop, playerColor);
	cell[7][6] = Cell(ChessType::Knight, playerColor);
	cell[7][7] = Cell(ChessType::Rook, playerColor);

}