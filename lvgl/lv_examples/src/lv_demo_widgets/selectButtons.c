#include "selectButtons.h"
#include "dentalArc.h"

/* Risorse esterne nella cartella resources*/
extern lv_img_dsc_t topSelectionButtonImg;
extern lv_img_dsc_t BottomLeftSelectionButtonImg;
extern lv_img_dsc_t BottomMidSelectionButtonImg;
extern lv_img_dsc_t BottomRightSelectionButtonImg;
extern lv_img_dsc_t topMidSelectionButtonImg;
extern const int zoomFactor;

/* Stili importati*/
extern lv_style_t greenPressedStyle;

/* Puntatore ai bottoni*/
lv_obj_t* topSelectionButton;
lv_obj_t* BottomMidSelectionButton;
lv_obj_t* BottomLeftSelectionButton;
lv_obj_t* BottomRightSelectionButton;
lv_obj_t* topMidSelectionButton;

void deselectAllOtherButtons(lv_event_t* e);

void isOnBtnAreaCentered(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_HIT_TEST) {
        lv_hit_test_info_t* info = lv_event_get_param(e);        
        lv_area_t area;
        lv_obj_get_coords(obj, &area);
        int w = area.x2 - area.x1;
        int h = area.y2 - area.y1;
        area.x1 = area.x1 + w / 4;
        area.x2 = area.x2 - w / 4;
        area.y1 = area.y1 + h / 6;
        area.y2 = area.y2 - h / 6;        
        info->res = _lv_area_is_point_on(&area, info->point, h/2);
    }
}

void isOnBtnAreaHorizontalCentered(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_HIT_TEST) {
        lv_hit_test_info_t* info = lv_event_get_param(e);
        lv_area_t area;
        lv_obj_get_coords(obj, &area);
        int w = area.x2 - area.x1;
        int h = area.y2 - area.y1;
        area.x1 = area.x1 + w / 4;
        area.x2 = area.x2 - w / 4;
        area.y1 = area.y1 + h / 2;
        info->res = _lv_area_is_point_on(&area, info->point, h/2);
    }
}


void imgButtonSetUp(lv_obj_t* obj, lv_img_dsc_t* desc) {
    lv_img_set_src(obj, desc);
    lv_img_set_zoom(obj, zoomFactor);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_size_mode(obj, LV_IMG_SIZE_MODE_REAL);
    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
}


