#ifndef CHECKERS_H
#define CHECKERS_H


void jugarDamas();


void initBoard();                 
int getBoardSize();           
char getCell(int r, int c);       
char getCurrentPlayer();           

bool tryMoveGUI(int fromRow, int fromCol, int toRow, int toCol, char &winner);

#endif

