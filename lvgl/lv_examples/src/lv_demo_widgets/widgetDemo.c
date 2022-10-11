#include "widgetDemo.h"

/* Widgets */
lv_obj_t* switch1;
lv_obj_t* meter;
lv_obj_t* spinbox;
lv_obj_t* ball;
lv_obj_t* spinner;
lv_obj_t* float_btn;
lv_obj_t* drawer;
lv_obj_t* arrow;
lv_obj_t* dropdownList;
lv_obj_t* arc;
lv_obj_t* contRowDrawer;

/* Menu pages */
lv_obj_t* menu;
lv_obj_t* root_page;
lv_obj_t* switchTransitionPage;
lv_obj_t* meterPage;
lv_obj_t* settingsPage;
lv_obj_t* keyboardPage;
lv_obj_t* drawerPage;

/* Animations */
lv_anim_t ballAnim;
lv_anim_t meterAnim;
lv_anim_t drawerAnim;


int drawerHeightMin = 30;
int drawerHeightMax = 180;

void animSize(void* obj, int32_t value) {
    lv_obj_set_size(obj, value, value);
}

void animYmove(void* obj, int32_t value) {
    lv_obj_set_y(obj, value);
}

void animMeter(void* indic, int32_t value)
{
    lv_meter_set_indicator_value(meter, indic, value);
}


void switch_cb(lv_event_t* e);
lv_obj_t* createMenuCont(lv_obj_t* parent, const char* icon, const char* txt);
void initTransitionMenu(lv_obj_t* parent);
void initMeterMenu(lv_obj_t* parent);
void initSettingsMenu(lv_obj_t* parent);
void initKeyboardMenu(lv_obj_t* parent);
void initDrawerMenu(lv_obj_t* parent);
void dialogBotton_cb(lv_event_t* e);
void menuPageChanged_cb(lv_event_t* e);




