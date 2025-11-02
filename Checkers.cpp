#include "clear_window.h"
#include <iostream>
#include <string>
#include <conio.h>

const int SIZE = 10;

using std::cout;

char board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
			board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';
        }
    }
    
    for(int i=0; i < 4; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            if((i + j) % 2 == 1) {
                board[i][j] = 'b'; // Player 1 pieces
            }
        }
	}

    for(int i=6; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            if((i + j) % 2 == 1) {
                board[i][j] = 'w'; // Player 2 pieces
            }
		}


}
}

void printBoard() {
    cout << " ";
    for(int i=0;i < SIZE;++i)
		cout << i << " ";
	cout << "\n";




    for (int i = 0; i < SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool movePiece(int fromRow, int fromCol, int toRow, int toCol, char player) {
    if (toRow < 0 || toRow >= SIZE || toCol < 0 || toCol >= SIZE)
        return false;
    if (board[toRow][toCol] != player || board[toRow][toCol] != '.')
        return false;


    int dir = (player == 'w') ? -1 : 1;
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (rowDiff == dir && abs(colDiff) == 1)
        {
        board[toRow][toCol] = player;
        board[fromRow][fromCol] = '.';
        return true;
	}

    if(rowDiff == 2 * dir && abs(colDiff) == 2) {
        int midRow = fromRow + dir;
        int midCol = fromCol + (colDiff / 2);
        char opponent = (player == 'w') ? 'b' : 'w';
   
        if(board[midRow][midCol] == opponent) {
            board[toRow][toCol] = player;
            board[fromRow][fromCol] = '.';
            board[midRow][midCol] = '.';
            return true;
		}
	}

	return false;

}

int main() {
    clearScreen();
    cout << "¡Bienvenidos a Checkers!\n";


    return 0;
}