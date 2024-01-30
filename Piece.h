#include "LinkedList.h"
#ifndef PIECE_H
#define PIECE_H



struct Move {
	int upDown, leftRight;
	bool operator == (int x[2]) {
		return this->upDown == x[0] && this->leftRight == x[1]; // error occurs here
	}
	Move(int x, int y) {
		this->upDown = x;
		this->leftRight = y;
	}
};

class Piece {
public:
	string name;
	int row, col;
	bool isWhite;
	LinkedList<Move>moveSet;
	Piece(int, int, bool, string);

	// string& n try that in order to obeserve the flow of inheritance
	virtual bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>);

	// Conditions for moveCheck
	bool isInMoveSet(int, int);
	bool isInBoard(int, int);
	virtual bool isInterrupted(int, int, LinkedList<LinkedList<Piece*>*>);
};



class King : public Piece {
public:
	King(int, int, bool, const string&);
	//bool isCastle(int, int);
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>) override;
	//bool isRookMoved(int, int, LinkedList<LinkedList<Piece*>*>);
	//bool dumbMove(int, int, LinkedList<LinkedList<Piece*>*>);
};

//class Rook : public Piece {
//public:
//	bool isMoved;
//	Rook(int, int, bool, const string&);
//};
#endif