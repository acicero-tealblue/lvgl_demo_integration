#include "dentalArc.h"

#define NUMDENTALGROUPS 10
/* GLOBAL VARIABLES */
extern int zoomFactor;
int verticalSpacing = 10;
int horizontalSpacing = 5;

/* Risorse in file .c*/
extern lv_img_dsc_t resetbtn;
extern lv_img_dsc_t conteinerDati;
extern lv_img_dsc_t leftMostTeethImg;
extern lv_img_dsc_t dentalArcBottomFirstLeftImg;
extern lv_img_dsc_t dentalArcBottomFirstRightImg;
extern lv_img_dsc_t dentalArcBottomMiddleLeftImg;
extern lv_img_dsc_t dentalArcBottomMiddleRightImg;
extern lv_img_dsc_t dentalArcRightMostImg;
extern lv_img_dsc_t dentalArcTopFirstLeftImg;
extern lv_img_dsc_t dentalArcTopFirstRightImg;
extern lv_img_dsc_t dentalArcTopMiddleLeftImg;
extern lv_img_dsc_t dentalArcTopMiddleRightImg;

static lv_style_t greenPressedStyle;

static bool initialized = false;

/* Puntatori ai gruppi dentali*/
lv_obj_t* leftMostTeeth; //0
lv_obj_t* dentalArcTopMiddleLeft; //1
lv_obj_t* dentalArcTopFirstLeft; //2
lv_obj_t* dentalArcTopFirstRight; //3
lv_obj_t* dentalArcTopMiddleRight; //4
lv_obj_t* dentalArcBottomMiddleLeft; //5
lv_obj_t* dentalArcBottomFirstLeft; //6
lv_obj_t* dentalArcBottomFirstRight; //7
lv_obj_t* dentalArcBottomMiddleRight; //8
lv_obj_t* dentalArcRightMost; //9

lv_obj_t* dentalGroupsArray[NUMDENTALGROUPS]; // vettore per scorrere facilmente tra i vari gruppi dentali


/* FUNCTIONS PROTOTIPES */
void createDentalGroup(lv_obj_t* dentalGroup, lv_img_dsc_t* imgDesc);
void changeDentalGroupPositioning(lv_obj_t* dentalGroup, int left_right, int top_bottom, lv_coord_t horizontalChange, lv_coord_t verticalChange);
void setUpCallbackBtnReset();
void dentalArcInit(lv_obj_t* parent) {
    
    if (!initialized) {
        /* init style pressed*/
        lv_color_t colorGreen = lv_color_hex(0x448300);
        lv_style_init(&greenPressedStyle);
        lv_style_set_img_recolor_opa(&greenPressedStyle, LV_OPA_30);
        lv_style_set_img_recolor(&greenPressedStyle, colorGreen);

        dentalArcTopFirstLeft = lv_img_create(parent);
        createDentalGroup(dentalArcTopFirstLeft, &dentalArcTopFirstLeftImg);
        changeDentalGroupPositioning(dentalArcTopFirstLeft, -1, -1, 0, 0);
        lv_obj_add_state(dentalArcTopFirstLeft, LV_STATE_CHECKED);

        dentalGroupsArray[2] = dentalArcTopFirstLeft;

        dentalArcBottomFirstLeft = lv_img_create(parent);
        createDentalGroup(dentalArcBottomFirstLeft, &dentalArcBottomFirstLeftImg);
        changeDentalGroupPositioning(dentalArcBottomFirstLeft, -1, 1, 0, 0);
        lv_obj_add_state(dentalArcBottomFirstLeft, LV_STATE_CHECKED);
        dentalGroupsArray[6] = dentalArcBottomFirstLeft;

        dentalArcTopFirstRight = lv_img_create(parent);
        createDentalGroup(dentalArcTopFirstRight, &dentalArcTopFirstRightImg);
        changeDentalGroupPositioning(dentalArcTopFirstRight, 1, -1, 0, 0);
        lv_obj_add_state(dentalArcTopFirstRight, LV_STATE_CHECKED);
        dentalGroupsArray[3] = dentalArcTopFirstRight;

        dentalArcBottomFirstRight = lv_img_create(parent);
        createDentalGroup(dentalArcBottomFirstRight, &dentalArcBottomFirstRightImg);
        changeDentalGroupPositioning(dentalArcBottomFirstRight, 1, 1, 0, 0);
        lv_obj_add_state(dentalArcBottomFirstRight, LV_STATE_CHECKED);
        dentalGroupsArray[7] = dentalArcBottomFirstRight;

        dentalArcTopMiddleLeft = lv_img_create(parent);
        createDentalGroup(dentalArcTopMiddleLeft, &dentalArcTopMiddleLeftImg);
        changeDentalGroupPositioning(dentalArcTopMiddleLeft, -1, -1, lv_obj_get_width(dentalArcTopFirstLeft), 0);
        dentalGroupsArray[1] = dentalArcTopMiddleLeft;

        dentalArcBottomMiddleLeft = lv_img_create(parent);
        createDentalGroup(dentalArcBottomMiddleLeft, &dentalArcBottomMiddleLeftImg);
        changeDentalGroupPositioning(dentalArcBottomMiddleLeft, -1, 1, lv_obj_get_width(dentalArcTopFirstLeft) - 8, 30);
        dentalGroupsArray[5] = dentalArcBottomMiddleLeft;

        dentalArcTopMiddleRight = lv_img_create(parent);
        createDentalGroup(dentalArcTopMiddleRight, &dentalArcTopMiddleRightImg);
        changeDentalGroupPositioning(dentalArcTopMiddleRight, 1, -1, lv_obj_get_width(dentalArcTopFirstLeft), 0);
        dentalGroupsArray[4] = dentalArcTopMiddleRight;

        dentalArcBottomMiddleRight = lv_img_create(parent);
        createDentalGroup(dentalArcBottomMiddleRight, &dentalArcBottomMiddleRightImg);
        changeDentalGroupPositioning(dentalArcBottomMiddleRight, 1, 1, lv_obj_get_width(dentalArcTopFirstLeft) - 8, 30);
        dentalGroupsArray[8] = dentalArcBottomMiddleRight;

        leftMostTeeth = lv_img_create(parent);
        createDentalGroup(leftMostTeeth, &leftMostTeethImg);
        changeDentalGroupPositioning(leftMostTeeth, -1, 0, lv_obj_get_width(dentalArcTopFirstLeft) + lv_obj_get_width(dentalArcTopMiddleLeft) - 10, 50);
        dentalGroupsArray[0] = leftMostTeeth;

        dentalArcRightMost = lv_img_create(parent);
        createDentalGroup(dentalArcRightMost, &dentalArcRightMostImg);
        changeDentalGroupPositioning(dentalArcRightMost, 1, 0, lv_obj_get_width(dentalArcTopFirstLeft) + lv_obj_get_width(dentalArcTopMiddleLeft) - 10, 50);
        dentalGroupsArray[9] = dentalArcRightMost;

        setUpCallbackBtnReset();
        initialized = true;
    }
}

