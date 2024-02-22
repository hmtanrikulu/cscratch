#include "Piece.h"

class Game {
	bool turn;
	bool finish;
	bool check;
	bool escape;
	LinkedList<LinkedList<Piece*>*> board;
public:
	bool isKingInCheck();
	void play();
	void print();
	bool moveResolvesTheCheck(int, int, int, int);
	void gameStatus();
	Game();
};