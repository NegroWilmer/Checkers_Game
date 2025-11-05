#include "clear_window.h"
#include "Linux.h"
#include <iostream>
#include <iomanip>


const int SIZE = 10;

char board[SIZE][SIZE];

void initBoard() {
	for (int i = 0; i < SIZE; ++i) {
		for (int	 j = 0; j < SIZE; ++j) {
			board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if ((i + j) % 2 == 1) {
				board[i][j] = 'b'; 
			}
		}
	}

	for (int i = 6; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if ((i + j) % 2 == 1) {
				board[i][j] = 'w'; 
			}
		}


	}
}

void printBoard() {

	std::cout << "   ";
	for (int i = 0; i < SIZE; ++i)
		std::cout << std::setw(3) << i;
	std::cout << "\n";

	for (int i = 0; i < SIZE; ++i) {
		
		std::cout << std::setw(3) << i;
		for (int j = 0; j < SIZE; ++j) {
			std::cout << '[' << board[i][j] << ']';
		}
		std::cout << "\n";
	}
}

bool movePiece(int fromRow, int fromCol, int toRow, int toCol, char player) {
	
	if (fromRow < 0 || fromRow >= SIZE || fromCol < 0 || fromCol >= SIZE)
		return false;
	if (toRow < 0 || toRow >= SIZE || toCol < 0 || toCol >= SIZE)
		return false;

	
	if (board[fromRow][fromCol] != player)
		return false;

	
	if (board[toRow][toCol] != '.')
		return false;

	int dir = (player == 'w') ? -1 : 1;
	int rowDiff = toRow - fromRow;
	int colDiff = toCol - fromCol;

	
	if (rowDiff == dir && std::abs(colDiff) == 1)
	{
		board[toRow][toCol] = player;
		board[fromRow][fromCol] = '.';
		return true;
	}

	
	if (rowDiff == 2 * dir && std::abs(colDiff) == 2) {
		int midRow = fromRow + dir;
		int midCol = fromCol + (colDiff / 2);

		if (midRow < 0 || midRow >= SIZE || midCol < 0 || midCol >= SIZE)
			return false;

		char opponent = (player == 'w') ? 'b' : 'w';

		if (board[midRow][midCol] == opponent) {
			board[toRow][toCol] = player;
			board[fromRow][fromCol] = '.';
			board[midRow][midCol] = '.';
			return true;
		}
	}

	return false;
}

bool isGameOver(char& winner) {
	int wCout = 0, bCout = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] == 'w') wCout++;
			if (board[i][j] == 'b') bCout++;
		}

	if (wCout == 0) {
		winner = 'b';
		return true;
	}
	if (bCout == 0) {
		winner = 'w'; return true;
	}

	return false;

}

int main() {
	initBoard();
	char player = 'w';
	char winner;

	while (true) {
		printBoard();
		std::cout << "jugador " << player << "'s turn (format: fromRow fromCol toRow toCol): ";
		int fromRow, fromCol, toRow, toCol;
		std::cin >> fromRow >> fromCol >> toRow >> toCol;

		if (!std::cin) {
			std::cout << "entrada no valida. Saliendo. \n";
			(void)_getch();
			break;
		}
		if (movePiece(fromRow, fromCol, toRow, toCol, player)) {
			if (isGameOver(winner)) {
				printBoard();
				std::cout << "Game over! jugador " << player << "wins\n";
				(void)_getch();
				break;
			}
			player = (player == 'w') ? 'b' : 'w';
		}
		else {
			std::cout << "movimiento invalido. intente de nuevo \n";
			(void)_getch();
		}
	}
	return 0;
}
