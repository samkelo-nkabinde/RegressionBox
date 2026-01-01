#define RAYGUI_IMPLEMENTATION
#include "ui.h"

int screenWidth = SCREEN_WIDTH;
int screenHeight = SCREEN_HEIGHT;
int graphingAreaHeight = 550;
float uiScale = 1.0;
bool showResiduals = true;

void updateUIscale(Vector2 baseResolution, Vector2 currentResolution)
{
	float scaleX = currentResolution.x / baseResolution.x;
	float scaleY = currentResolution.y / baseResolution.y;
	uiScale = fminf(scaleX, scaleY);
}

Rectangle scaleRectangle(Rectangle rec)
{
	rec.x *= uiScale;
	rec.y *= uiScale;
	rec.width *= uiScale;
	rec.height *= uiScale;

	return rec;
}

ButtonOptionE drawControls()
{
		
	DrawRectangle(0 , 0, screenWidth, graphingAreaHeight * uiScale, Fade(LIGHTGRAY, 0.2f) );

	DrawLine( 0, graphingAreaHeight * uiScale,
		 screenWidth , 
		 graphingAreaHeight * uiScale,
		 GRAY );
	
	GuiGroupBox( scaleRectangle( (Rectangle){ 20, 570, 400, 110 } ), "Controls" );

	if( GuiButton( scaleRectangle( (Rectangle){ 40, 590, 160, 30 } ), "Linear Mode" ) )
	{
		return LINEAR_MODE;
	}

	if( GuiButton( scaleRectangle( (Rectangle){ 220, 590, 160, 30 } ), "Logistic Mode") )
	{
		return LOGISTIC_MODE;
	}
		
	if( GuiButton( scaleRectangle( (Rectangle){ 220, 640, 160, 30 } ), "Reset" ) )
	{
		return RESET;
	}
		
	GuiCheckBox( scaleRectangle( (Rectangle){ 40, 640, 20, 20 } ), "Show Residuals", &showResiduals );

	return -1;
}