/*
* Funzione per il set up di un gruppo dentale. Il primo parametro è un img lvgl mentre il secondo è il descrittore dell'immagine
* che è salvato nel rispettivo file .c
*/
void createDentalGroup(lv_obj_t* dentalGroup, lv_img_dsc_t* imgDesc) {
    lv_img_set_src(dentalGroup, imgDesc);
    lv_img_set_zoom(dentalGroup, zoomFactor);
    lv_obj_add_flag(dentalGroup, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_size_mode(dentalGroup, LV_IMG_SIZE_MODE_REAL);
    lv_obj_set_size(dentalGroup, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_flag(dentalGroup, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_style(dentalGroup, &greenPressedStyle, LV_STATE_CHECKED);
}

/*
* Funzione per il posizionamento del gruppo dentale. Fornisce un posizionamento a spanne nella bocca partendo dalle sue dimensioni,
* occorre raffinare il posizionamento per mezzo dei parametri horizontal e vertical change
* left_right: +1 se dx, -1 se sx
* top_bottom: +1 se bottom, -1 se top, 0 se al centro
*/
void changeDentalGroupPositioning(lv_obj_t* dentalGroup, int left_right, int top_bottom, lv_coord_t horizontalChange, lv_coord_t verticalChange) {
    lv_coord_t dentalGroupWidth = lv_obj_get_width(dentalGroup); // width senza contare lo zoom
    lv_coord_t dentalGroupHeight = lv_obj_get_height(dentalGroup);

    lv_obj_align(dentalGroup, LV_ALIGN_CENTER, left_right * dentalGroupWidth * zoomFactor / 256 * 0.5 + (left_right) * (int)(horizontalSpacing + horizontalChange), top_bottom * dentalGroupHeight * zoomFactor / 256 * 0.5 + top_bottom * (int)verticalSpacing - verticalChange);
}

void setUpCallbackBtnReset(){
    for (int i = 0; i < NUMDENTALGROUPS; i++)
        lv_obj_add_event_cb(dentalGroupsArray[i], deselectAllButtons, LV_EVENT_VALUE_CHANGED, NULL);

}

void resetInitialChecked() {
    if (initialized) {
        for (int i = 0; i < NUMDENTALGROUPS; i++) {
            if (i == 2 || i == 3 || i == 6 || i == 7)
                lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            else
                lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
        }
    }
}

void topSelectionChecked(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (initialized) {
        if (state % 2 != 0) {
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                if (i > 0 && i < NUMDENTALGROUPS - 1)
                    lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
                else
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
        else {
            lv_obj_clear_state(target, LV_STATE_CHECKED);
            for (int i = 1; i < NUMDENTALGROUPS-1; i++) {
                lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
    }
}

void bottomLeftSelectionChecked(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (initialized) {
        if (state % 2 != 0) {
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                if (i==1||i==2||i==5||i==6)
                    lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
                else
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
        else {
            lv_obj_clear_state(target, LV_STATE_CHECKED);
            for (int i = 1; i < NUMDENTALGROUPS - 1; i++) {
                if (i == 1 || i == 2 || i == 5 || i == 6)
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }

    }
}

void bottomRightSelectionChecked(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (initialized) {
        if (state % 2 != 0) {
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                if (i == 3 || i == 4 || i == 7 || i == 8)
                    lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
                else
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
        else {
            lv_obj_clear_state(target, LV_STATE_CHECKED);
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                if (i == 3 || i == 4 || i == 7 || i == 8)
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
    }
}

void bottomMidSelectionChecked(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (initialized) {
        if (state % 2 != 0) {
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                    lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
        else {
            lv_obj_clear_state(target, LV_STATE_CHECKED);
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
    }
}

void topMidSelectionChecked(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    if (initialized) {
        if (state % 2 != 0) {
            for (int i = 0; i < NUMDENTALGROUPS; i++) {
                if (i == 2 || i == 3 || i == 6 || i == 7)
                    lv_obj_add_state(dentalGroupsArray[i], LV_STATE_CHECKED);
                else
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
        else {
            lv_obj_clear_state(target, LV_STATE_CHECKED);
            for (int i = 2; i < NUMDENTALGROUPS - 2; i++) {
                if (i == 2 || i == 3 || i == 6 || i == 7)
                    lv_obj_clear_state(dentalGroupsArray[i], LV_STATE_CHECKED);
            }
        }
    }
}
