/*
 * System libraries
 */
#include <stdlib.h>
#include <stdio.h>

/*
 * Local headers
 */
#include "../inc/board.h"
#include "../inc/point.h"

/*
 * Creates the board
 */
Board *createBoard()
{
	int x, y;
	Board *board = (Board*)malloc(sizeof(Board));
	
	board->movesMade = 0;
	board->currentPlayer = USER;
	
	board->numOfTokens = (int*)malloc(NUMBER_OF_BOARD_COLUMNS * sizeof(int));
	board->grid = (Point***)malloc(NUMBER_OF_BOARD_COLUMNS * sizeof(Point**));
	board->moves = (int*)malloc(NUMBER_OF_BOARD_COLUMNS * NUMBER_OF_BOARD_ROWS * sizeof(int));
	
	for(x = 0; x < NUMBER_OF_BOARD_COLUMNS; x++)
	{
		board->grid[x] = (Point**)malloc(NUMBER_OF_BOARD_ROWS * sizeof(Point*));
		board->numOfTokens[x] = 0;
		
		for(y = 0; y < NUMBER_OF_BOARD_ROWS; y++)
		{
			board->grid[x][y] = newPoint(x, y);
		}
	}
	
	board->cl = generateCL(board->grid);
	
	return board;
}

/*
 * Deletes the board
 */
void deleteBoard(Board *board)
{
	free(board->cl);
	free(board->grid);
	free(board->numOfTokens);
	free(board->moves);
	free(board);
}

/*
 * Returns current player (the player who is doing the current move)
 */
int getCurrentPlayer(Board *board)
{
	return board->currentPlayer;
}

/*
 * Returns the board's strength
 */
int getBoardStrength(Board *board)
{
	int i, sum = 0, boardStrength;
	int weights[] = {0,1,10,50,600};
	
	for(i = 0; i < 69; i++)
	{
		if(getScore(board->cl[i]) > 0)
		{
			sum = sum + weights[abs(getScore(board->cl[i]))];
		}
		else
		{
			sum = sum - weights[abs(getScore(board->cl[i]))];
		}
	}
	
	if(board->currentPlayer == USER)
	{
		boardStrength = sum + 16;
	}
	else
	{
		boardStrength = sum - 16;
	}
	
	return boardStrength;
}


int getScore(Point *points[]) 
{
	int user = 0, computer = 0, i;
	
	for(i = 0; i < 4; i++)
	{
		if(getState(points[i]) == USER)
		{
			user++;
		}
		else if(getState(points[i]) == COMPUTER)
		{
			computer++;
		}
	}
	
	if(user > computer)
	{
		return user;
	}
	else if(computer > user)
	{
		return -computer;
	}
	else
	{
		return 0;
	}
}

/*
 * Returns 1 (USER) if user has won, -1 (COMPUTER) if computer has won or 0 if game is still going on
 */
int getWinner(Board *board)
{
	int i;
	
	for(i = 0; i < 69; i++)
	{
		if(getScore(board->cl[i]) == 4)
		{
			return USER;
		}
		else if(getScore(board->cl[i]) == -4)
		{
			return COMPUTER;
		}
	}
	
	return 0;
}

/*
 * Displays (prints) the board on the screen
 */
void printBoard(Board *board)
{
	int y, x;
	
	for(y = NUMBER_OF_BOARD_ROWS - 1; y > -1; y--)
	{
		printf("\t\t\t");
		for(x = 0; x < NUMBER_OF_BOARD_COLUMNS; x++)
		{
			if(getState(board->grid[x][y]) == EMPTY)
			{
				printf("- ");
			}
			else if(getState(board->grid[x][y]) == USER)
			{
				printf("O ");
			}
			else
			{
				printf("X ");
			}
		}
		
		printf("\n");
	}
}
