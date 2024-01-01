#include "Piece.h"

Piece::Piece(int r, int c, bool isW, string n) {
	this->row = r;
	this->col = c;
	this->isWhite = isW;
	this->name = n;
	this->moveSet;
}

bool Piece::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	cout << "Default moveCheck Error";
	return 0;
}

bool Piece::isInMoveSet(int r2, int c2) {
	int r1 = this->row, c1 = this->col;
	for (int i = 0; i < this->moveSet.length; i++) {
		int move[2] = { (r2 - r1), (c2 - c1) };
		if (this->moveSet[i] == move) return true;
	}
	return false;
}

// Conditions are written in error case
bool Piece::isInBoard(int r2, int c2) {
	int r1 = this->row, c1 = this->col;
	if (r1 + r2 > 7 || r1 + r2 < 0) return false;
	if (c1 + c2 > 7 || c1 + c2 < 0) return false;
	return true;
}

// Looks if r2-c2 is occupied or ally, if there any other piece on the way
bool Piece::isInterrupted(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	int r1 = this->row, c1 = this->col;
	string move = "cross";
	if (r1 == r2) move = "lateral";
	if (c1 == c2) move = "vertical";
	if (((*board[r2])[c2] != nullptr) && ((*board[r2])[c2]->isWhite == this->isWhite)) return false;
	if (move == "cross") {
		bool signR = r2 - r1 > 0 ? true : false;
		bool signC = c2 - c1 > 0 ? true : false;
		int tmpR = r1, tmpC = c1;
		if (signR && signC) {
			for (int i = 0; i < abs(r2 - r1) - 1; i++) {
				tmpR++;
				for (int j = 0; j < abs(c2 - c1) - 1; j++) {
					tmpC++;
					if ((*board[tmpR])[tmpC] != nullptr) return false;
				}
			}
		}
		else if (!signR && signC) {
			for (int i = 0; i < abs(r2 - r1) - 1; i++) {
				tmpR--;
				for (int j = 0; j < abs(c2 - c1 - 1); j++) {
					tmpC++;
					if ((*board[tmpR])[tmpC] != nullptr) return false;
				}
			}
		}
		else if (signR && !signC) {
			for (int i = 0; i < abs(r2 - r1) - 1; i++) {
				tmpR++;
				for (int j = 0; j < abs(c2 - c1) - 1; j++) {
					tmpC--;
					if ((*board[tmpR])[tmpC] != nullptr) return false;
				}
			}
		}
		else if (!signR && !signC) {
			for (int i = 0; i < abs(r2 - r1) - 1; i++) {
				tmpR--;
				for (int j = 0; j < abs(c2 - c1) - 1; j++) {
					tmpC--;
					if ((*board[tmpR])[tmpC] != nullptr) return false;
				}
			}
		}
		else if (move == "lateral") {
			bool sign = c2 - c1 > 0 ? true : false;
			int tmp = c1;
			if (sign) {
				for (int i = 0; i < abs(c2 - c1) - 1; i++) {
					tmp++;
					if ((*board[r1])[tmp] != nullptr) return false;
				}
			}
			else {
				for (int i = 0; i < abs(c2 - c1) - 1; i++) {
					tmp--;
					if ((*board[r1])[tmp] != nullptr) return false;
				}
			}
		}
		else if (move == "vertical") {
			int tmp = r1;
			bool sign = r2 - r1 > 0 ? true : false;
			if (sign) {
				for (int i = 0; i < abs(r2 - r1) - 1; i++) {
					tmp++;
					if ((*board[tmp])[c1] != nullptr) return false;
				}
			}
			else {
				for (int i = 0; i < abs(r2 - r1) - 1; i++) {
					tmp--;
					if ((*board[tmp])[c1] != nullptr) return false;
				}
			}
		}
		return true;
	}
	return true;
}

// Constructors
// Example Constructor 
// 
//King::King(int row, int col, bool isWhite, const string& name = "King")
//	: Piece(row, col, isWhite, name) {
//	// Initialize King-specific attributes or moveSet here
//}

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
}

//bool King::isCastle(int r2, int c2) {
//	if (this->isMoved == true) return false;
//	else if ((r2 == 0 && (c2 == 1 || c2 == 6)) || (r2 == 7 && (c2 == 1 || c2 == 6))) return true;
//	else return false;
//}

// condition dumbMove() missing
bool King::moveCheck(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
	cout << "king's moveCheck";
	//int r1 = this->row, c1 = this->col;
	//if (isInMoveSet(r2, c2) && isInBoard(r2, c2) && isInterrupted(r2, c2, board)) return true; //  && dumbMove(r2, c2, board)
	//else if (isInterrupted(r2, c2, board)) return true; //  && isRookMoved(r2, c2, board), isCastle(r2, c2) && 
	//else {
	//	return false;
	//}
	return true;
}

//bool King::isRookMoved(int r2, int c2, LinkedList<LinkedList<Piece*>*> board) {
//	if ((r2 == 0 && (c2 == 1 || c2 == 6)) || r2 == 7 && (c2 == 1 || c2 == 6)) {
//		if ((*board[0])[0] != nullptr) {
//			try {
//				Rook* rook = (Rook*)(*board[0])[0];
//				if (rook->isMoved) return false;
//			}
//			catch (exception e) {
//				return false;
//			}
//			return true;
//		}
//		return false;
//	}
//	else if (r2 == 0 && c2 == 6) {
//		if ((*board[0])[0] != nullptr) {
//			try {
//				Rook* rook = (Rook*)(*board[0])[7];
//				if (rook->isMoved) return false;
//			}
//			catch (exception e) {
//				return false;
//			}
//			return true;
//		}
//		return false;
//	}
//	else if (r2 == 7 && c2 == 1) {
//		if ((*board[7])[0] != nullptr) {
//			try {
//				Rook* rook = (Rook*)(*board[7])[0];
//				if (rook->isMoved) return false;
//			}
//			catch (exception e) {
//				return false;
//			}
//			return true;
//		}
//		return false;
//	}
//	else if (r2 == 7 && c2 == 6) {
//		if ((*board[7])[7] != nullptr) {
//			try {
//				Rook* rook = (Rook*)(*board[7])[7];
//				if (rook->isMoved) return false;
//			}
//			catch (exception e) {
//				return false;
//			}
//			return true;
//		}
//		return false;
//	}
//}

