#ifndef point_H__
#define point_H__

/*
 * System libraries
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Types definition
 */ 
typedef struct Point_s Point;

/*
 * Struct for representing each point of the board.
 * x, y: the x-axis and y-axis number of the point. Together they make the point's position. e.g. x = 4, y = 3, point's position is (4,3)
 * state: point's state
 */
struct Point_s
{
	int x, y, state;
};

/*
 * Global variables
 */
#define USER		1
#define COMPUTER	-1
#define EMPTY		0

/*
 * Function prototypes
 */
Point *newPoint(int a, int b);
void deletepoint(Point *point);
void setState(Point *point, int player);
int getState(Point *point);
void generateCL1(Point ***grid, Point ***lines, int *count);
void generateCL2(Point ***grid, Point ***lines, int *count);
void generateCL3(Point ***grid, Point ***lines, int *count);
void generateCL4(Point ***grid, Point ***lines, int *count);
Point ***generateCL(Point ***grid);

#endif