void buttonsInit(lv_obj_t* parent) {
    topSelectionButton = lv_img_create(parent);
    imgButtonSetUp(topSelectionButton, &topSelectionButtonImg);
    lv_obj_align(topSelectionButton, LV_ALIGN_TOP_MID, 0, 25);
    lv_obj_add_flag(topSelectionButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_state(topSelectionButton, LV_STATE_CHECKED);
    lv_obj_add_style(topSelectionButton, &greenPressedStyle, LV_STATE_CHECKED);
    lv_obj_add_event_cb(topSelectionButton, topSelectionChecked, LV_EVENT_VALUE_CHANGED, NULL); //collego evento a funzione di callback
    lv_obj_add_event_cb(topSelectionButton, deselectAllOtherButtons, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(topSelectionButton, isOnBtnAreaCentered, LV_EVENT_ALL, NULL);

    lv_coord_t botSelectBtnPos = lv_obj_get_width(parent) * 0.18;
    
    BottomMidSelectionButton = lv_img_create(parent);
    imgButtonSetUp(BottomMidSelectionButton, &BottomMidSelectionButtonImg);
    lv_obj_align(BottomMidSelectionButton, LV_ALIGN_BOTTOM_MID, 0, 15);
    lv_obj_add_flag(BottomMidSelectionButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_state(BottomMidSelectionButton, LV_STATE_CHECKED);
    lv_obj_add_style(BottomMidSelectionButton, &greenPressedStyle, LV_STATE_CHECKED);
    lv_obj_add_event_cb(BottomMidSelectionButton, bottomMidSelectionChecked, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(BottomMidSelectionButton, deselectAllOtherButtons, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(BottomMidSelectionButton, isOnBtnAreaHorizontalCentered, LV_EVENT_ALL, NULL);

    BottomLeftSelectionButton = lv_img_create(parent);
    imgButtonSetUp(BottomLeftSelectionButton, &BottomLeftSelectionButtonImg);
    lv_obj_align(BottomLeftSelectionButton, LV_ALIGN_BOTTOM_MID, -botSelectBtnPos, -10);
    lv_obj_add_flag(BottomLeftSelectionButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_state(BottomLeftSelectionButton, LV_STATE_CHECKED);
    lv_obj_add_style(BottomLeftSelectionButton, &greenPressedStyle, LV_STATE_CHECKED);
    lv_obj_add_event_cb(BottomLeftSelectionButton, bottomLeftSelectionChecked, LV_EVENT_VALUE_CHANGED, NULL); //collego evento a funzione di callback
    lv_obj_add_event_cb(BottomLeftSelectionButton, deselectAllOtherButtons, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(BottomLeftSelectionButton, isOnBtnAreaCentered, LV_EVENT_ALL, NULL);

    BottomRightSelectionButton = lv_img_create(parent);
    imgButtonSetUp(BottomRightSelectionButton, &BottomRightSelectionButtonImg);
    lv_obj_align(BottomRightSelectionButton, LV_ALIGN_BOTTOM_MID, botSelectBtnPos, -10);
    lv_obj_add_flag(BottomRightSelectionButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_state(BottomRightSelectionButton, LV_STATE_CHECKED);
    lv_obj_add_style(BottomRightSelectionButton, &greenPressedStyle, LV_STATE_CHECKED);
    lv_obj_add_event_cb(BottomRightSelectionButton, bottomRightSelectionChecked, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(BottomRightSelectionButton, deselectAllOtherButtons, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(BottomRightSelectionButton, isOnBtnAreaCentered, LV_EVENT_ALL, NULL);

    lv_coord_t posTopMidSelect = lv_obj_get_height(topSelectionButton) * 2.3;
    
    topMidSelectionButton = lv_img_create(parent);
    imgButtonSetUp(topMidSelectionButton, &topMidSelectionButtonImg);
    lv_obj_align(topMidSelectionButton, LV_ALIGN_TOP_MID, 0, posTopMidSelect);
    lv_obj_add_flag(topMidSelectionButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_state(topMidSelectionButton, LV_STATE_CHECKED);
    lv_obj_add_style(topMidSelectionButton, &greenPressedStyle, LV_STATE_CHECKED);
    lv_obj_add_event_cb(topMidSelectionButton, topMidSelectionChecked, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(topMidSelectionButton, deselectAllOtherButtons, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(topMidSelectionButton, isOnBtnAreaCentered, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(topMidSelectionButton, LV_OBJ_FLAG_HIDDEN);
}

void deselectAllButtons() {
    lv_obj_clear_state(topSelectionButton, LV_STATE_CHECKED);
    lv_obj_clear_state(BottomMidSelectionButton, LV_STATE_CHECKED);
    lv_obj_clear_state(BottomLeftSelectionButton, LV_STATE_CHECKED);
    lv_obj_clear_state(BottomRightSelectionButton, LV_STATE_CHECKED);
    lv_obj_clear_state(topMidSelectionButton, LV_STATE_CHECKED);
}

void deselectAllOtherButtons(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (state % 2 != 0) {
        lv_obj_clear_state(topSelectionButton, LV_STATE_CHECKED);
        lv_obj_clear_state(BottomMidSelectionButton, LV_STATE_CHECKED);
        lv_obj_clear_state(BottomLeftSelectionButton, LV_STATE_CHECKED);
        lv_obj_clear_state(BottomRightSelectionButton, LV_STATE_CHECKED);
        lv_obj_clear_state(topMidSelectionButton, LV_STATE_CHECKED);
        lv_obj_add_state(target, LV_STATE_CHECKED);
    }
}
