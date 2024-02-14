#include "Game.h"

Game::Game() {
	this->turn = 1;
	this->finish = 0;
}

// %50 checkmate part is done complete the check part!
void Game::checkTheKing() {
	// Game status part
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*this->board[i])[j] != nullptr) {
				if ((*this->board[i])[j]->name == "King") {
					King* tmp = dynamic_cast<King*>((*this->board[i])[j]);
					if (tmp != nullptr) {
						for (int m = 0; m < tmp->moveSet.length; m++) {
							int r2 = tmp->moveSet[m].upDown, c2 = tmp->moveSet[m].leftRight;
							// This one is checkmate part
							if (tmp->isDumbMove(r2, c2, this->board) && tmp->isDumbMove(tmp->row, tmp->col, this->board)) {
								if (tmp->isWhite) cout << "black player won !";
								else cout << "white player won";
								this->finish = 1;
							}
							// Check part
							else if (tmp->isDumbMove(tmp->row, tmp->col, this->board)) {
								if (tmp->isDumbMove(r2, c2, this->board)) {
									cout << "check";
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game:: print() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = (*this->board[i])[j];
			if (piece == nullptr) {
				std::cout << ". "; // Print a dot for empty squares
			}
			else {
				char pieceChar = ' '; // Placeholder for the piece character
				// Determine the piece type and assign the corresponding character
				if (piece->name == "Pawn") pieceChar = 'P';
				else if (piece->name == "Rook") pieceChar = 'R';
				else if (piece->name == "Knight") pieceChar = 'N'; // 'K' is for King, so 'N' for kNight
				else if (piece->name == "Bishop") pieceChar = 'B';
				else if (piece->name == "Queen") pieceChar = 'Q';
				else if (piece->name == "King") pieceChar = 'K';

				// Convert to lowercase for black pieces
				if (!piece->isWhite) {
					pieceChar = tolower(pieceChar);
				}

				std::cout << pieceChar << ' ';
			}
		}
		std::cout << std::endl; // New line at the end of each row
	}
}

//void Game::initilizeTheBoard() {
//}


// Don't initilize the board every turn make necessary adjustments !
// Add the moveCheck when a piece takes the other part !

void Game::play() {
	bool currTurn = this->turn;

	// Creates the empty board
	for (int i = 0; i < 8; i++) {
		LinkedList<Piece*>* newElement = new LinkedList<Piece*>;
		this->board.insert(newElement);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->board[i]->insert(new Piece(i, j, 1, ""));
			(*this->board[i])[j] = nullptr;
		}
	}
	// Initialize the board
	(*this->board[0])[0] = new Rook(0, 0, 1, "Rook");
	(*this->board[0])[1] = new Knight(0, 1, 1, "Knight");
	(*this->board[0])[2] = new Bishop(0, 2, 1, "Bishop");
	(*this->board[0])[3] = new Queen(0, 3, 1, "Queen");
	(*this->board[0])[4] = new King(0, 4, 1, "King");
	(*this->board[0])[5] = new Bishop(0, 5, 1, "Bishop");
	(*this->board[0])[6] = new Knight(0, 6, 1, "Knight");
	(*this->board[0])[7] = new Rook(0, 7, 1, "Rook");
	for (int i = 0; i < 8; i++) {
		(*this->board[1])[i] = new Pawn(1, i, 1, "Pawn");
	}
	for (int i = 0; i < 8; i++) {
		(*this->board[6])[i] = new Pawn(6, i, 0, "Pawn");
	}
	(*this->board[7])[0] = new Rook(7, 0, 0, "Rook");
	(*this->board[7])[1] = new Knight(7, 1, 0, "Knight");
	(*this->board[7])[2] = new Bishop(7, 2, 0, "Bishop");
	(*this->board[7])[3] = new Queen(7, 3, 0, "Queen");
	(*this->board[7])[4] = new King(7, 4, 0, "King");
	(*this->board[7])[5] = new Bishop(7, 5, 0, "Bishop");
	(*this->board[7])[6] = new Knight(7, 6, 0, "Knight");
	(*this->board[7])[7] = new Rook(7, 7, 0, "Rook");

	while (this->finish != 1) {
		print();
		LinkedList<char> userPrompt;
		string turnIndicator, moveStr;

		if (this->turn == 1) turnIndicator = "White";
		else turnIndicator = "Black";


		cout << "make your move " << turnIndicator << endl;
		cout << "(ex. 00to40)" << endl;
		cin >> moveStr;
		for (int i = 0; i < moveStr.length(); i++) {
			userPrompt.insert(moveStr[i]);
		}
		int r1 = '7' - userPrompt[0], c1 = userPrompt[1] - '0', r2 = '7' - userPrompt[4], c2 = userPrompt[5] - '0';

		if ((*this->board[r1])[c1]->moveCheck(r2, c2, this->board)) {
			(*this->board[r2])[c2] = (*this->board[r1])[c1];
			(*this->board[r1])[c1] = nullptr;
		}
		else if (!(*this->board[r1])[c1]->moveCheck(r2, c2, this->board)) {
			cout << "invalid input try again!" << endl;
			continue;
		}
			cout << "you made your move " << turnIndicator << "\n\n";
		checkTheKing();
		this->turn = !this->turn;
	}
	cout << "Game Over";
}

	// delete this !
//void test() {
//	// Creates the board.
//	LinkedList<LinkedList<Piece*>*> board;
//	for (int i = 0; i < 8; i++) {
//		LinkedList<Piece*>* newElement = new LinkedList<Piece*>;
//		board.insert(newElement);
//	}
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//			board[i]->insert(new Piece(i, j, 1, ""));
//			(*board[i])[j] = nullptr;
//		}
//	}
//
//	// Adds Pieces
//	(*board[7])[4] = (new King(7, 4, 1, "King"));
//	cout << (*board[7])[4]->name;
//	(*board[7])[4]->moveCheck(6, 4, board);
//
//	(*board[7])[0] = (new Rook(7, 0, 1, "Rook"));
//	cout << (*board[7])[0]->name;
//	(*board[7])[0]->moveCheck(7, 1, board);
//
//	(*board[1])[1] = (new Pawn(1, 1, 1, "Pawn"));
//	cout << (*board[1])[1]->name;
//	(*board[1])[1]->moveCheck(2, 1, board);
//
//	(*board[6])[6] = (new Bishop(6, 6, 1, "Bishop"));
//	cout << (*board[6])[6]->name;
//	(*board[6])[6]->moveCheck(5, 7, board);
//
//	(*board[5])[5] = (new Queen(5, 5, 1, "Queen"));
//	cout << (*board[5])[5]->name;
//	(*board[5])[5]->moveCheck(5, 4, board);
//
//	(*board[0])[0] = (new Knight(0, 0, 1, "Knight"));
//	cout << (*board[0])[0]->name;
//	(*board[0])[0]->moveCheck(1, 2, board);
//}
//
