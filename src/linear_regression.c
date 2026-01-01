#include "linear_regression.h"
#include "ui.h"

void fitData( DataPoint* data, int dataCount, float* regressionLine )
{
	double sum_X = 0, sum_XX = 0, sum_XY = 0, sum_Y = 0;

	for(int i = 0; i < dataCount; ++i)
	{
		sum_X += data[i].position.x;
		sum_XX += data[i].position.x *data[i].position.x;
		sum_XY += data[i].position.x * data[i].position.y;
		sum_Y += data[i].position.y;
	}

	float n = (float)dataCount;
	float regressionSlope = (n*sum_XY - sum_X*sum_Y) / (n*sum_XX - sum_X*sum_X);
	float regressionIntercept = (sum_Y - regressionSlope*sum_X) / n;

	regressionLine[0] = regressionIntercept;
	regressionLine[1] = regressionSlope;

	return;
}

void drawLineOfBestFit(float* regressionLine )
{
	DrawLineEx( (Vector2){ 0, regressionLine[0] }, 
		    (Vector2){ screenWidth, regressionLine[1]*screenWidth + regressionLine[0]}, 
		    3.0f * uiScale, BLUE);

	return;
}

void drawLinearPoints(DataPoint* data, int dataCount)
{
	for (int i = 0; i < dataCount; i++) 
	{
		DrawCircleV(data[i].position, 5 * uiScale, RED);
        }
}

void drawResiduals( DataPoint* data, int dataCount, float* regressionLine )
{
	for( int i = 0; i < dataCount; ++i )
	{
		float predictedY = regressionLine[1]*data[i].position.x  + regressionLine[0]; // y = mx + b
		DrawLineV( (Vector2){ data[i].position.x, data[i].position.y},
			   (Vector2){ data[i].position.x, predictedY}, Fade(RED, 0.5f) );
	}

	return;
}
