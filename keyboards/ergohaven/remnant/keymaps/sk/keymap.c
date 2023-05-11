#include QMK_KEYBOARD_H

#include "layers.h"
#include "features/caps_word.h"
#include "features/select_word.h"

static layer_state_t current_layer_state = 0;

enum custom_keycodes {
    SELECT_WORD = SAFE_RANGE,
    // Other custom keys...
    STICKY_LAYER_TOGGLE,
};

#define L_GUI_T LGUI_T(KC_A)
#define L_ALT_T LALT_T(KC_S)
#define L_CTL_T LCTL_T(KC_D)
#define L_SFT_T LSFT_T(KC_F)

#define R_GUI_T RGUI_T(KC_J)
#define R_ALT_T RALT_T(KC_K)
#define R_CTL_T RCTL_T(KC_L)
#define R_SFT_T RSFT_T(KC_SCLN)

#define LT_CURS LT(_CURSOR,KC_BSPC)
#define LT_NUMB LT(_NUMBERS,KC_DEL)
#define LT_FUNC LT(_FKEYS,KC_ESC)
#define LT_SYST LT(_SYS,KC_ENT)
#define LT_MOUS LT(_MOUSE,KC_TAB)
#define LT_SYMB LT(_SYMBOLS,KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_5x6(
                             KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS ,
                             KC_BSLS, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL  ,
                             CW_TOGG, L_GUI_T, L_ALT_T, L_CTL_T, L_SFT_T, KC_G   ,          KC_H   , R_SFT_T, R_CTL_T, R_ALT_T, R_GUI_T, KC_QUOT ,
                             KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT ,
                                               KC_PGUP, KC_PGDN,                                              KC_LBRC, KC_RBRC,
                                                          LT_CURS, LT_NUMB, LT_FUNC,     LT_SYST, LT_MOUS, LT_SYMB
                           ),
	[1] = LAYOUT_5x6_5(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_BSLS, KC_B, KC_Y, KC_O, KC_U, KC_QUOT, KC_SCLN, KC_L, KC_D, KC_W, KC_V, KC_Z, CW_TOGG, LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMM, KC_DOT, LSFT_T(KC_H), LCTL_T(KC_T), LALT_T(KC_S), LGUI_T(KC_N), KC_Q, KC_LSFT, KC_G, KC_X, KC_J, KC_K, KC_MINS, KC_SLSH, KC_R, KC_M, KC_F, KC_P, KC_RSFT, KC_PGUP, KC_PGDN, LT(10,KC_BSPC), LT(11,KC_DEL), LT(12,KC_ESC), LT(15,KC_ENT), LT(14,KC_TAB), LT(13,KC_SPC), KC_LBRC, KC_RBRC, KC_LEFT, KC_RGHT, KC_DOWN, KC_UP),
	[2] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[4] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[5] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[6] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[7] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[8] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[9] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[10] = LAYOUT_5x6_5(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_NO, KC_NO, RCS(KC_Z), RCS(KC_Y), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_X), KC_BSPC, LCTL(KC_Z), LCTL(KC_Y), KC_DEL, KC_INS, KC_CAPS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, LCTL(KC_C), KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_PSCR, STICKY_LAYER_TOGGLE, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, LCTL(KC_V), KC_HOME, KC_PGUP, KC_PGDN, KC_END, LCTL(KC_H), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, LCTL(KC_L), LCTL(KC_A), SELECT_WORD, LCTL(KC_F), LCTL(KC_G), KC_NO, KC_NO, KC_TRNS, KC_TRNS),
	[11] = LAYOUT_5x6_5(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_TILD, KC_CIRC, KC_HASH, KC_DLR, KC_AT, KC_EXLM, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PERC, KC_7, KC_8, KC_9, KC_COLN, KC_LT, KC_NUM, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_PPLS, KC_4, KC_5, KC_6, KC_PMNS, KC_GT, STICKY_LAYER_TOGGLE, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_PAST, KC_1, KC_2, KC_3, KC_PSLS, KC_PEQL, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_COMM, KC_DOT, KC_0, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_PENT, KC_TAB),
	[12] = LAYOUT_5x6_5(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_EJCT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WHOM, KC_F7, KC_F8, KC_F9, KC_F10, KC_F13, KC_SCRL, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CALC, KC_F4, KC_F5, KC_F6, KC_F11, KC_F14, STICKY_LAYER_TOGGLE, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_MYCM, KC_F1, KC_F2, KC_F3, KC_F12, KC_F15, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_TRNS, KC_TRNS),
	[13] = LAYOUT_5x6_5(KC_TILD, KC_COMM, KC_LPRN, KC_RPRN, KC_SCLN, KC_QUES, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_AT, KC_LCBR, KC_DQUO, KC_QUOT, KC_RCBR, KC_DOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HASH, KC_CIRC, KC_EQL, KC_UNDS, KC_DLR, KC_ASTR, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_EXLM, KC_LT, KC_PIPE, KC_MINS, KC_GT, KC_SLSH, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, STICKY_LAYER_TOGGLE, KC_AMPR, KC_PLUS, KC_BSLS, KC_COLN, KC_PERC, KC_NO, KC_NO, KC_TRNS, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, KC_NO, KC_NO),
	[14] = LAYOUT_5x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_ACL2, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ACL0, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_ACL1, LCTL(KC_RCTL), KC_BTN4, KC_BTN5, KC_NO, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, STICKY_LAYER_TOGGLE, KC_WH_U, KC_WH_D, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO),
	[15] = LAYOUT_5x6_5(KC_PWR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, STICKY_LAYER_TOGGLE, KC_WAKE, KC_SLEP, LALT(KC_PSCR), KC_PAUS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELECT_WORD)) { return false; }
    // Your macros ...

    // handle sticky holding of Miryoku thumb cluster layer-taps as toggles
    if (keycode == STICKY_LAYER_TOGGLE && record->event.pressed) {
        default_layer_set(default_layer_state ? 0 : (1 << get_highest_layer(layer_state)));
    }

    return true;
}

