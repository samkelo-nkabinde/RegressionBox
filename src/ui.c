#define RAYGUI_IMPLEMENTATION
#include "ui.h"

int screenWidth = 1000;
int screenHeight = 700;
int graphingAreaHeight = 550;

bool showResiduals = true;

ButtonOption drawControls()
{
		
	DrawRectangle( 0 , 0, screenWidth, graphingAreaHeight, Fade(LIGHTGRAY, 0.2f) );
	DrawLine( 0, graphingAreaHeight, screenWidth, 550, GRAY );
	
	GuiGroupBox( (Rectangle){ 20, 570, 400, 110 }, "Controls" );

	if( GuiButton( (Rectangle){ 40, 590, 160, 30 }, "Linear Mode" ) )
	{
		return LINEAR_MODE_BUTTON;
	}

	if( GuiButton( (Rectangle){ 220, 590, 160, 30 }, "Logistic Mode") )
	{
		return LOGISTIC_MODE_BUTTON;
	}
		
	if( GuiButton( (Rectangle){ 220, 640, 160, 30 }, "Reset" ) )
	{
		return RESET_BUTTON;
	}
		
	GuiCheckBox( (Rectangle){ 40, 640, 20, 20 }, "Show Residuals", &showResiduals );

	return -1;
}
