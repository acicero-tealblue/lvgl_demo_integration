/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"
#include "lv_demo_widgets.h"
#include <stdio.h>


/*********************
 *      DEFINES
 *********************/



/**********************
 *  STATIC VARIABLES
 **********************/
//static lv_obj_t * tv;
//static lv_obj_t * t1;
//static lv_obj_t * t2;
//static lv_obj_t * t3;
//static lv_obj_t * kb;

//static lv_style_t style_box;

#if LV_USE_DEMO_WIDGETS

static void event_handler(lv_obj_t* obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        lv_btn_set_state(obj, LV_BTN_STATE_CHECKED_PRESSED);
    }
    else if (event == LV_EVENT_VALUE_CHANGED) {
        lv_btn_set_state(obj, LV_BTN_STATE_CHECKED_DISABLED);
        lv_btn_set_checkable(obj, true);
    }
}



void lv_demo_widgets(void)
{
    lv_obj_t* label;

    lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");

}

#endif
