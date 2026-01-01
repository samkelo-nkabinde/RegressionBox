#include "logistic_regression.h"
#include "ui.h"

void trainLogisticModel( DataPoint* data, int dataCount, float* weights, float learningRate, int epchons )
{
	for(int i = 0; i < epchons; ++i)
	{
		for(int j = 0; j < dataCount; ++j)
		{
			/* Normilize the data input to range of 0.0 to 1.0 */ 
			float normalized_X = data[j].position.x / (float)screenWidth;
			float normalized_Y = data[j].position.y / (float)graphingAreaHeight;
			
			/* Prediction */
			float z = weights[0] + weights[1]*normalized_X + weights[2]*normalized_Y;
			float prediction = sigmoid(z);

			/* Error */
			float error = prediction - (float)data[j].class;

			/* Update weights */
			weights[0] -= error * learningRate * 1.0f;
			weights[1] -= error * learningRate * normalized_X;
			weights[2] -= error * learningRate * normalized_Y;

		}
	}

	return;
}

float sigmoid( float z )
{
	return 1.0f / (1.0f + expf(-z));
}

void drawHeatMap( float* weights, int pixelCount )
{
	for(int y = 0; y < (int)(550 * uiScale); y += pixelCount)
	{
		for(int x = 0; x < screenWidth; x += pixelCount)
		{
			/* normalize x and y to span a given pixel area */
			float normalized_X = (float)x / screenWidth;
			float normalized_Y = (float)y / graphingAreaHeight;
			
			float probability = sigmoid(weights[0] + normalized_X*weights[1] + normalized_Y*weights[2]);
			
			Color pixelColour;
			if(probability > 0.5f)
			{
				pixelColour = Fade(GREEN, probability*0.3f);
			}
			else
			{
				pixelColour = Fade(RED, (1.0f - probability)*0.3f);
			}
			
			DrawRectangleRec(scaleRectangle( (Rectangle){ x, y, pixelCount, pixelCount } ), pixelColour);

		}
	}

	return;
}

void drawPoint( DataPoint* data, int dataCount )
{
        for (int i = 0; i < dataCount; ++i) 
	{
                DrawCircleV(data[i].position, 6 * uiScale, (data[i].class == 0) ? MAROON : DARKGREEN);
                DrawCircleLines(data[i].position.x, data[i].position.y, 7 * uiScale, WHITE);
        }

	return;
}