//----------------------------------------------------------------------------
// per-key color indicators for layers and modifiers
//----------------------------------------------------------------------------

void keyboard_post_init_user(void) {
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
    // set initial effect on keyboard start; ignore what's in EEPROM!
    rgb_matrix_mode_noeeprom(
      // RGB_MATRIX_TYPING_HEATMAP
      RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    );

    /*
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators-without-rgb-matrix-effect
    //
    // Indicators without RGB Matrix Effect
    //
    // If you want to just use RGB indicators without RGB matrix effect, it is not
    // possible to disable the latter because toggling RGB off will disable
    // everything. You can workaround it with solid effect and colors off using
    // this init function:
    //
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    // rgb_matrix_sethsv_noeeprom(HSV_OFF); // XXX: this throws away the color!
    HSV hsv = rgb_matrix_get_hsv();
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, 0); // turn off, preserving color
    */
}

// dim indicator colors by this much (default is MAX brightness!)
#define DIM_BY 2
#define DIMMED(rgb_color) DIMMED_(rgb_color)
#define DIMMED_(r, g, b) ((r)/DIM_BY), ((g)/DIM_BY), ((b)/DIM_BY)

#define INDEX_FINGER_COLOR  DIMMED(RGB_YELLOW)
#define MIDDLE_FINGER_COLOR DIMMED(RGB_GREEN)
#define RING_FINGER_COLOR   DIMMED(RGB_CYAN)
#define PINKY_FINGER_COLOR  DIMMED(RGB_MAGENTA)
#define LEFT_THUMB_COLOR    DIMMED(RGB_RED)
#define RIGHT_THUMB_COLOR   DIMMED(RGB_PURPLE)
#define EXTRA_LAYER_COLOR   DIMMED(RGB_BLUE)
#define CAPS_LOCK_COLOR     DIMMED(RGB_BLUE)
#define CAPS_WORD_COLOR     DIMMED(RGB_SPRINGGREEN)

