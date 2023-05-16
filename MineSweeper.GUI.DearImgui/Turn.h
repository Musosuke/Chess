#pragma once
#include "Chess.h"

class Turn
{
public:
	Turn();
	~Turn();

	void Move(Chess, Chess);
private:
	Chess chessMoved;
	Chess chessKilled;


};

