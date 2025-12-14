#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "linear_regression.h"
#include "logistic_regression.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
#define FRAME_RATE 60

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stats SandBox: Regression" );
	SetTargetFPS(FRAME_RATE);

	DataPoint data[MAX_POINTS];
	int dataCount = 0;
	
	/* current UI state/mode, 0 for linear regression, 1 for logistic regression */
	int mode = 0;
	bool showResiduals = true;

	/* linear regression equation, [intercept , slope ]  */
	float regressionLine[2] = {0};

	/* logistic regression weights [bias, weight of x, weight of y] */
	float weights[3] = {0};

	float learningRate = 0.1f;
	int epchos = 50;

	while(!WindowShouldClose())
	{
		/* handling input */
		Vector2 mousePosition = GetMousePosition();
		
		if( mousePosition.y < 550 && dataCount < MAX_POINTS)
		{
			if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				data[dataCount].position = mousePosition;
				data[dataCount].class = 0;
				dataCount++;
			}
			else if( IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && mode == 1)
			{
				data[dataCount].position = mousePosition;
				data[dataCount].class = 1;
				dataCount++;
			}
		}

	        BeginDrawing();
		ClearBackground(RAYWHITE);
		
		if(mode)
		{
			trainLogisticModel( data, dataCount,
					    weights, learningRate,
					    epchos, SCREEN_WIDTH );

			drawPoint( data, dataCount );
			drawHeatMap( weights, SCREEN_WIDTH, 20 );
			DrawRectangle(0, 550, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
		}
		else
		{
			drawLinearPoints( data, dataCount);

			if( dataCount > 1)
			{
				fitData( data, dataCount, regressionLine );
				drawLineOfBestFit( regressionLine, SCREEN_WIDTH);
				if(showResiduals) drawResiduals( data, dataCount, regressionLine );			
				DrawRectangle(0, 550, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);		
			}
		}

		/* UI controls */
		DrawRectangle(0 , 0, SCREEN_WIDTH, 550, Fade(LIGHTGRAY, 0.2f));
		DrawLine(0, 550, SCREEN_WIDTH, 550, GRAY);

		GuiGroupBox( (Rectangle){ 20, 570, 400, 110 }, "Controls" );

		if( GuiButton( (Rectangle){ 40, 590, 160, 30 }, "Linear Mode" ) )
		{
			mode = 0;
			dataCount = 0;
		}

		if( GuiButton( (Rectangle){ 220, 590, 160, 30}, "Logistic Mode") )
		{
			mode = 1;
			dataCount = 0;
			memset(weights, 0, 3*sizeof(float));
		}
		
		if( GuiButton( (Rectangle){ 220, 640, 160, 30}, "Reset" ) )
		{
			dataCount = 0;
			memset(weights, 0, 3*sizeof(float));
		}
		
		GuiCheckBox( (Rectangle){ 40, 640, 20, 20 }, "Show Residuals", &showResiduals);
	        EndDrawing();	
	}
	CloseWindow();
	return 0;
}
