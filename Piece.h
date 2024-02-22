#include "LinkedList.h"
#ifndef PIECE_H
#define PIECE_H



struct Move {
public:
	int upDown, leftRight;
	// We use this operator to compare the moves inside piece's isInMoveSet
	bool operator == (Move m) {
		return this->upDown == m.upDown && this->leftRight == m.leftRight; // error occurs here
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

	virtual bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&);

	// Conditions for moveCheck
	bool isInMoveSet(int, int);
	bool isInBoard(int, int);
	virtual bool isInterrupted(int, int, LinkedList<LinkedList<Piece*>*>);
};



class King : public Piece {
public:
	bool isMoved;
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
	bool isCastle(int, int);
	bool isRookMoved(int, int, LinkedList<LinkedList<Piece*>*>);
	bool isDumbMove(int, int, LinkedList<LinkedList<Piece*>*>);
	King(int, int, bool, const string&);
};

class Rook : public Piece {
public:
	bool isMoved;
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
	Rook(int, int, bool, const string&);
};

class Knight :public Piece {
public:
	Knight(int, int, bool, const string&);
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
};

class Bishop :public Piece {
public:
	Bishop(int, int, bool, const string&);
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
};

class Queen :public Piece {
public:
	Queen(int, int, bool, const string&);
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
};

class Pawn :public Piece {
public:
	bool isMoved;
	Pawn(int, int, bool, const string&);
	bool moveCheck(int, int, LinkedList<LinkedList<Piece*>*>&) override;
	bool isInterrupted(int, int, LinkedList<LinkedList<Piece*>*>);
	bool crossMove(int, int, LinkedList<LinkedList<Piece*>*>);
	void convert(int, int, LinkedList<LinkedList<Piece*>*>);
	bool enPassant(int, int, LinkedList<LinkedList<Piece*>*>);
};
#endif