// see ../../../remnant/remnant.c
static const uint8_t
    // { 25, 18, 17,  8,  7,  0 }, // { 29, 36, 37, 46, 47, 54 },
    // { 24, 19, 16,  9,  6,  1 }, // { 30, 35, 38, 45, 48, 53 },
    // { 23, 20, 15, 10,  5,  2 }, // { 31, 34, 39, 44, 49, 52 },
    // { 22, 21, 14, 11,  4,  3 }, // { 32, 33, 40, 43, 50, 51 },
    // { __, __, 13, 12, __, __ }, // { __, __, 41, 42, __, __ },
    // { __, __, __, 26, 27, 28 }, // { 57, 56, 55, __, __, __ }
    LEFT_INDEX_FINGER_HOME   = 7,  RIGHT_INDEX_FINGER_HOME   = 36,
    LEFT_MIDDLE_FINGER_HOME  = 8,  RIGHT_MIDDLE_FINGER_HOME  = 37,
    LEFT_RING_FINGER_HOME    = 17, RIGHT_RING_FINGER_HOME    = 46,
    LEFT_PINKY_FINGER_HOME   = 18, RIGHT_PINKY_FINGER_HOME   = 47,
    LEFT_THUMB_CLUSTER_HOME  = 1,  RIGHT_THUMB_CLUSTER_HOME  = 30,
    LEFT_THUMB_CLUSTER_INNER = 2,  RIGHT_THUMB_CLUSTER_INNER = 31,
    LEFT_THUMB_CLUSTER_OUTER = 3,  RIGHT_THUMB_CLUSTER_OUTER = 32,
    LEFT_CAPS_LOCK           = 0,  RIGHT_CAPS_LOCK           = 29;

// https://docs.qmk.fm/#/feature_caps_word?id=representing-caps-word-state
static bool is_caps_word_active = false;
void caps_word_set_user(bool active) {
  is_caps_word_active = active;
  // TODO: add this to "split transport" payload
}

// https://qmk.github.io/qmk_mkdocs/master/en/feature_rgb_matrix/#indicator-examples
#ifdef VIAL_ENABLE
  void
#else
  bool
#endif
rgb_matrix_indicators_user(void) {

    uint8_t mods = get_mods();

    if (mods & MOD_MASK_SHIFT) {
        rgb_matrix_set_color( LEFT_INDEX_FINGER_HOME, INDEX_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_INDEX_FINGER_HOME, INDEX_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_INDEX_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_INDEX_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_CTRL) {
        rgb_matrix_set_color( LEFT_MIDDLE_FINGER_HOME, MIDDLE_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_MIDDLE_FINGER_HOME, MIDDLE_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_MIDDLE_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_MIDDLE_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_ALT) {
        rgb_matrix_set_color( LEFT_RING_FINGER_HOME, RING_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_RING_FINGER_HOME, RING_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_RING_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_RING_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_GUI) {
        rgb_matrix_set_color( LEFT_PINKY_FINGER_HOME, PINKY_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_PINKY_FINGER_HOME, PINKY_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_PINKY_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_PINKY_FINGER_HOME, RGB_OFF);
    }

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case 10:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 11:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 12:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
            break;

        case 13:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 14:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 15:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RIGHT_THUMB_COLOR);
            break;

        default:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;
    }

    if (IS_LAYER_ON(7)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
    }

    if (IS_LAYER_ON(8)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
    }

    if (host_keyboard_led_state().caps_lock) {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, CAPS_LOCK_COLOR);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, CAPS_LOCK_COLOR);
    }
    else if (is_caps_word_active) {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, CAPS_WORD_COLOR);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, CAPS_WORD_COLOR);
    }
    else {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, RGB_OFF);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, RGB_OFF);
    }

#ifndef VIAL_ENABLE
    return true;
#endif
}
