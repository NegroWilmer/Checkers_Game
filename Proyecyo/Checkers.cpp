#include "clear_window.h"
#include "linux.h"
#include <iostream>
#include <iomanip>
#include <cctype>

const int SIZE = 10;
char board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'b';

    for (int i = 6; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'w';
}

void printBoard() {
    std::cout << "   ";
    for (int i = 0; i < SIZE; ++i) std::cout << std::setw(3) << i;
    std::cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        std::cout << std::setw(3) << i;
        for (int j = 0; j < SIZE; ++j)
            std::cout << '[' << board[i][j] << ']';
        std::cout << "\n";
    }
}

bool isKing(char p) {
    return std::isupper(static_cast<unsigned char>(p));
}

bool isOpponent(char p, char player) {
    if (player == 'w') return p == 'b' || p == 'B';
    else return p == 'w' || p == 'W';
}

bool diagonalClear(int fromRow, int fromCol, int toRow, int toCol) {
    int dr = (toRow > fromRow) ? 1 : -1;
    int dc = (toCol > fromCol) ? 1 : -1;
    int r = fromRow + dr, c = fromCol + dc;
    while (r != toRow && c != toCol) {
        if (board[r][c] != '.') return false;
        r += dr;
        c += dc;
    }
    return true;
}

bool canCapture(char player) {
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            char piece = board[r][c];
            if (piece == '.' || piece == ' ') continue;
            if (player == 'w' && !(piece == 'w' || piece == 'W')) continue;
            if (player == 'b' && !(piece == 'b' || piece == 'B')) continue;

            int drs[4] = { 1, 1, -1, -1 };
            int dcs[4] = { 1, -1, 1, -1 };

            for (int d = 0; d < 4; ++d) {
                int mr = r + drs[d], mc = c + dcs[d];
                int lr = r + 2 * drs[d], lc = c + 2 * dcs[d];
                if (mr >= 0 && mr < SIZE && mc >= 0 && mc < SIZE &&
                    lr >= 0 && lr < SIZE && lc >= 0 && lc < SIZE &&
                    isOpponent(board[mr][mc], player) && board[lr][lc] == '.')
                    return true;

                if (isKing(piece)) {
                    int rr = r + drs[d], cc = c + dcs[d];
                    bool found = false;
                    while (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE) {
                        if (board[rr][cc] == '.') {
                            rr += drs[d]; cc += dcs[d];
                            continue;
                        }
                        if (isOpponent(board[rr][cc], player)) {
                            int lr = rr + drs[d], lc = cc + dcs[d];
                            while (lr >= 0 && lr < SIZE && lc >= 0 && lc < SIZE) {
                                if (board[lr][lc] == '.') return true;
                                else break;
                            }
                            break;
                        }
                        else break;
                    }
                }
            }
        }
    }
    return false;
}

bool movePiece(int fromRow, int fromCol, int toRow, int toCol, char player) {
    if (fromRow < 0 || fromRow >= SIZE || fromCol < 0 || fromCol >= SIZE ||
        toRow < 0 || toRow >= SIZE || toCol < 0 || toCol >= SIZE)
        return false;

    char piece = board[fromRow][fromCol];
    if (piece == '.' || piece == ' ') return false;
    if (player == 'w' && !(piece == 'w' || piece == 'W')) return false;
    if (player == 'b' && !(piece == 'b' || piece == 'B')) return false;
    if (board[toRow][toCol] != '.') return false;

    int dr = toRow - fromRow, dc = toCol - fromCol;
    int absDr = std::abs(dr), absDc = std::abs(dc);
    bool king = isKing(piece);

    if (canCapture(player)) {
        if (!king && absDr == 2 && absDc == 2) {
            int midRow = (fromRow + toRow) / 2;
            int midCol = (fromCol + toCol) / 2;
            if (isOpponent(board[midRow][midCol], player)) {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
                board[midRow][midCol] = '.';
                if (player == 'w' && toRow == 0) board[toRow][toCol] = 'W';
                if (player == 'b' && toRow == SIZE - 1) board[toRow][toCol] = 'B';
                return true;
            }
        }
        else if (king && absDr == absDc && absDr >= 2) {
            int stepR = (dr > 0) ? 1 : -1;
            int stepC = (dc > 0) ? 1 : -1;
            int r = fromRow + stepR, c = fromCol + stepC;
            int oppRow = -1, oppCol = -1;
            while (r != toRow && c != toCol) {
                if (board[r][c] == '.') {
                    r += stepR; c += stepC;
                    continue;
                }
                if (isOpponent(board[r][c], player) && oppRow == -1) {
                    oppRow = r; oppCol = c;
                    r += stepR; c += stepC;
                    while (r != toRow && c != toCol) {
                        if (board[r][c] != '.') return false;
                        r += stepR; c += stepC;
                    }
                    break;
                }
                else return false;
            }
            if (oppRow != -1) {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
                board[oppRow][oppCol] = '.';
                return true;
            }
        }
        std::cout << "Debe capturar si es posible. Presione una tecla para continuar.\n";
        (void)_getch();
        return false;
    }

    if (!king && absDr == 1 && absDc == 1) {
        int dir = (player == 'w') ? -1 : 1;
        if (dr == dir) {
            board[toRow][toCol] = piece;
            board[fromRow][fromCol] = '.';
            if (player == 'w' && toRow == 0) board[toRow][toCol] = 'W';
            if (player == 'b' && toRow == SIZE - 1) board[toRow][toCol] = 'B';
            return true;
        }
    }

    if (king && absDr == absDc && diagonalClear(fromRow, fromCol, toRow, toCol)) {
        board[toRow][toCol] = piece;
        board[fromRow][fromCol] = '.';
        return true;
    }

    return false;
}

bool isGameOver(char& winner) {
    int w = 0, b = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 'w' || board[i][j] == 'W') w++;
            if (board[i][j] == 'b' || board[i][j] == 'B') b++;
        }
	if (w == 0) {
        winner = 'b';
        return true;
    }
    if (b == 0) {
        winner = 'w';
        return true;
    }
	return false;
}

    void jugarDamas() {
        initBoard();
        char player = 'w';
        char winner;

        while (true) {
            printBoard();
            std::cout << "jugador " << player << " es tu turno (formato: DesdeFila DesdeCol ParaFila ParaCol): ";
            int fromRow, fromCol, toRow, toCol;
            std::cin >> fromRow >> fromCol >> toRow >> toCol;

            if (!std::cin) {
                std::cout << "Entrada no valida. Saliendo.\n";
                (void)_getch();
                break;
            }

            if (!movePiece(fromRow, fromCol, toRow, toCol, player)) {
                std::cout << "Movimiento invalido. Intente de nuevo.\n";
                (void)_getch();
                continue;
            }

            if (isGameOver(winner)) {
                printBoard();
                std::cout << "¡Juego terminado! Jugador " << winner << " gana.\n";
                (void)_getch();
                break;
            }

            player = (player == 'w') ? 'b' : 'w';
        }
    }
