/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "app.h"

#include "../../../lvgl/lvgl.h"
#include "../../lv_ex_conf.h"


#include "../../lv_examples.h"
//#include "lv_demo_widgets.h"
//#include <stdio.h>


/*********************
 *      DEFINES
 *********************/



/**********************
 *  STATIC VARIABLES
 **********************/

static lv_style_t textRobotoStyle;
static lv_style_t buttonPressedStyle;
static lv_style_t textRoboto24GreenStyle;
static lv_style_t textRobotoGreenStyle;
static lv_style_t whiteBackground;
lv_style_t greenPressedStyle;
const int zoomFactor = 90; // fattore di zoom per le immagini: 256 è senza zoom, >256= immagine più grande, <256 inmmagine più piccola

lv_obj_t * resetLabel;
lv_obj_t * tileView;
lv_obj_t * mainScreen;
lv_obj_t * widgetScreen;

/* Risorse in file .c*/
extern lv_font_t roboto_14;
extern lv_font_t roboto_24;
extern lv_img_dsc_t resetbtn;
extern lv_img_dsc_t conteinerDati;
extern lv_img_dsc_t topSelectionButtonImg;
extern lv_img_dsc_t BottomLeftSelectionButtonImg;
extern lv_img_dsc_t BottomMidSelectionButtonImg;
extern lv_img_dsc_t BottomRightSelectionButtonImg;
extern lv_img_dsc_t topMidSelectionButtonImg;



void reset_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        resetInitialChecked();
    }
}

static bool widgetMenuAttivo = false;
void tileSwipe_cb(lv_event_t * e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t* tile = lv_tileview_get_tile_act(target);
    if (tile == widgetScreen && !widgetMenuAttivo) {
        menuLoading(widgetScreen);
        widgetMenuAttivo = true;
    }
    else if (tile == mainScreen && widgetMenuAttivo) {
        menuHiding();

        widgetMenuAttivo = false;
    }
}

void app_create(void){

    tileView = lv_tileview_create(NULL);
    mainScreen = lv_tileview_add_tile(tileView, 0, 0, LV_DIR_RIGHT);
    widgetScreen = lv_tileview_add_tile(tileView, 1, 0, LV_DIR_LEFT);


    lv_obj_set_size(mainScreen, 1280, 800);
    lv_obj_clear_flag(mainScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_size(widgetScreen, 1280, 800);
    lv_obj_clear_flag(widgetScreen, LV_OBJ_FLAG_SCROLLABLE);

    widgetInit(widgetScreen);
    lv_obj_add_event_cb(tileView, tileSwipe_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /*
    * Inizializzo gli stili
    */
    lv_color_t colorGreen = lv_color_hex(0x448300);  //Green in RGB
    lv_color_t colorOrange = lv_color_hex(0xedbb3b); //Arancio

    lv_style_init(&whiteBackground);
    lv_style_set_bg_color(&whiteBackground, lv_color_white());
    lv_style_set_border_color(&whiteBackground, lv_color_white());

    lv_style_init(&textRobotoStyle);
    lv_style_set_text_font(&textRobotoStyle, &roboto_14);
    lv_style_set_text_color(&textRobotoStyle, colorOrange);

    lv_style_init(&textRoboto24GreenStyle);
    lv_style_set_text_font(&textRoboto24GreenStyle, &roboto_24);
    lv_style_set_text_color(&textRoboto24GreenStyle, colorGreen);

    lv_style_init(&buttonPressedStyle);
    lv_style_set_img_recolor_opa(&buttonPressedStyle, LV_OPA_30);
    lv_style_set_img_recolor(&buttonPressedStyle, lv_color_black());



    lv_style_init(&greenPressedStyle);
    lv_style_set_img_recolor_opa(&greenPressedStyle, LV_OPA_30);
    lv_style_set_img_recolor(&greenPressedStyle, colorGreen);

    lv_style_init(&textRobotoGreenStyle);
    lv_style_set_text_font(&textRobotoGreenStyle, &roboto_14);

    lv_style_set_text_color(&textRobotoGreenStyle, colorGreen);

    lv_obj_add_style(mainScreen, &whiteBackground, LV_STATE_DEFAULT);

    /*
    * Inizializzo bocca
    */

    lv_obj_t * teethContainer = lv_obj_create(mainScreen);


    lv_obj_align(teethContainer, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(teethContainer, lv_pct(95), lv_pct(90));
    lv_obj_clear_flag(teethContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(teethContainer, &whiteBackground, LV_STATE_DEFAULT);

    lv_obj_t * rightLabel = lv_label_create(teethContainer);
    lv_obj_set_align(rightLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(rightLabel, "R");
    lv_obj_add_style(rightLabel, &textRoboto24GreenStyle, LV_STATE_DEFAULT);

    lv_obj_t * leftLabel = lv_label_create(teethContainer);
    lv_obj_set_align(leftLabel, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(leftLabel, "L");
    lv_obj_add_style(leftLabel, &textRoboto24GreenStyle, LV_STATE_DEFAULT);

    dentalArcInit(teethContainer); //Inizializzo bocca
    buttonsInit(teethContainer);  //Inizializzo bottoni

    /* Inizializzo il bottone per il reset */
    lv_obj_t * resetBtn = lv_img_create(mainScreen);
    imgButtonSetUp(resetBtn, &resetbtn);

    lv_coord_t dimReset = lv_obj_get_width(resetBtn) / 3;
    lv_obj_align(resetBtn, LV_ALIGN_TOP_MID, dimReset, 25);
    lv_obj_add_event_cb(resetBtn, reset_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(resetBtn, deselectAllButtons, LV_EVENT_CLICKED, NULL);

    lv_obj_add_style(resetBtn, &buttonPressedStyle, LV_STATE_PRESSED);

    resetLabel = lv_label_create(resetBtn);
    lv_obj_set_align(resetLabel, LV_ALIGN_CENTER);
    lv_obj_add_style(resetLabel, &textRobotoStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(resetLabel, "Reset");

    /* Inizializzo container dati */
    lv_obj_t * containerLaserData = lv_img_create(mainScreen);
    lv_img_set_src(containerLaserData, &conteinerDati);
    lv_img_set_zoom(containerLaserData, 90);
    lv_img_set_size_mode(containerLaserData, LV_IMG_SIZE_MODE_REAL);


    lv_obj_align(containerLaserData, LV_ALIGN_TOP_MID, -dimReset, 15);
    lv_obj_set_size(containerLaserData, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    lv_obj_t * laserDataLabel = lv_label_create(containerLaserData);
    lv_label_set_text(laserDataLabel, "70 kW - 10 mA");
    lv_obj_add_style(laserDataLabel, &textRobotoGreenStyle, LV_STATE_DEFAULT);
    lv_obj_set_align(laserDataLabel, LV_ALIGN_CENTER);
}

void lv_demo_widgets(void) {
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
        false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);


    app_create();
    lv_disp_load_scr(tileView);
}


