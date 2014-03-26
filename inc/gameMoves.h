#ifndef gameMoves_H__
#define gameMoves_H__

/*
 * Local headers
 */
#include "board.h"

/*
 * Function prototypes
 */
int isMoveValid(Board *board, int column);
void makeMove(Board *board, int column);
void undoMove(Board *board);
int validMovesLeft(Board *board);
int getRandomMove(Board *board);
int getReasonedMove(Board *board);
int minValue(Board *board, int ply);
int maxValue(Board *board, int ply);

#endif