#ifndef _UI_H_
#define _UI_H_

#include <stdbool.h>
#include <math.h>
#include "raygui.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

extern int screenWidth;
extern int screenHeight;
extern int graphingAreaHeight;
extern float uiScale;
extern bool showResiduals;

typedef enum
{
	LINEAR_MODE,
	LOGISTIC_MODE,
	RESET
}
buttonOptionEnum;

typedef buttonOptionEnum ButtonOptionE;

ButtonOptionE drawControls();
void updateUIscale(Vector2 baseResolution, Vector2 currentResolution);
Rectangle scaleRectangle(Rectangle button);
#endif
