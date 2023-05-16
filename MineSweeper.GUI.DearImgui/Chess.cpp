#include "Chess.h"

void Chess::ClearMovelist() {
	Movelist->clear();
}

void Chess::AddMovelist(int y, int x) {
	Movelist->push_back(make_pair(y, x));
}

bool Chess::FindMovelist(int, int) {

}

