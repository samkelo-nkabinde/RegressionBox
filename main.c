#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "raylib.h"

#include "linear_regression.h"
#include "logistic_regression.h"
#include "ui.h"

#define FRAME_RATE 60
void updateDataPoints(DataPoint data[], int dataCount)
{
	for(int i = 0; i < dataCount; ++i)
	{
		data[i].position.x *= uiScale;
		data[i].position.y *= uiScale;
	}
	return;
}
int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stats SandBox: Regression" );

	Vector2 baseResolution = {SCREEN_WIDTH, SCREEN_HEIGHT};
	Vector2 currentResolution = {GetScreenWidth(), GetScreenHeight()};

	SetTargetFPS(FRAME_RATE);
	
	SetWindowMinSize(560, 380);	


	DataPoint data[MAX_POINTS];
	int dataCount = 0;
	
	/* current UI state/mode, 0 for linear regression, 1 for logistic regression */
	int mode = 0;

	/* linear regression equation, [intercept , slope ]  */
	float regressionLine[2] = {0};

	/* logistic regression weights [bias, weight of x, weight of y] */
	float weights[3] = {0};

	float learningRate = 0.1f;
	int epchos = 50;

	while( !WindowShouldClose() )
	{

		if(IsWindowResized())
		{
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
			currentResolution = (Vector2){screenWidth, screenHeight};
			updateUIscale(baseResolution, currentResolution);
			updateDataPoints(data, dataCount);
			graphingAreaHeight = (int)(0.8 * screenHeight);
		}
		
		/* handling input */
		Vector2 mousePosition = GetMousePosition();
		
		if( mousePosition.y < graphingAreaHeight && dataCount < MAX_POINTS )
		{
			if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )
			{
				data[dataCount].position = mousePosition;
				data[dataCount].class = 0;
				dataCount++;
			}
			else if( IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && mode == 1 )
			{
				data[dataCount].position = mousePosition;
				data[dataCount].class = 1;
				dataCount++;
			}
		}

	        BeginDrawing();
		{
			ClearBackground(RAYWHITE);	
			if(mode)
			{
				trainLogisticModel( data, dataCount, weights, learningRate, epchos);
				drawPoint( data, dataCount );
				drawHeatMap( weights, 20 );
				DrawRectangle(0, graphingAreaHeight, screenWidth, screenHeight, WHITE );
			}
			else
			{
				drawLinearPoints( data, dataCount );

				if( dataCount > 1)
				{
					fitData( data, dataCount, regressionLine );
					drawLineOfBestFit( regressionLine);
					if(showResiduals) drawResiduals( data, dataCount, regressionLine );			
					DrawRectangle(0, graphingAreaHeight, screenWidth, screenHeight, WHITE );
	
				}
			}

			/* UI controls */
			switch(drawControls())
			{
				case LINEAR_MODE:
					mode = 0;
					dataCount = 0;
					break;

				case LOGISTIC_MODE:
					mode = 1;
					dataCount = 0;
					memset(weights, 0, 3*sizeof(float));
					break;

				case RESET:
					dataCount = 0;
					memset(weights, 0, 3*sizeof(float));
					break;

				default:
					break;
			}
		}
	        EndDrawing();		
	}
	CloseWindow();
	return 0;
}
