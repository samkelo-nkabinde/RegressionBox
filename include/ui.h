#ifndef _UI_H_
#define _UI_H_

#include <stdbool.h>

#include "raygui.h"

extern int screenWidth;
extern int screenHeight;
extern int graphingAreaHeight;

typedef enum{

	LINEAR_MODE_BUTTON,
	LOGISTIC_MODE_BUTTON,
	RESET_BUTTON

}ButtonOption;

extern bool showResiduals;

ButtonOption drawControls();

#endif
