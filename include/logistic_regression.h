#ifndef _LOGISTIC_REGRESSION_H_
#define _LOGISTIC_REGRESSION_H_

#include <math.h>

#include "raylib.h"
#include "data_point.h"
#include "ui.h"

/*
 * Train a logistic model for a finite number of epchons,
 * References a float array of the form [bias, weight of x, wight of y] 
 * Finds the weights such that z < 0 for Class A (Red), z > 0 for Class B (Green)
 * where z is calculated with the formula z = bias + weight of x + weight of y
 */
void 
trainLogisticModel( DataPoint* data, int dataCount, float* weights, float learningRate, int epchons );

/*
 * Activation function for the model
 */
float sigmoid( float z );

/*
 * Draw the decision boundary 
 * Samples the screen for specific number of pixels to draw the probability field
 */
void drawHeatMap( float* weights, int pixelCount );

/*
 * Draw point, Red dot for class A and Green dot for class B
 */
void drawPoint( DataPoint* data, int dataCount );

void displayWeights(float* weights);

#endif
