#ifndef _LINEAR_REGRESSION_H_
#define _LINEAR_REGRESSION_H_

#include "raylib.h"
#include "data_point.h"


/*
 * Finds the line of best fit using least of squres method 
 * References an float array of [regression intercept (b), regression slope (m)] for the formula y = mx + b
 */
void fitData( DataPoint* data, int dataCount, float* regressionLine );

/*
 * Draws the line of best fit using the calculated regression line
 */
void drawLineOfBestFit( float* regressionLine );

/*
 * Draws a Red circle, to represent a data point
 */
void drawLinearPoints(DataPoint* data, int dataCount);

/*
 * Finds the predicted y, then calcuted the error distance from the actual y
 * Draws the error distance from the actual point to the predicted y, the y point of the line of best fit
 */
void drawResiduals( DataPoint* data, int dataCount, float* regressionLine );

#endif