void widgetInit(lv_obj_t* parent) {
    /*  Creazione menu */
    menu = lv_menu_create(parent);

    lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
    if (lv_color_brightness(bg_color) > 127) {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 10), 0);
    }
    else {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
    }
    lv_obj_set_size(menu, lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_center(menu);

    lv_obj_t* cont;
    lv_obj_t* section;


    /* Creazione pagine menu*/
    lv_obj_t* switchTransitionPage = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(switchTransitionPage, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(switchTransitionPage);
    section = lv_obj_create(switchTransitionPage);
    lv_obj_set_height(section, lv_pct(95));
    lv_obj_set_width(section, lv_pct(98));
    initTransitionMenu(section);

    meterPage = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(meterPage, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(meterPage);
    section = lv_obj_create(meterPage);
    lv_obj_set_height(section, lv_pct(95));
    lv_obj_set_width(section, lv_pct(98));
    initMeterMenu(section);

    settingsPage = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(settingsPage, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(settingsPage);
    section = lv_menu_section_create(settingsPage);
    lv_obj_set_style_pad_top(section, 10, 0);
    lv_obj_set_style_pad_left(section, 10, 0);
    lv_obj_set_style_pad_row(section, 20, 0);
    initSettingsMenu(section);

    keyboardPage = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(keyboardPage, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(keyboardPage);
    section = lv_obj_create(keyboardPage);
    lv_obj_set_height(section, lv_pct(95));
    lv_obj_set_width(section, lv_pct(98));
    initKeyboardMenu(section);

    drawerPage = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(drawerPage, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(drawerPage);
    section = lv_obj_create(drawerPage);
    lv_obj_set_height(section, lv_pct(95));
    lv_obj_set_width(section, lv_pct(98));
    initDrawerMenu(section);

    lv_obj_add_event_cb(menu, menuPageChanged_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* Creazione indice menu */
    root_page = lv_menu_page_create(menu, "Widget Test");
    lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    section = lv_menu_section_create(root_page);
    cont = createMenuCont(section, LV_SYMBOL_PLAY, "Transition");
    lv_menu_set_load_page_event(menu, cont, switchTransitionPage);

    cont = createMenuCont(section, LV_SYMBOL_BATTERY_FULL, "Meter");
    lv_menu_set_load_page_event(menu, cont, meterPage);

    cont = createMenuCont(section, LV_SYMBOL_SETTINGS, "Settings");
    lv_menu_set_load_page_event(menu, cont, settingsPage);

    cont = createMenuCont(section, LV_SYMBOL_KEYBOARD, "Keyboard");
    lv_menu_set_load_page_event(menu, cont, keyboardPage);

    cont = createMenuCont(section, LV_SYMBOL_LIST, "Drawer");
    lv_menu_set_load_page_event(menu, cont, drawerPage);


    

    lv_menu_set_sidebar_page(menu, root_page);
    /*Create floating btn*/
    float_btn = lv_btn_create(menu);
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -20, -20);
    lv_obj_add_event_cb(float_btn, dialogBotton_cb, LV_EVENT_CLICKED, menu);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_CLOSE, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);

    lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(menu, LV_OBJ_FLAG_HIDDEN);

}



void switch_cb(lv_event_t* e) {
    int ystart, ystop, sizeStart, sizeStop;
    lv_obj_t* target = lv_event_get_target(e);
    lv_state_t state = lv_obj_get_state(target);
    ystart = 0;
    ystop = 400;
    sizeStart = 10;
    sizeStop = 60;
    if (state % 2 != 0) {
        ystart = 0;
        ystop = 300;
        sizeStart = 10;
        sizeStop = 60;
    }
    else {
        ystart = 300;
        ystop = 0;
        sizeStart = 60;
        sizeStop = 10;
    }
    lv_anim_set_values(&ballAnim, sizeStart, sizeStop);
    lv_anim_set_exec_cb(&ballAnim, animSize);
    lv_anim_start(&ballAnim);
    lv_anim_set_exec_cb(&ballAnim, animYmove);
    lv_anim_set_values(&ballAnim, ystart, ystop);
    lv_anim_start(&ballAnim);
}

void messagaBox_cb(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_current_target(e);
    /* Qua possi gestire il bottone schiacciato*/
}

void dialogBotton_cb(lv_event_t* e) {
    static const char* btns[] = { "Conferma", "Annulla", "" };

    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "Dialog", "Conferma o annulla", btns, true);
    lv_obj_add_event_cb(mbox1, messagaBox_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
}

void lv_spinbox_increment_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox);
    }
}

void loadingTimer_cb(lv_timer_t* timer) {
    if(spinner != NULL)
        lv_obj_del(spinner);

    lv_obj_clear_flag(menu, LV_OBJ_FLAG_HIDDEN);
}

void menuHiding() {
    lv_obj_add_flag(menu, LV_OBJ_FLAG_HIDDEN);
}

void menuLoading(lv_obj_t* parent) {
    lv_obj_add_flag(menu, LV_OBJ_FLAG_HIDDEN);
    spinner = lv_spinner_create(parent, 1000, 60);
    lv_obj_set_size(spinner, 100, 100);
    lv_obj_center(spinner);
    lv_timer_t* timer = lv_timer_create(loadingTimer_cb, 500, NULL);
    lv_timer_set_repeat_count(timer, 1);
}


void menuPageChanged_cb(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t* page = lv_menu_get_cur_main_page(target);
    if (page == meterPage)
        lv_anim_start(&meterAnim);
    else
        lv_anim_del(meter, NULL);
    if (float_btn != NULL) {
        if (page == drawerPage)
            lv_obj_add_flag(float_btn, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_clear_flag(float_btn, LV_OBJ_FLAG_HIDDEN);
    }
}

static void lv_spinbox_decrement_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox);
    }
}
lv_obj_t* createMenuCont(lv_obj_t* parent, const char* icon, const char* txt) {
    lv_obj_t* obj = lv_menu_cont_create(parent);
    lv_obj_t* img = NULL;
    lv_obj_t* label = NULL;
    if (icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if (txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }
    return obj;
}

void animDrawer_cb(void* obj, int32_t value)
{
    lv_obj_set_height(obj, value);
}

void drawerPressed_cb(lv_event_t* e) {
    
    lv_anim_set_var(&drawerAnim, drawer);
    
    lv_anim_set_time(&drawerAnim, 250);
    lv_anim_set_exec_cb(&drawerAnim, animDrawer_cb);
    lv_anim_set_path_cb(&drawerAnim, lv_anim_path_overshoot);

    lv_obj_t* target = lv_event_get_target(e);
    if (lv_obj_has_state(target, LV_STATE_CHECKED)) {
        lv_anim_set_values(&drawerAnim, drawerHeightMin, drawerHeightMax);
        lv_obj_align(arrow, LV_ALIGN_TOP_RIGHT, 5, -5);
        lv_label_set_text(arrow, LV_SYMBOL_DOWN);
        lv_obj_clear_flag(contRowDrawer, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_anim_set_values(&drawerAnim, drawerHeightMax, drawerHeightMin);
        lv_obj_align(arrow, LV_ALIGN_RIGHT_MID, 5, 0);
        lv_label_set_text(arrow, LV_SYMBOL_UP);
        lv_obj_add_flag(contRowDrawer, LV_OBJ_FLAG_HIDDEN);
    }
    lv_anim_start(&drawerAnim);
}

void toggleBtn_cb(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t* cont = lv_event_get_user_data(e);
    int n = lv_obj_get_child_cnt(cont);
    if (lv_obj_has_state(target, LV_STATE_CHECKED)) {
        for (int i = 0; i < n; i++) {
            if (lv_obj_get_child(cont, i) != target)
                lv_obj_clear_state(lv_obj_get_child(cont, i), LV_STATE_CHECKED);
        }
    }
}

void initDrawerMenu(lv_obj_t* parent) {
    drawer = lv_obj_create(parent);
    lv_obj_set_align(drawer, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_size(drawer, lv_pct(100), 30);
    lv_obj_clear_flag(drawer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(drawer, lv_palette_lighten(LV_PALETTE_GREY, 4), LV_STATE_DEFAULT);

    arrow = lv_label_create(drawer);
    lv_label_set_text(arrow, LV_SYMBOL_UP);
    lv_obj_align(arrow, LV_ALIGN_RIGHT_MID, 5, 0);
    lv_obj_add_flag(arrow, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(arrow, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(arrow, drawerPressed_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_anim_init(&drawerAnim);

    /* Inizializzo widget all'interno del drawer */

    contRowDrawer = lv_obj_create(drawer);
    lv_obj_set_style_bg_color(contRowDrawer, lv_palette_lighten(LV_PALETTE_GREY, 4), LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(contRowDrawer, 0, LV_STATE_ANY);
    lv_obj_set_flex_flow(contRowDrawer, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_border_opa(contRowDrawer, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_clear_flag(contRowDrawer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_height(contRowDrawer, lv_pct(100));
    lv_obj_set_width(contRowDrawer, lv_pct(100));
    lv_obj_align(contRowDrawer, LV_ALIGN_TOP_MID, 0, 0);
    
    dropdownList = lv_dropdown_create(contRowDrawer);
    lv_dropdown_set_options(dropdownList, "Option 1\n"
        "Option 2\n"
        "Option 3\n"
        "Option 4\n"
        "Option 5\n"
        "Option 6");
    lv_obj_set_height(dropdownList, lv_pct(50));

    lv_obj_t* contBtn = lv_obj_create(contRowDrawer);
    lv_obj_set_size(contBtn, 150, lv_pct(100));
    lv_obj_set_style_bg_color(contBtn, lv_palette_lighten(LV_PALETTE_GREY, 4), LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(contBtn, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(contBtn, 0, LV_STATE_ANY);

    lv_obj_t* btn1 = lv_btn_create(contBtn);
    lv_obj_add_event_cb(btn1, toggleBtn_cb, LV_EVENT_VALUE_CHANGED, contBtn);
    lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_size(btn1, lv_pct(50), lv_pct(100));
    
    lv_obj_align(btn1, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_border_color(btn1, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_STATE_ANY);
    lv_obj_set_style_border_width(btn1, 3, LV_STATE_ANY);
    lv_obj_set_style_border_opa(btn1, LV_OPA_90, LV_STATE_ANY);
 
    lv_obj_t* btnText = lv_label_create(btn1);
    lv_label_set_text(btnText, "S1");
    lv_obj_center(btnText);

    lv_obj_t* btn2 = lv_btn_create(contBtn);
    lv_obj_add_event_cb(btn2, toggleBtn_cb, LV_EVENT_VALUE_CHANGED, contBtn);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_size(btn2, lv_pct(50), lv_pct(100));
    lv_obj_align(btn2, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_border_color(btn2, lv_palette_main(LV_PALETTE_DEEP_PURPLE), LV_STATE_ANY);

    btnText = lv_label_create(btn2);
    lv_label_set_text(btnText, "S2");
    lv_obj_center(btnText);


    lv_obj_add_flag(contRowDrawer, LV_OBJ_FLAG_HIDDEN);

}

void initKeyboardMenu(lv_obj_t* parent) {
    lv_obj_t* kb = lv_keyboard_create(parent);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t* ta;
    ta = lv_textarea_create(parent);
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 10);
    lv_textarea_set_placeholder_text(ta, "Start typing");
    lv_obj_set_size(ta, lv_pct(95), lv_pct(35));


    lv_keyboard_set_textarea(kb, ta);
}

void slider_cb(lv_event_t* e) {
    lv_obj_t* label = lv_event_get_user_data(e);
    lv_obj_t* target = lv_event_get_target(e);

    int value = lv_slider_get_value(target);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", value);
    lv_label_set_text(label, buf);
}
void initSettingsMenu(lv_obj_t* parent) {
    lv_obj_t* cont = lv_menu_cont_create(parent);
    lv_obj_t* cb;
    cb = lv_checkbox_create(cont);
    lv_checkbox_set_text(cb, "XRay");
    cb = lv_checkbox_create(cont);
    lv_checkbox_set_text(cb, "Risparmio energetico");
    lv_obj_add_flag(cb, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    cb = lv_checkbox_create(cont);
    lv_checkbox_set_text(cb, "Ricostruzione algoritmica");
    lv_obj_add_flag(cb, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

    cont = lv_menu_cont_create(parent);
    lv_obj_set_style_pad_column(cont, 20, 0);
    lv_obj_set_style_pad_right(cont, 150, 0);

    lv_obj_t* percentLabel; // Etichetta con testo costante
    percentLabel = lv_label_create(cont);
    lv_label_set_text(percentLabel, "Power");

    percentLabel = lv_label_create(cont); // Etichetta con percentuale che viene modificata dallo slider
    lv_obj_add_flag(percentLabel, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_label_set_text(percentLabel, "0%");

    lv_obj_t* slider;
    slider = lv_slider_create(cont);
    lv_obj_set_flex_grow(slider, 1);
    lv_obj_set_style_pad_row(cont, 20, 0);
    lv_slider_set_range(slider, 0, 100);


    lv_obj_add_event_cb(slider, slider_cb, LV_EVENT_VALUE_CHANGED, percentLabel);

    cont = lv_menu_cont_create(parent);
    const char* opts = "Small\nMedium\nLarge\nExtralarge";
    static lv_style_t style_sel;
    lv_style_init(&style_sel);
    lv_style_set_text_font(&style_sel, &lv_font_montserrat_22);
    lv_obj_t* roller = lv_roller_create(cont);
    lv_roller_set_options(roller, opts, LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(roller, 2);
    lv_obj_add_style(roller, &style_sel, LV_PART_SELECTED);
    lv_roller_set_selected(roller, 1, LV_ANIM_OFF);

    cont = lv_menu_cont_create(parent);


    lv_obj_t* contSpinbox = lv_obj_create(cont);
    lv_obj_set_size(contSpinbox, 200, LV_SIZE_CONTENT);
    lv_obj_set_style_border_opa(contSpinbox, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(contSpinbox, LV_OBJ_FLAG_SCROLLABLE);

    spinbox = lv_spinbox_create(contSpinbox);
    lv_spinbox_set_range(spinbox, -1000, 1000);
    lv_spinbox_set_digit_format(spinbox, 4, 0);
    lv_spinbox_step_prev(spinbox);
    lv_obj_set_width(spinbox, 100);
    lv_obj_center(spinbox);

    lv_coord_t h = lv_obj_get_height(spinbox);

    lv_obj_t* btn = lv_btn_create(contSpinbox);
    lv_obj_set_size(btn, h, h);
    lv_obj_align_to(btn, spinbox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn, lv_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);

    btn = lv_btn_create(contSpinbox);
    lv_obj_set_size(btn, h, h);
    lv_obj_align_to(btn, spinbox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn, lv_spinbox_increment_event_cb, LV_EVENT_ALL, NULL);


    
}

void initTransitionMenu(lv_obj_t* parent) {
    /* Switch con transizione */
    switch1 = lv_switch_create(parent);

    lv_obj_set_align(switch1, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(switch1, switch_cb, LV_EVENT_VALUE_CHANGED, NULL);

    ball = lv_obj_create(parent);

    lv_obj_set_style_bg_color(ball, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_radius(ball, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_size(ball, 10, 10);


    lv_obj_align(ball, LV_ALIGN_TOP_RIGHT, -lv_obj_get_width(ball) / 2, 0);

    lv_anim_init(&ballAnim);
    lv_anim_set_var(&ballAnim, ball);
    lv_anim_timeline_set_reverse(&ballAnim, lv_obj_has_state(switch1, LV_STATE_CHECKED));
    lv_anim_set_time(&ballAnim, 1000);
    lv_anim_set_path_cb(&ballAnim, lv_anim_path_ease_in_out);
}

void initMeterMenu(lv_obj_t* parent) {
    meter = lv_meter_create(parent);
    lv_obj_center(meter);
    lv_obj_set_size(meter, 200, 200);

    /*Add a scale first*/
    lv_meter_scale_t* scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 8);

    lv_meter_indicator_t* indic;

    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);


    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false,
        0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_BLUE_GREY), -10);

    lv_anim_init(&meterAnim);
    lv_anim_set_exec_cb(&meterAnim, animMeter);
    lv_anim_set_var(&meterAnim, indic);
    lv_anim_set_values(&meterAnim, 0, 100);
    lv_anim_set_time(&meterAnim, 2500);
    lv_anim_set_repeat_delay(&meterAnim, 200);
    lv_anim_set_playback_time(&meterAnim, 500);
    lv_anim_set_playback_delay(&meterAnim, 100);
    lv_anim_set_repeat_count(&meterAnim, LV_ANIM_REPEAT_INFINITE);    
}
