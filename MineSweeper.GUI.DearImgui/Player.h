#pragma once
#include <chrono>
#include "Chess.h"

class Player {

public:
	Player();
	Player(int _countdown_time, Color _playerColor);

	void OneRoundPassed();
private:
	Color playerColor;
	int start_time;
	int countdown_time;
};