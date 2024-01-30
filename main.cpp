#include "Piece.h"

void test() {

	LinkedList<LinkedList<Piece*>*> board;
	// Insert rows
	for (int i = 0; i < 8; i++) {
		LinkedList<Piece*>* newElement = new LinkedList<Piece*>;
		board.insert(newElement);
	}

	// Insert columns
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i]->insert(new Piece(i, j, 1, ""));
			(*board[i])[j] = nullptr;
		}
	}	

	(*board[4])[5] = (new King(4, 5, 1, "King"));
	
	// inspect the line 27 in order to understand the design of the program
	// this is our move mechanism !
	Piece* p = (*board[4])[5];
	(*board[4])[5] = nullptr;
	(*board[5])[5] = p;
	if (((*board[4])[5]) == nullptr) cout << "king is gone!" << endl;
	if (((*board[5])[5]) != nullptr) cout << "king is here!";
	cout << (*board[5])[5]->name;
	if ((*board[5])[5]->moveCheck(6, 6, board)) cout << "Let's Move!";
	for (int i = 0; i < 8; i++) {
		delete board[i];
	}
}




//last error: having trouble because of dangling pointers
// trying to delete them before return 0 using destructors properly.
int main() {
	test();
	// write a code that prints all the pieces on the board
	return 0;
}

// //Derefrence the pointers you handle before you orint otherwise you may have troubles due to swallow copies.
//cout << (*(board[0]))[2].col;