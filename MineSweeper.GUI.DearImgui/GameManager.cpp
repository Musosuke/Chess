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
	selected_X = 0;
	selected_Y = 0;
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
	if (board->cell[y][x].getColor() == turn) {
		// when selecting, click cells that moveable can move chess, click other cell will stop selecting.
		if (isSelecting) {
			bool found = isMoveable(y, x);
			if (found) {
				//Move(selected_y,selected_x,y,x);
			}
			isSelecting = false;
		}
		//when no selecting, click cells that is not Empty(has chess) can select the chess.
		else {
			if (!board->cell[y][x].isEmpty) {
				selected_Y = y;
				selected_X = x;
				isSelecting = true;
			}

		}
	}
	else {
		isSelecting = false;
	}
	return isSelecting;
}

vector<pair<int, int>> GameManager::getMoveablelist(int y, int x) {
	return board->getMoveablelist(y, x);
}

bool GameManager::isMoveable(int y, int x) {
	vector<pair<int, int>> list = getMoveablelist(selected_Y, selected_X);
	bool found = false;
	for (int i = 0; i < list.size(); i++) {
		if (y == list[i].first && x == list[i].second) {
			found = true;
			break;
		}
	}
	return found;
}