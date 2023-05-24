#include "GameManager.h"

GameManager::GameManager()
{
	start();
	player1 = Player(2400, Color::White);
	player2 = Player(2400, Color::Black);
	turn = 0;
	_over = false;
	isSelecting = false;
	winner = -1;
	selected_X = 9;
	selected_Y = 9;
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

void GameManager::UpdateFrame() {
	view.Update();
}

bool GameManager::click(int y, int x) {

	//when selecting, select the target cell that the chess should move to.
	//if target cell is not moveable or moved, cancel selecting
	if (isSelecting) {
		// when selecting, click cells that moveable can move chess, click other cell will stop selecting.
		bool found = isMoveable(y, x);
		if (found) {
			board->MoveChess(selected_Y, selected_X, y, x);
			if (board->promotion) {

			}
			board->Update();
			nextTurn();
		}
		selected_X = 9;
		selected_Y = 9;
		isSelecting = false;
	}
	//when not selecting, select the target chess to move
	else {
		//don't select empty cell, there is not chess
		if (board->cell[y][x].isEmpty) {
			isSelecting = false;
			return isSelecting;
		}

		//only select chesses that conform with turn
		if (board->cell[y][x].getColor() == turn) {
			selected_Y = y;
			selected_X = x;
			isSelecting = true;
		}

	}
	return isSelecting;
}

void GameManager::nextTurn() {
	if (_over) return;
	turn = -turn;
}

int GameManager::gameover(int p) {
	if (_over) return winner;
	winner = p;
	_over = true;
	return winner;
}

vector<pair<int, int>> GameManager::getMoveablelist(int y, int x) {
	return board->getMoveablelist(y, x);
}

bool GameManager::isMoveable(int y, int x) {
	if (selected_Y > 7 || selected_X > 7) {
		return false;
	}
	//vector<pair<int, int>> list = getMoveablelist(selected_Y, selected_X);
	vector<pair<int, int>> list = board->getMoveablelist(selected_Y, selected_X);
	bool found = false;
	for (int i = 0; i < list.size(); i++) {
		if (y == list[i].first && x == list[i].second) {
			found = true;
			break;
		}
	}
	return found;
}

bool GameManager::isPromotion() {
	return board->promotion;
}
void GameManager::selectedType(int t) {
	board->PromoType(t);
}