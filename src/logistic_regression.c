#include "logistic_regression.h"

void trainModel( DataPoint* data, int dataCount, float* weights, float learningRate, int epchons, int screenWidth )
{
	for(int i = 0; i < epchons; ++i)
	{
		for(int j = 0; j < dataCount; ++j)
		{
			/* Normilize the data input to range of 0.0 to 1.0 */ 
			float normalized_X = data[j].position.x / screenWidth;
			float normalized_Y = data[j].position.y / 550.0f;
			
			/* Prediction */
			float z = weights[0] + weights[1]*normalized_X + weights[2]*normalized_Y;
			float prediction = sigmoid(z);

			/* Error */
			float error = prediction - (float)data[i].class;

			/* Update weights */
			weights[0] -= error * learningRate * 1.0f;
			weights[1] -= error * learningRate * normalized_X;
			weights[3] -= error * learningRate * normalized_Y;

		}
	}

	return;
}

float sigmoid( float z )
{
	return 1.0f / (1.0f + expf(-z));
}

void drawHeatMap( float* weights, int screenWidth, int pixelCount )
{
	for(int y = 0; y < 550.0f; ++y)
	{
		for(int x = 0; x < screenWidth; ++x)
		{
			/* normalize x and y to span a given pixel area */
			float normalized_X = x / screenWidth;
			float normalized_Y = y / 550.0f;
			
			float probability = sigmoid(weights[0] + normalized_X*weights[1] + normalized_Y*weights[2]);
			
			Color pixelColour;
			if(probability > 0.5f)
			{
				pixelColour = Fade(GREEN, probability*0.3f);
			}
			else
			{
				pixelColour = Fade(RED, (1 - probability)*0.3f);
			}
			
			DrawRectangle(x, y, 20, 20, pixelColour);

		}
	}

	return;
}

void drawPoint( DataPoint* data, int dataCount )
{
        for (int i = 0; i < dataCount; i++) 
	{
                DrawCircleV(data[i].position, 6, (data[i].class == 0) ? MAROON : DARKGREEN);
                DrawCircleLines(data[i].position.x, data[i].position.y, 7, WHITE);
        }

	return;
}
