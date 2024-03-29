#include "Piece.h"

// This part belongs to base class Piece

Piece::Piece(int r, int c, bool isW, string n) {
	this->row = r;
	this->col = c;
	this->isWhite = isW;
	this->name = n;
	this->moveSet;
}

bool Piece::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) return true;
	else return false;
	return true;
}

bool Piece::isInMoveSet(int r2, int c2) { // flag
	int r1 = this->row, c1 = this->col;	
	Move m(this->isWhite ? (r1 - r2) : (r2 - r1), (c2 - c1));
	for (int i = 0; i < this->moveSet.length; i++) {
	if (this->moveSet[i] == m) return true;
	}	
	return false;
}

bool Piece::isInBoard(int r2, int c2) {
	int r1 = this->row, c1 = this->col;
	if (r2 > 7 || r2 < 0) return false;
	if (c2 > 7 || c2 < 0) return false;
	return true;
}


bool Piece::isInterrupted(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	int r1 = this->row, c1 = this->col;
	string move = "cross";
	if (r1 == r2) move = "lateral";
	if (c1 == c2) move = "vertical";


	// mevzu
	if ( ((*board[r2])[c2] != nullptr) && ((*board[r2])[c2]->isWhite == this->isWhite)) return true;

	else {
		if (move == "cross") {
			bool signR = r2 - r1 > 0;
			bool signC = c2 - c1 > 0;
			int steps = abs(r2 - r1);
			for (int step = 1; step < steps; step++) {
				int tmpR = r1 + (signR ? step : -step);
				int tmpC = c1 + (signC ? step : -step);
				if ((*board[tmpR])[tmpC] != nullptr) return true;
			}
		}
		else if (move == "lateral") {
			bool sign = c2 - c1 > 0;
			for (int i = 1; i < abs(c2 - c1); i++) { 
				int tmpC = c1 + (sign ? i : -i);
				if ((*board[r1])[tmpC] != nullptr) return true;
			}
		}
		else if (move == "vertical") {
			bool sign = r2 - r1 > 0;
			for (int i = 1; i < abs(r2 - r1); i++) { 
				int tmpR = r1 + (sign ? i : -i);
				if ((*board[tmpR])[c1] != nullptr) return true;
			}
		}
		return false; 
	}
}



// This part belongs to child class King
King::King(int row, int col, bool isWhite, const string& name = "King")
	: Piece(row, col, isWhite, name) {
	LinkedList<Move> moves;
	moves.insert(Move(0, 1));
	moves.insert(Move(0, -1));
	moves.insert(Move(1, 0));
	moves.insert(Move(-1, 0));
	moves.insert(Move(1, 1));
	moves.insert(Move(1, -1));
	moves.insert(Move(-1, -1));
	moves.insert(Move(-1, 1));
	this->moveSet = moves;
	this->isMoved = false;
}

bool King::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board) && !isDumbMove(r2, c2, board)) {
		return true;
	}
	else if (isInBoard(r2, c2) && (!isInterrupted(r2, c2, board)) && (!isRookMoved(r2, c2, board)) && (isCastle(r2, c2)))return true;
	else {
		return false;
	}
	cout << "king's moveCheck"; 
	return true;
}

bool King::isDumbMove(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	Piece* tmp;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			tmp = (*board[i])[j];
			int iterator = 0;
			if ((tmp != this) && (tmp != nullptr) && (tmp->isWhite != this->isWhite)) {
				while (iterator < tmp->moveSet.length) {
					int tmpR, tmpC;
					tmpR = tmp->row + tmp->moveSet[iterator].upDown;
					tmpC = tmp->col + tmp->moveSet[iterator].leftRight;
					if ((tmpR == r2) && (tmpC == c2)) {
						//
						return true;
					}
					iterator++;
				}
			}
		}
	}
	return false;
}


