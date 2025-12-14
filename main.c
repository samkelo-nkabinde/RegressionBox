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
	
	/* 0 for linear regression, 1 for logistic regression */
	int mode = 0;
	bool showResiduals = true;

	/* linear regression equation, [intercept , slope ]  */
	float regressionLine[2] = {0};

	/* logistic regression weights [bias, weight of x, weight of y] */
	float weights[3] = {0};

	float leaningRate = 0.1f;

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		/* UI controls */
		DrawRectangle(0 , 0, SCREEN_WIDTH, 550, Fade(LIGHTGRAY, 0.2f));
		DrawLine(0, 550, SCREEN_WIDTH, 550, GRAY);
		//DrawRectangle(0, 550, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
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
			memset(weights, sizeof(float), 3);
		}
		
		if( GuiButton( (Rectangle){ 220, 640, 160, 30}, "Reset" ) )
		{
			dataCount = 0;
			memset(weights, sizeof(float), 3);
		}
		
		GuiCheckBox( (Rectangle){ 40, 640, 20, 20 }, "Show Residuals", &showResiduals);
		EndDrawing();	
	}
	CloseWindow();
	return 0;
}
