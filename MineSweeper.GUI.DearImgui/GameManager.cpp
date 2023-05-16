#include "GameManager.h"

vector<pair<int, int>> GameManeger::getMoveablelist(int y, int x) {
	return board->getMoveablelist(y, x);
}