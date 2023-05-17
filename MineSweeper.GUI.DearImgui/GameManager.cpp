#include "GameManager.h"

GameManager::GameManager()
{
	start();
	player1 = Player(2400, Color::White);
	player2 = Player(2400, Color::Black);
	turn = 0;
	_over = false;
	winner = -1;
	board = new Board();
}

GameManager::~GameManager()
{
}

int GameManager::getTurn() {
	return turn;
}
int GameManager::isOver() {
	return _over;
}

int GameManager::showWinner() {
	return winner;
}

void GameManager::start() {
	start(Color::White);
}

void GameManager::start(int n) {
	board = new Board();
	turn = n;
	_over = false;
}

vector<pair<int, int>> GameManager::getMoveablelist(int y, int x) {
	return board->getMoveablelist(y, x);
}