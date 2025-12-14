#ifndef _DATA_POINT_H_
#define _DATA_POINT_H_

#include "raylib.h" 

#define MAX_POINTS 50 

/*
 * Data point stucture to used for both linear and logistic regression 
 * position, tracks the current position of data point entered
 * class, catergorisies a point whether it is, 0 for Class A (Red) or 1 for Class B (Green)
 */
typedef struct{
	Vector2 position;
	int class;	 
} DataPoint;
 
#endif
