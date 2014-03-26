/*
 * System libraries
 */
#include <stdlib.h>

/*
 * Local headers
 */
#include "../inc/point.h"
#include "../inc/board.h"

 
/*
 * Creates and returns a new point
 */
Point *newPoint(int a, int b)
{
	Point *point = (Point*)malloc(sizeof(Point));
	
	point->x = a;
	point->y = b;
	point->state = EMPTY;
	
	return point;
}

/*
 * Deletes a point
 */
void deletepoint(Point *point)
{
	free(point);
}

/*
 * Sets point's state: e.g. if user added a token at this point, state = USER
 */
void setState(Point *point, int player)
{
	point->state = player;
}

/*
 * Returns a point's state
 */
int getState(Point *point)
{
	return point->state;
}

void generateCL1(Point ***grid, Point ***lines, int *count)
{
	int i, y, x, t;
	
	for(y = 0; y < NUMBER_OF_BOARD_ROWS; y++)
	{
		for(x = 0; x < 4; x++)
		{
			Point **temp = (Point**)malloc(4 * sizeof(Point*));
			
			for(i = x; i < x + 4; i++)
			{
				temp[i-x] = grid[i][y];
			}
			
			lines[*count] = temp;
			(*count)++;
		}
	}
}

void generateCL2(Point ***grid, Point ***lines, int *count)
{
	int i, y, x, t;
	
	for(x = 0; x < NUMBER_OF_BOARD_COLUMNS; x++)
	{
		for(y = 0; y < 3; y++)
		{
			Point **temp = (Point**)malloc(4 * sizeof(Point*));
			
			for(i = y; i < y + 4; i++)
			{
				temp[i-y] = grid[x][i];
			}
			
			lines[*count] = temp;
			(*count)++;
		}
	}
}

void generateCL3(Point ***grid, Point ***lines, int *count)
{
	int i, y, x, t;
	
	for(x = 0; x < 4; x++)
	{
		for(y = 0; y < 3; y++)
		{
			Point **temp = (Point**)malloc(4 * sizeof(Point*));
			
			for(t = x, i = y; t < x + 4 && i < y + 4; t++, i++)
			{
				temp[i-y] = grid[t][i];
			}
			
			lines[*count]=temp;
			(*count)++;
		}
	}
}

void generateCL4(Point ***grid, Point ***lines, int *count)
{
	int i, y, x, t;
	
	for(x = 0; x < 4; x++)
	{
		for(y = 5; y > 2; y--)
		{
			Point **temp = (Point**)malloc(4 * sizeof(Point*));
			
			for(t = x, i = y; t < x + 4 && i > -1; t++, i--)
			{
				temp[t-x] = grid[t][i];
			}
			
			lines[*count] = temp;
			(*count)++;
		}
	}
}

Point ***generateCL(Point ***grid)
{
	int i, y, x, t, count = 0;
	Point ***lines = (Point***)malloc(69 * sizeof(Point**));
	
	for(i = 0; i < 69; i++)
	{
		lines[i] = (Point**)malloc(4 * sizeof(Point*));
	}
	
	generateCL1(grid, lines, &count);
	generateCL2(grid, lines, &count);
	generateCL3(grid, lines, &count);
	generateCL4(grid, lines, &count);
	
	return lines;
}



