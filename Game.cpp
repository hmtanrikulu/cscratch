#include "Game.h"

Game::Game() {
	this->turn = 1;
	this->finish = 0;
	this->check = 0;
	this->escape = 0;
}

bool Game::isKingInCheck() {
	King* king = nullptr;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = (*this->board[i])[j];
			if (piece != nullptr && piece->name == "King" && piece->isWhite == !this->turn) {
				King* tmp = dynamic_cast<King*>(piece);
				if (tmp && tmp->isDumbMove(tmp->row, tmp->col, this->board)) {
					king = tmp;
				}
			}
		}
	}
	if (king == nullptr) return false;
	else return true;
}


bool Game::moveResolvesTheCheck(int r1, int c1, int r2, int c2) {
	Piece* tempDest = (*this->board[r2])[c2]; // Temporarily store the destination piece
	Piece* tempSrc = (*this->board[r1])[c1]; // Temporarily store the source piece

	// Simulate the move
	(*this->board[r2])[c2] = tempSrc;
	(*this->board[r1])[c1] = nullptr;
	if (tempSrc) {
		tempSrc->row = r2;
		tempSrc->col = c2;
	}

	// Check if the move resolves the check
	bool checkResolved = !isKingInCheck();

	// Immediately revert the move
	(*this->board[r1])[c1] = tempSrc;
	(*this->board[r2])[c2] = tempDest;
	if (tempSrc) {
		tempSrc->row = r1;
		tempSrc->col = c1;
	}

	return checkResolved;
}


void Game::gameStatus() {
	King* king = nullptr;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = (*this->board[i])[j];
			if (piece != nullptr && piece->name == "King") {
				King* tmp = dynamic_cast<King*>(piece);
				if (tmp && tmp->isDumbMove(tmp->row, tmp->col, this->board)) {
					king = tmp;
					this->check = true;
				}
			}
		}
	}

	if (king != nullptr) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Piece* piece = (*this->board[i])[j];
				if (piece != nullptr && piece->isWhite == king->isWhite) {
					for (int m = 0; m < piece->moveSet.length; m++) {
						int saveMoveR = piece->moveSet[m].upDown + piece->row, saveMoveC = piece->moveSet[m].leftRight + piece->col;
						if (piece->moveCheck(saveMoveR, saveMoveC, this->board) && moveResolvesTheCheck(i, j, saveMoveR, saveMoveC)) {
							this->escape = true;
							break;
						}
					}
				}
			}
		}

		if (this->escape == 0 && this->check == 1) {
			cout << king->isWhite ? "\nBlack player won! GG!\n" : "\nWhite player won! GG!\n";
			this->finish = 1;
		}
		else {
			cout << "\n king is checked!\n";
		}
	}
}


void Game::play() {
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
	(*this->board[0])[0] = new Rook(0, 0, 0, "Rook");
	(*this->board[0])[1] = new Knight(0, 1, 0, "Knight");
	(*this->board[0])[2] = new Bishop(0, 2, 0, "Bishop");
	(*this->board[0])[3] = new Queen(0, 3, 0, "Queen");
	(*this->board[0])[4] = new King(0, 4, 0, "King");
	(*this->board[0])[5] = new Bishop(0, 5, 0, "Bishop");
	(*this->board[0])[6] = new Knight(0, 6, 0, "Knight");
	(*this->board[0])[7] = new Rook(0, 7, 0, "Rook");
	for (int i = 0; i < 8; i++) {
		(*this->board[1])[i] = new Pawn(1, i, 0, "Pawn");
	}
	for (int i = 0; i < 8; i++) {
		(*this->board[6])[i] = new Pawn(6, i, 1, "Pawn");
	}
	(*this->board[7])[0] = new Rook(7, 0, 1, "Rook");
	(*this->board[7])[1] = new Knight(7, 1, 1, "Knight");
	(*this->board[7])[2] = new Bishop(7, 2, 1, "Bishop");
	(*this->board[7])[3] = new Queen(7, 3, 1, "Queen");
	(*this->board[7])[4] = new King(7, 4, 1, "King");
	(*this->board[7])[5] = new Bishop(7, 5, 1, "Bishop");
	(*this->board[7])[6] = new Knight(7, 6, 1, "Knight");
	(*this->board[7])[7] = new Rook(7, 7, 1, "Rook");

	while (!this->finish) {
		print();
		string turnIndicator = this->turn ? "White" : "Black";
		string moveStr;
		cout << "Make your move " << (this->turn ? "White" : "Black") << "(ex.a2 to a4) : ";
		cin >> moveStr;
		int r1 = '8' - moveStr[1], c1 = moveStr[0] - 'a';
		int r2 = '8' - moveStr[5], c2 = moveStr[4] - 'a';


		// Escape movesda bu move var mý ???
		if (this->escape == 1 && this->check == 1 && !moveResolvesTheCheck(r1, c1, r2, c2)) continue;
		this->escape = 0;
		this->check = 0;

		try {
			if (!(*this->board[r1])[c1]->moveCheck(r2, c2, this->board) || (*this->board[r1])[c1] == nullptr || (*this->board[r1])[c1]->isWhite != this->turn) {
				throw invalid_argument("move is not valid!");
			}
			(*this->board[r2])[c2] = (*this->board[r1])[c1];
			(*this->board[r2])[c2]->row = r2, (*this->board[r2])[c2]->col = c2;
			(*this->board[r1])[c1] = nullptr;
			cout << "you made your move " << turnIndicator << "\n\n";
		}
		catch (const exception& e) {
			cout << "Invalid input, try again!" << endl;
			continue;
		}

		gameStatus();
		this->turn = !this->turn;
	}
	cout << "Game Over";	
}

void Game::print() {

	for (int i = 0; i < 8; i++) {
		cout << 8 - i << "|" << " ";
		for (int j = 0; j < 8; j++) {
			Piece* piece = (*this->board[i])[j];
			if (piece == nullptr) {
				cout << ". ";
			}
			else {
				char pieceChar = ' ';
				if (piece->name == "Pawn") pieceChar = 'P';
				else if (piece->name == "Rook") pieceChar = 'R';
				else if (piece->name == "Knight") pieceChar = 'N';
				else if (piece->name == "Bishop") pieceChar = 'B';
				else if (piece->name == "Queen") pieceChar = 'Q';
				else if (piece->name == "King") pieceChar = 'K';
				if (!piece->isWhite) {
					pieceChar = tolower(pieceChar);
				}

				cout << pieceChar << ' ';
			}
		}
		cout << endl;
	}
	cout << " " << " " << " a b c d e f g h\n";

}
