/*
 * System libraries
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * Local headers
 */
#include "../inc/point.h"
#include "../inc/board.h"
#include "../inc/gameMoves.h"

/*
 * Function prototypes
 */
int welcomeMessage();
int selectDifficulty();
int getUserMoveChoice(Board *board);
void printWinnerAndScore(int winner, int *userScore, int *computerScore);

/*
 * Main function of the game
 */
int main(int argc, char **argv) 
{
	int userMoveChoice, winner, difficulty, userScore = 0, computerScore = 0;
	int startGame, continueGame; 
	Board *board;
	char *boardString = (char*)malloc(NUMBER_OF_BOARD_ROWS * (NUMBER_OF_BOARD_COLUMNS + 1) * sizeof(char) + 1);
	
	startGame = welcomeMessage();
	if(startGame != 1)
	{
		printf("Exiting game\n");
		exit(-1);
	}
	
	while(1)
	{
		board = createBoard();
		
		difficulty = selectDifficulty();
		
		printf("\nGAME STARTS\n");
		
		while((getWinner(board) == 0) && validMovesLeft(board))
		{
			if(getCurrentPlayer(board) == USER)	
			{
				userMoveChoice = getUserMoveChoice(board);
				makeMove(board, userMoveChoice);
			}
			else
			{
				printf("\n\t\tComputer's turn...\n");
				
				if(difficulty == 1)
				{
					makeMove(board, getRandomMove(board));
				}
				else
				{
					makeMove(board, getReasonedMove(board));
				}
			}
			
			printBoard(board);
		}
		
		winner = getWinner(board);
		printWinnerAndScore(winner, &userScore, &computerScore);
		
		printf("Enter 1 to continue playing or any other number to exit the game: ");
		scanf("%d", &continueGame);
		if(continueGame != 1)
		{
			deleteBoard(board);
			break;
		}
		
		deleteBoard(board);
	}
	
	printf("Exiting game\n");
 
	free(boardString);
	
	return 0;
}

/*
 * Displays a welcoming message and asks the user if we wants to play or exit the game.
 * Returns user's choice
 */
int welcomeMessage()
{
	int startGame;
	
	printf("Welcome to the game!\n"); 
	printf("Enter 1 to start a new game, or any other integer number to exit the game: ");
	scanf("%d", &startGame);
	
	return startGame;
}

/*
 * Asks user to provide the game difficulty.
 * Returns user's selected difficulty
 */
int selectDifficulty()
{
	int difficulty;
	
	printf("Choose 1 for random computer moves, or 2 for reasoned computer moves: ");
	scanf("%d", &difficulty);
	while(difficulty < 1 || difficulty > 2)
	{
		printf("Difficulty must be 1 or 2. Please specify difficulty again: ");
		scanf("%d", &difficulty);	
	}		
		
	return difficulty;
}

/*
 * Gets and returns user's selected move.
 */
int getUserMoveChoice(Board *board)
{
	int userMoveChoice, isValid;
	
	printf("\n\t\tYour turn. Choose column: ");
	scanf("%d", &userMoveChoice);
	
	isValid = isMoveValid(board, userMoveChoice - 1);
	while(userMoveChoice < 1 || userMoveChoice > NUMBER_OF_BOARD_COLUMNS || isValid == 0)
	{
		if(userMoveChoice < 1 || userMoveChoice > NUMBER_OF_BOARD_COLUMNS)
		{
			printf("\t\tYour choice must be 1 to 7. Please give your choice again: ");
		}
		else
		{
			printf("\t\tColumn %d is full. Please choose a valid column: ", userMoveChoice);
		}
		
		scanf("%d", &userMoveChoice);	
		isValid = isMoveValid(board, userMoveChoice - 1);
	}
	
	userMoveChoice--;
	
	return userMoveChoice;
}

/*
 * Prints current game's winner and current score
 */
void printWinnerAndScore(int winner, int *userScore, int *computerScore)
{
	if(winner == USER)
	{
		printf("YOU HAVE WON\n\n");
		(*userScore)++;
	}
	else if(winner == COMPUTER)
	{
		printf("YOU HAVE LOST\n\n");
		(*computerScore)++;
	}
	else
	{
		printf("GAME ENDED AS A TIE\n\n");
	}
	
	printf("SCORE: \n");
	printf("User's score: %d\n", *userScore);
	printf("Computer's score: %d\n\n", *computerScore);
}








