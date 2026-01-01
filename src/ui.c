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

Rectangle scaleRectangleIgnoreY(Rectangle rec)
{
	rec.x *= uiScale;
	rec.width *= uiScale;
	rec.height *= uiScale;

	return rec;
}

ButtonOptionE drawControls()
{
		
	DrawRectangle(0 , 0, screenWidth, graphingAreaHeight , Fade(LIGHTGRAY, 0.2f) );

	DrawLine( 0, graphingAreaHeight,
		 screenWidth , 
		 graphingAreaHeight,
		 GRAY );
	
	GuiGroupBox( scaleRectangleIgnoreY( (Rectangle){ 20, graphingAreaHeight + 20 * uiScale, 400, 110 } ), "Controls" );

	if( GuiButton( scaleRectangleIgnoreY( (Rectangle){ 40, graphingAreaHeight + 40 * uiScale, 160, 30 } ), "Linear Mode" ) )
	{
		return LINEAR_MODE;
	}

	if( GuiButton( scaleRectangleIgnoreY( (Rectangle){ 220, graphingAreaHeight + 40 * uiScale, 160, 30 } ), "Logistic Mode") )
	{
		return LOGISTIC_MODE;
	}
		
	if( GuiButton( scaleRectangleIgnoreY( (Rectangle){ 220, graphingAreaHeight + 80 * uiScale , 160, 30 } ), "Reset" ) )
	{
		return RESET;
	}
		
	GuiCheckBox( scaleRectangleIgnoreY( (Rectangle){ 40, graphingAreaHeight + 80 * uiScale, 20, 20 } ), "Show Residuals", &showResiduals );

	return -1;
}