bool King::isRookMoved(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	if ((r2 == 0 && (c2 == 1 || c2 == 6)) || r2 == 7 && (c2 == 1 || c2 == 6)) {
		if ((*board[0])[0] != nullptr) { // sol alt
			try {
				Rook* rook = (Rook*)(*board[0])[0];
				if (!rook->isMoved) return false;
			}
			// Catch part here, handles the nullptr possibility.
			catch (exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	else if (r2 == 0 && c2 == 6) {
		if ((*board[0])[7] != nullptr) {
			try {
				Rook* rook = (Rook*)(*board[0])[7];
				if (!rook->isMoved) return false;
			}
			catch (exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	else if (r2 == 7 && c2 == 1) {
		if ((*board[7])[0] != nullptr) {
			try {
				Rook* rook = (Rook*)(*board[7])[0];
				if (!rook->isMoved) return false;
			}
			catch (exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	else if (r2 == 7 && c2 == 6) {
		if ((*board[7])[7] != nullptr) {
			try {
				Rook* rook = (Rook*)(*board[7])[7];
				if (!rook->isMoved) return false;
			}
			catch (exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	return true;
}

bool King::isCastle(int r2, int c2) {
	if (this->isMoved == true) return false;
	else if ((r2 == 0 && (c2 == 1 || c2 == 6)) || (r2 == 7 && (c2 == 1 || c2 == 6))) return true;
	else return false;
}

// This part belongs to child class Rook
Rook::Rook(int row, int col, bool isWhite, const string& name = "Rook")
	: Piece(row, col, isWhite, name) {LinkedList<Move> moves;
	for (int i = -7; i < 8; i++) {
		if (i != 0) {
		moves.insert(Move(i, 0));
		moves.insert(Move(0, i));
		}
	}
	this->moveSet = moves;
	this->isMoved = false;
}

bool Rook::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) {
		return true;
	}
	else {
		return false;
	}
	cout << "Rook's moveCheck";
	return true;
}

// This part belongs to child class Knight
bool Knight::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2)) {
		if ((*board[r2])[c2] != nullptr && this->isWhite == (*board[r2])[c2]->isWhite)
			return false;
		else 
		return true;
	}
	else
		return false;
}

Knight::Knight(int row, int col, bool isWhite, const string& name = "Knight")
	: Piece(row, col, isWhite, name) {
	LinkedList<Move> moves;
	moves.insert(Move(2, 1));
	moves.insert(Move(1, 2));
	moves.insert(Move(-1, 2));
	moves.insert(Move(-2, 1));
	moves.insert(Move(-2, -1));
	moves.insert(Move(-1, -2));
	moves.insert(Move(1, -2));
	moves.insert(Move(2, -1));
	this->moveSet = moves;
}

// This part belongs to child class Bishop
Bishop::Bishop(int row, int col, bool isWhite, const string& name = "Bishop")
	: Piece(row, col, isWhite, name) {
	LinkedList<Move> moves;
	for (int i = -8; i < 8; i++) {
		if (i != 0) {
			int j = i;
			moves.insert(Move(i, j));
		}

	}
	for (int m = -8; m < 8; m++) {
		if (m != 0) {
			int n = m * -1;
			moves.insert(Move(m, n));
		}
	}
	this->moveSet = moves;
}

bool Bishop::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

// This part belongs to Queen

Queen::Queen(int row, int col, bool isWhite, const string& name = "Queen")
	: Piece(row, col, isWhite, name) {
	LinkedList<Move> moves;
	for (int i = -7; i < 8; i++) {
		if (i != 0) {
			moves.insert(Move(i, 0));
			moves.insert(Move(0, i));
		}
	}
	for (int i = -7; i < 8; i++) {
		if (i != 0) {
			int j = i;
			moves.insert(Move(i, j));
		}
	}
	for (int m = -7; m < 8; m++) {
		if (m != 0) {
			int n = m * -1;
			moves.insert(Move(m, n));
		}
	}
	this->moveSet = moves;
}

bool Queen::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

// This part belongs to child class Pawn

Pawn::Pawn(int row, int col, bool isWhite, const string& name = "Pawn")
	: Piece(row, col, isWhite, name) {
	LinkedList<Move> moves;
	moves.insert(Move(1, 0));
	this->isMoved = false;
	this->moveSet = moves;
}

bool Pawn::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*>& board) {
	int r1 = this->row, c1 = this->col;
	if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) return true;
	else if (crossMove(r2, c2, board) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) return true;
	else if (enPassant(r2, c2, board) && isInBoard(r2, c2) && !isInterrupted(r2, c2, board)) return true;
	else {
		return false;
	}
}

bool Pawn::isInterrupted(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	int r1 = this->row, c1 = this->col;
	if (c2 == c1) {
		if ((*board[r2])[c2] != nullptr) return true;
	}
	return false;
}

bool Pawn::crossMove(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	int r1 = this->row, c1 = this->col;
	if ((r2 - r1 != 1 && this->isWhite) || (r2 - r1 != -1 && !this->isWhite)) return false;
	if (abs(c2 - c1) != 1) return false;
	if ((*board[r2])[c2] == nullptr) return false;
	if ((*board[r2])[c2]->isWhite == this->isWhite) return false;
	return true;
}

bool Pawn::enPassant(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	int r1 = this->row, c1 = this->col;
	if (((r2 - r1 == 2) || (r2 - r1 == -2)) && (c2 == c1) && ((*board[r2])[c2] == nullptr)) {
		return true;
	}
	return false;
}

void Pawn::convert(int r2, int c2, LinkedList <LinkedList <Piece*>*> board) {
	string convertTo;
	if (((this->isWhite == 1) && (r2 == 7)) || ((this->isWhite == 0) && (r2 == 0))) {
		cout << "Type A The Piece You'd Like To Convert Your Pawn To";
		cin >> convertTo;
		bool tmp = this->isWhite;
		delete this;
		(*board[r2])[c2] = nullptr;
		if (convertTo == "Queen") {
			(*board[r2])[c2] = new Queen(r2, c2, tmp, "Queen");
		}
		else if (convertTo == "Rook") {
			(*board[r2])[c2] = new Rook(r2, c2, tmp, "Rook");
		}
		else if (convertTo == "Knight") {
			(*board[r2])[c2] = new Knight(r2, c2, tmp, "Knight");
		}
		else if (convertTo == "Bishop") {
			(*board[r2])[c2] = new Bishop(r2, c2, tmp, "Bishop");
		}
	}
}
