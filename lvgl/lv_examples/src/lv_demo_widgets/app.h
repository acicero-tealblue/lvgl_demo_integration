﻿#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************
 *      INCLUDES
 **********************/

#include "../../../lvgl/lvgl.h"
#include "dentalArc.h"
#include "selectButtons.h"
#include "widgetDemo.h"

/**********************
 *       WIDGETS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern lv_obj_t* mainScreen;

void lv_demo_widgets();
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_H*/
