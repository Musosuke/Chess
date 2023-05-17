#include "Chess.h"

void Chess::ClearMovelist() {
	Movelist->clear();
}

void Chess::AddMovelist(int y, int x) {
	Movelist->push_back(make_pair(y, x));
}

bool Chess::FindMovelist(int y, int x) {
	//find da pair exist or not
	std::vector<std::pair<int, int>>::iterator it;
	for (it = Movelist->begin(); it != Movelist->end(); it++) {
		if (it->first == y && it->second == x)
			return true;
	}
	return false;
}

