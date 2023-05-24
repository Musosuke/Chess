#include "Board.h"

vector<pair<int, int>> Board::getMoveablelist(int y, int x) {
	return *cell[y][x].chess->Movelist;
}



void Board::Update() {
	for (int i = 0; i < w_chess.size(); i++)
	{
		w_chess[i]->ClearMovelist();
		ScanStraight(w_chess[i]);
		ScanIncline(w_chess[i]);
		ScanKnight(w_chess[i]);
		//ScanEnPassant(w_chess[i]);
	}
	for (int i = 0; i < b_chess.size(); i++)
	{
		b_chess[i]->ClearMovelist();
		ScanStraight(b_chess[i]);
		ScanIncline(b_chess[i]);
		ScanKnight(b_chess[i]);
		//ScanEnPassant(b_chess[i]);
	}
}

void Board::ScanStraight(Chess* c) {
	if (c->Type == Pawn || c->Type == Rook || c->Type == Queen || c->Type == King) {
		switch (c->Type) {
		case Pawn: {
			//Pawn eat chess, too lazy to write another function.
			for (int i = -1; i < 2; i += 2) {
				if (TestRange(c->position.first + c->color, c->position.second + i)) {
					if (cell[c->position.first + c->color][c->position.second + i].getColor() == -c->color) {
						c->AddMovelist(c->position.first + c->color, c->position.second + i);
					}
				}
			}
			//Pawn move
			for (int shift = 1; shift <= 2; shift++) {
				if (TestRange(c->position.first + c->color * shift, c->position.second))
				{
					if (cell[c->position.first + c->color * shift][c->position.second].isEmpty)
						c->AddMovelist(c->position.first + c->color * shift, c->position.second);
					else
						break;
				}
				if (!c->firstMove)
					break;
			}
			break; }
		case King: {
			for (int dir = -1; dir < 2; dir += 2) {
				if (TestRange(c->position.first + c->color * dir, c->position.second))
				{
					if (cell[c->position.first + c->color * dir][c->position.second].isEmpty || cell[c->position.first + c->color * dir][c->position.second].getColor() == -c->color)
						c->AddMovelist(c->position.first + c->color * dir, c->position.second);
				}
				if (TestRange(c->position.first, c->position.second + c->color * dir))
				{
					if (cell[c->position.first][c->position.second + c->color * dir].isEmpty || cell[c->position.first][c->position.second + c->color * dir].getColor() == -c->color)
						c->AddMovelist(c->position.first, c->position.second + c->color * dir);
				}
			}
			break; }
		default: {
			//forward/backward dir
			for (int dir = -1; dir < 2; dir += 2) {
				//Y dir
				for (int shift = 1; shift < 8; shift++) {
					int y = c->position.first + c->color * dir * shift;
					int x = c->position.second;
					if (TestRange(y, x))
					{
						if (cell[y][x].getColor() == c->color) {
							break;
						}
						c->AddMovelist(y, x);
						if (!cell[y][x].isEmpty) {
							break;
						}
					}
					else
						break;
				}
				//X dir
				for (int shift = 1; shift < 8; shift++) {
					int y = c->position.first;
					int x = c->position.second + c->color * dir * shift;
					if (TestRange(y, x))
					{
						if (cell[y][x].getColor() == c->color) {
							break;
						}
						c->AddMovelist(y, x);
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

void Board::ScanIncline(Chess* c) {
	if (c->Type == Queen || c->Type == Bishop) {
		/*
		*   y,x
			+0+0 ~+7+7
			+0-0 ~+7-7
			-0+0 ~-7+7
			-0-0 ~-7-7
		*/
		for (int i = 1; i <= 7; ++i)
		{
			int y = c->position.first + i;
			int x = c->position.second + i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 7; ++i)
		{
			int y = c->position.first + i;
			int x = c->position.second - i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 7; ++i)
		{
			int y = c->position.first - i;
			int x = c->position.second + i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 7; ++i)
		{
			int y = c->position.first - i;
			int x = c->position.second - i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}

	}
	else if (c->Type == King) {
		for (int i = 1; i <= 1; ++i)
		{
			int y = c->position.first + i;
			int x = c->position.second + i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 1; ++i)
		{
			int y = c->position.first + i;
			int x = c->position.second - i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 1; ++i)
		{
			int y = c->position.first - i;
			int x = c->position.second + i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
				if (!cell[y][x].isEmpty) {
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i <= 1; ++i)
		{
			int y = c->position.first - i;
			int x = c->position.second - i;
			if (TestRange(y, x))
			{
				if (cell[y][x].getColor() == c->color) {
					break;
				}
				c->AddMovelist(y, x);
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

void Board::ScanKnight(Chess* c) {
	if (c->Type == Knight) {
		int y = c->position.first;
		int x = c->position.second;
		if (TestRange(y + 2, x + 1)) {
			if (cell[y + 2][x + 1].isEmpty || cell[y + 2][x + 1].getColor() == -c->color)
				c->AddMovelist(y + 2, x + 1);
		}

		if (TestRange(y + 2, x - 1)) {
			if (cell[y + 2][x - 1].isEmpty || cell[y + 2][x - 1].getColor() == -c->color)
				c->AddMovelist(y + 2, x - 1);
		}
		if (TestRange(y - 2, x + 1)) {
			if (cell[y - 2][x + 1].isEmpty || cell[y - 2][x + 1].getColor() == -c->color)
				c->AddMovelist(y - 2, x + 1);
		}
		if (TestRange(y - 2, x - 1)) {
			if (cell[y - 2][x - 1].isEmpty || cell[y - 2][x - 1].getColor() == -c->color)
				c->AddMovelist(y - 2, x - 1);
		}
		if (TestRange(y + 1, x + 2)) {
			if (cell[y + 1][x + 2].isEmpty || cell[y + 1][x + 2].getColor() == -c->color)
				c->AddMovelist(y + 1, x + 2);
		}
		if (TestRange(y + 1, x - 2)) {
			if (cell[y + 1][x - 2].isEmpty || cell[y + 1][x - 2].getColor() == -c->color)
				c->AddMovelist(y + 1, x - 2);
		}
		if (TestRange(y - 1, x + 2)) {
			if (cell[y - 1][x + 2].isEmpty || cell[y - 1][x + 2].getColor() == -c->color)
				c->AddMovelist(y - 1, x + 2);
		}
		if (TestRange(y - 1, x - 2)) {
			if (cell[y - 1][x - 2].isEmpty || cell[y - 1][x - 2].getColor() == -c->color)
				c->AddMovelist(y - 1, x - 2);
		}

	}
	else
		return;

}

void Board::ScanEnPassant(Chess* c) {

	if (c->Type == ChessType::Pawn) {
		if (TestRange(c->position.first, c->position.second - 1) && TestRange(c->position.first, c->position.second + 1)) {
			Cell leftChess = cell[c->position.first][c->position.second - 1];
			Cell rightChess = cell[c->position.first][c->position.second + 1];

			if (!leftChess.isEmpty &&
				leftChess.getColor() != c->color)
			{
				int lefty = c->position.first;
				int leftx = c->position.second - 1;
				c->AddMovelist(lefty, leftx);
			}
			if (!rightChess.isEmpty &&
				rightChess.getColor() != c->color)
			{
				int righty = c->position.first;
				int rightx = c->position.second + 1;
				c->AddMovelist(righty, rightx);
			}
		}
	}
}


bool Board::TestRange(int y, int x) {
	return (y < 8 && y >= 0 && x < 8 && x >= 0);
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
	promotion = false;
	chessPro = NULL;

	playerColor = Color::Black;
	cell[0][0] = Cell(ChessType::Rook, playerColor, make_pair(0, 0));
	cell[0][1] = Cell(ChessType::Knight, playerColor, make_pair(0, 1));
	cell[0][2] = Cell(ChessType::Bishop, playerColor, make_pair(0, 2));
	cell[0][3] = Cell(ChessType::Queen, playerColor, make_pair(0, 3));
	cell[0][4] = Cell(ChessType::King, playerColor, make_pair(0, 4));
	cell[0][5] = Cell(ChessType::Bishop, playerColor, make_pair(0, 5));
	cell[0][6] = Cell(ChessType::Knight, playerColor, make_pair(0, 6));
	cell[0][7] = Cell(ChessType::Rook, playerColor, make_pair(0, 7));

	for (int i = 0; i < 8; ++i) {
		cell[1][i] = Cell(ChessType::Pawn, Color::Black, make_pair(1, i));
	}

	for (int i = 0; i < 8; ++i) {
		cell[6][i] = Cell(ChessType::Pawn, Color::White, make_pair(6, i));
	}

	playerColor = Color::White;
	cell[7][0] = Cell(ChessType::Rook, playerColor, make_pair(7, 0));
	cell[7][1] = Cell(ChessType::Knight, playerColor, make_pair(7, 1));
	cell[7][2] = Cell(ChessType::Bishop, playerColor, make_pair(7, 2));
	cell[7][3] = Cell(ChessType::King, playerColor, make_pair(7, 3));
	cell[7][4] = Cell(ChessType::Queen, playerColor, make_pair(7, 4));
	cell[7][5] = Cell(ChessType::Bishop, playerColor, make_pair(7, 5));
	cell[7][6] = Cell(ChessType::Knight, playerColor, make_pair(7, 6));
	cell[7][7] = Cell(ChessType::Rook, playerColor, make_pair(7, 7));

	for (int i = 0; i < 8; i++) {
		b_chess.push_back(cell[0][i].chess);
		b_chess.push_back(cell[1][i].chess);
		w_chess.push_back(cell[6][i].chess);
		w_chess.push_back(cell[7][i].chess);
	}

	Update();
}


void Board::MoveChess(int y1, int x1, int y2, int x2) {
	if (cell[y1][x1].isEmpty) {
		return;
	}
	auto moveableList = this->getMoveablelist(y1, x1);
	if (cell[y1][x1].chess->FindMovelist(y2, x2)) {
		//if y2x2 is moveable, and is a chess, need to remove this chess from Chess list
		if (!cell[y2][x2].isEmpty) {
			int colorofy2x2 = cell[y2][x2].getColor();

			if (colorofy2x2 == Color::Black) {
				//find chess and erase
				for (int i = 0; i < b_chess.size(); ++i) {
					if (b_chess[i]->position.first == y2 && b_chess[i]->position.second == x2) {
						b_chess.erase(b_chess.begin() + i);
						break;
					}
				}
			}
			else if (colorofy2x2 == Color::White) {
				//find chess and erase
				for (int i = 0; i < w_chess.size(); ++i) {
					if (w_chess[i]->position.first == y2 && w_chess[i]->position.second == x2) {
						w_chess.erase(w_chess.begin() + i);
						break;
					}
				}
			}
		}

		//if need to append lost chess to some list, do it here
		cell[y2][x2].chess = cell[y1][x1].chess;//this pos was replaced as the chess
		cell[y2][x2].isEmpty = false;
		cell[y2][x2].chess->firstMove = false;
		cell[y2][x2].chess->position = make_pair(y2, x2);

		cell[y1][x1] = Cell();//clear this cell into empty,without rule checking?



		////enpassant and move forward
		////if the chess is pawn, and move to left or right, then put pawn forward once if in range.
		//if (cell[x2][y2].getType() == ChessType::Pawn) {
		//	int movey = y2-y1;
		//	int movex = x2-x1;
		//	//if pawn go left or right
		//	if (movey == 0 && (movex == 1 || movex == -1)) {
		//		int theMovedChessColor = cell[y2][x2].getColor();
		//		if (TestRange(y2 + theMovedChessColor, x2)) {
		//			cell[y2 + theMovedChessColor][x2].chess = cell[y2][x2].chess;
		//			cell[y2][x2] = Cell();
		//		}
		//	}
		//}


		//do promotion
		//changes type to Rook, Knight, Bishop, or Queen
		if (cell[y2][x2].getType() == ChessType::Pawn) {
			if (cell[y2][x2].getColor() == Color::Black && y2 == 7) {
				promotion = true;
				chessPro = cell[y2][x2].chess;
			}
			else if (cell[y2][x2].getColor() == Color::White && y2 == 0) {
				promotion = true;
				chessPro = cell[y2][x2].chess;
			}
		}
	}
	else {
		return;
	}

}

void Board::PromoType(int t) {
	chessPro->Type = t;
	promotion = false;
}