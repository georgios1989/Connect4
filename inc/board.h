#ifndef board_H__
#define board_H__

/*
 * Local headers
 */
#include "point.h"

/*
 * Types definition
 */
typedef struct Board_s Board;

/*
 * Struct for representing the board.
 * movesMade: how many moves have been done until current board state.
 * currentPlayer: the player doing the current move.
 * numOfTokens: a 1D array showing how many tokens have been added to each column.
 * moves: a 1D array showing column selected at each move (e.g. at 1st move column 3 was selected)
 */
struct Board_s 
{
	int movesMade, currentPlayer;
	int *numOfTokens, *moves; // moves: column selected at that move
	Point ***grid, ***cl;
};

/*
 * Global variables
 */
#define NUMBER_OF_BOARD_COLUMNS		7
#define NUMBER_OF_BOARD_ROWS		6

/*
 * Function prototypes
 */
Board *createBoard();
void deleteBoard(Board *board);
int getCurrentPlayer(Board *board);		
int getBoardStrength(Board *board);
int getScore(Point *points[]);
int getWinner(Board *board);
void printBoard(Board *board);

#endif