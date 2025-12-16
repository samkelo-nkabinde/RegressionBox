#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "raylib.h"

#include "linear_regression.h"
#include "logistic_regression.h"
#include "ui.h"

#define FRAME_RATE 60

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Stats SandBox: Regression" );
	SetTargetFPS(FRAME_RATE);
	
	SetWindowMinSize(320, 224);	


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

		screenWidth = clampScreenWidth( GetScreenWidth() );
		screenHeight = clampScreenHeight( GetScreenHeight() );

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
		ClearBackground(RAYWHITE);
		printf("%d %d\n", screenWidth, screenHeight);	
		if(mode)
		{
			trainLogisticModel( data, dataCount, weights, learningRate, epchos);
			drawPoint( data, dataCount );
			drawHeatMap( weights, 20 );
			DrawRectangle( 0, graphingAreaHeight, screenWidth, screenHeight, WHITE );
		}
		else
		{
			drawLinearPoints( data, dataCount );

			if( dataCount > 1)
			{
				fitData( data, dataCount, regressionLine );
				drawLineOfBestFit( regressionLine);
				if(showResiduals) drawResiduals( data, dataCount, regressionLine );			
				DrawRectangle( 0, graphingAreaHeight, screenWidth, screenHeight, WHITE );		
			}
		}

		/* UI controls */
		switch(drawControls())
		{
			case LINEAR_MODE_BUTTON:
			{
				mode = 0;
				dataCount = 0;
				break;
			}
			case LOGISTIC_MODE_BUTTON:
			{
				mode = 1;
				dataCount = 0;
				memset(weights, 0, 3*sizeof(float));
				break;
			}
			case RESET_BUTTON:
			{
				dataCount = 0;
				memset(weights, 0, 3*sizeof(float));
				break;
			}
			default:
				break;
		}
	        EndDrawing();	
	}
	CloseWindow();
	return 0;
}
