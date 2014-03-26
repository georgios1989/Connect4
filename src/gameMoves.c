/*
 * System libraries
 */
#include <stdlib.h>
#include <limits.h>

/*
 * Local headers
 */
#include "../inc/gameMoves.h"
#include "../inc/board.h" 

/*
 * Global variables for move validation
 */
#define VALID_MOVE				1
#define INVALID_MOVE			0
#define VALID_MOVES_LEFT		1
#define VALID_MOVES_NOT_LEFT	0

/*
 * Checks if a move is valid. If valid, returns 1 (VALID_MOVE) otherwise 0 (INVALID_MOVE)
 */
int isMoveValid(Board *board, int column)
{
	if(board->numOfTokens[column] < NUMBER_OF_BOARD_ROWS)
	{
		return VALID_MOVE;
	}
	else
	{
		return INVALID_MOVE;
	}
}

/*
 * Adds token to the selected column
 */
void makeMove(Board *board, int column)
{	
	setState(board->grid[column][board->numOfTokens[column]], board->currentPlayer);
	
	board->numOfTokens[column]++;
	board->movesMade++;
	board->moves[board->movesMade] = column;
	board->currentPlayer = -board->currentPlayer;
}

/*
 * Undo previous move
 */
void undoMove(Board *board)
{
	setState(board->grid[board->moves[board->movesMade]][board->numOfTokens[board->moves[board->movesMade]]-1], (EMPTY));
	
	board->numOfTokens[board->moves[board->movesMade]]--;
	board->movesMade--;
	board->currentPlayer = -board->currentPlayer;	
}

/*
 * Returns 1 (VALID_MOVES_LEFT) if valid moves do exist and 0 (VALID_MOVES_NOT_LEFT) if not
 */
int validMovesLeft(Board *board)
{
	if(board->movesMade < (NUMBER_OF_BOARD_COLUMNS * NUMBER_OF_BOARD_ROWS))
	{
		return VALID_MOVES_LEFT;
	}
	else
	{
		return VALID_MOVES_NOT_LEFT;
	}
}

/*
 * Chooses and returns a random move
 */
int getRandomMove(Board *board)
{
	int i, selectedMove = -1, randomColumn;
	int isColumnValid[NUMBER_OF_BOARD_COLUMNS];
	
	for(i = 0; i < NUMBER_OF_BOARD_COLUMNS; i++)
	{
		if(isMoveValid(board, i))
		{
			isColumnValid[i] = 1;
		}
		else
		{
			isColumnValid[i] = 0;
		}
	}
	
	while(selectedMove == -1)
	{
		randomColumn = rand() % NUMBER_OF_BOARD_COLUMNS;
		
		if(isColumnValid[randomColumn] == 1)
		{
			selectedMove = randomColumn;
		}
	}
	
	return selectedMove;
}

/*
 * Chooses and returns a reasoned move
 */
int getReasonedMove(Board *board)
{
	int i, highest = 0;
	int moves[NUMBER_OF_BOARD_COLUMNS];
	
	for(i = 0; i < NUMBER_OF_BOARD_COLUMNS; i++)
	{
		moves[i] = INT_MIN;
		
		if(isMoveValid(board, i))
		{
			makeMove(board, i);
			moves[i] = minValue(board, 4);
			
			if(moves[i] >= moves[highest])
			{
				highest = i;
			}
			
			undoMove(board);  /* DOUBLE CHECK THIS!!! */
		} 
	}
	
	return highest;
}

// don't change this unless you understand it
int minValue(Board *board, int ply)
{
	int i, lowest = 0;
	int moves[NUMBER_OF_BOARD_COLUMNS];
	
	for(i = 0; i < NUMBER_OF_BOARD_COLUMNS; i++)
	{
		moves[i] = INT_MAX;
		
		if(isMoveValid(board, i))
		{
			makeMove(board, i);
			
			if((getWinner(board) == 0) && ply > 0)
			{
				moves[i] = maxValue(board, ply - 1);
			}
			else 
			{
				moves[i] = -getBoardStrength(board);
			}
			
			if(moves[i] < moves[lowest])
			{
				lowest = i;
			}
			
			undoMove(board);   /* DOUBLE CHECK THIS!!! */
		}
		
	}
	
	return moves[lowest];
}

//careful with this
int maxValue(Board *board, int ply)
{
	int i, highest = 0;
	int moves[NUMBER_OF_BOARD_COLUMNS];
	
	for(i = 0; i < NUMBER_OF_BOARD_COLUMNS; i++)
	{
		moves[i] = INT_MAX;
		
		if(isMoveValid(board, i))
		{
			makeMove(board, i);
			if((getWinner(board) == 0) && ply > 0)
			{
				moves[i] = minValue(board, ply - 1);
			}
			else
			{
				moves[i] = -getBoardStrength(board);
			}
			
			if(moves[i] < moves[highest])
			{
				highest = i;
			}
			
			undoMove(board);
		}
	}
	
	return moves[highest];
}




