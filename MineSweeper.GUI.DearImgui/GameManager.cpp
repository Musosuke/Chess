#include "GameManager.h"

GameManager::GameManager()
{
	start();
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

void GameManager::UpdateFrame() {
	view.Update();
}

vector<pair<int, int>> GameManager::getMoveablelist(int y, int x) {
	return board->getMoveablelist(y, x);
}