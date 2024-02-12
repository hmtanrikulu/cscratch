#include "Piece.h"

void test() {
	// Creates the board.
	LinkedList<LinkedList<Piece*>*> board;
	for (int i = 0; i < 8; i++) {
		LinkedList<Piece*>* newElement = new LinkedList<Piece*>;
		board.insert(newElement);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i]->insert(new Piece(i, j, 1, ""));
			(*board[i])[j] = nullptr;
		}
	}

	// Adds Pieces
	(*board[7])[4] = (new King(7, 4, 1, "King"));
	cout << (*board[7])[4]->name;
	(*board[7])[4]->moveCheck(6, 4, board);

	(*board[7])[0] = (new Rook(7, 0, 1, "Rook"));
	cout << (*board[7])[0]->name;
	(*board[7])[0]->moveCheck(7, 1, board);

	(*board[1])[1] = (new Pawn(1, 1, 1, "Pawn"));
	cout << (*board[1])[1]->name;
	(*board[1])[1]->moveCheck(2, 1, board);

	(*board[6])[6] = (new Bishop(6, 6, 1, "Bishop"));
	cout << (*board[6])[6]->name;
	(*board[6])[6]->moveCheck(5, 7, board);

	(*board[5])[5] = (new Queen(5, 5, 1, "Queen"));
	cout << (*board[5])[5]->name;
	(*board[5])[5]->moveCheck(5, 4, board);

	(*board[0])[0] = (new Knight(0, 0, 1, "Knight"));
	cout << (*board[0])[0]->name;
	(*board[0])[0]->moveCheck(1, 2, board);

}


//last error: having trouble because of dangling pointers
// trying to delete them before return 0 using destructors properly.
int main() {
	test();
	cout << "good text dawg";
	return 0;
}

// //Derefrence the pointers you handle before you orint otherwise you may have troubles due to swallow copies.
//cout << (*(board[0]))[2].col;

