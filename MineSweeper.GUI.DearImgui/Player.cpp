#pragma once
#include "Player.h"



Player::Player(int _countdown_time, Color _playerColor) {
	this->playerColor = _playerColor;
	this->countdown_time = _countdown_time;
	this->start_time = 0;
}

void Player::OneRoundPassed() {
	countdown_time -= 5;
}