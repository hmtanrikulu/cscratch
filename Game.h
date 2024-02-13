#include "Piece.h"

class Game {
	bool turn;
	bool finish;
	LinkedList<LinkedList<Piece*>*> board;
public:
	void play();
	void checkTheKing();
	//void initilizeTheBoard();
	Game();
};