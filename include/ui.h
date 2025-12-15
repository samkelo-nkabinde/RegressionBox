#ifndef _UI_H_
#define _UI_H_

#include <stdbool.h>

#include "raygui.h"

#define SCREEN_WIDTH 1000 
#define SCREEN_HEIGHT 700
#define GRAPHING_HEIGHT

typedef enum{

	LINEAR_MODE_BUTTON,
	LOGISTIC_MODE_BUTTON,
	RESET_BUTTON

}ButtonOption;

extern bool showResiduals;

ButtonOption drawControls();

#endif
