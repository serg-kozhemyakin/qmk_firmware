#include QMK_KEYBOARD_H

#include "print.h"

#include "layers.h"
#include "features/caps_word.h"
#include "features/select_word.h"
#include "features/mouse_turbo_click.h"

static layer_state_t last_used_english_layer = _QWERTY;
static layer_state_t last_used_english_layout = _QWERTY;
static int temporary_switch_off_russian_layer = 0;
static int temporary_switch_off_gaming_layer = 0;

enum custom_keycodes {
    SELECT_WORD = SAFE_RANGE,
    TURBO,
    STICKY_LAYER_TOGGLE,
    T_ENGR, // toggle engram layout on/off
    T_GAME, // toggle gaming layer on/off
};

#define RUS_ENG TG(_RUSSIAN)

// qwerty homerow
#define L_GUI_T LGUI_T(KC_A)
#define L_ALT_T LALT_T(KC_S)
#define L_CTL_T LCTL_T(KC_D)
#define L_SFT_T LSFT_T(KC_F)

#define R_SFT_T RSFT_T(KC_J)
#define R_CTL_T RCTL_T(KC_K)
#define R_ALT_T RALT_T(KC_L)
#define R_GUI_T RGUI_T(KC_SCLN)

// russian homerow
#define LRGUI_T LGUI_T(RU_EF)
#define LRALT_T LALT_T(RU_YERU)
#define LRCTL_T LCTL_T(RU_VE)
#define LRSFT_T LSFT_T(RU_A)

#define RRSFT_T RSFT_T(RU_O)
#define RRCTL_T RCTL_T(RU_EL)
#define RRALT_T RALT_T(RU_DE)
#define RRGUI_T RGUI_T(RU_ZHE)

// engram homerow
#define LEGUI_T LGUI_T(KC_C)
#define LEALT_T LALT_T(KC_I)
#define LECTL_T LCTL_T(KC_E)
#define LESFT_T LSFT_T(KC_A)

#define RESFT_T RGUI_T(KC_H)
#define RECTL_T RALT_T(KC_T)
#define REALT_T RCTL_T(KC_S)
#define REGUI_T RSFT_T(KC_N)

// other layers
#define LT_CURS LT(_CURSOR,KC_BSPC)
#define LT_NUMB LT(_NUMBERS,KC_DEL)
#define LT_FUNC LT(_FKEYS,KC_ESC)
#define LT_SYST LT(_SYS,KC_ENT)
#define LT_MOUS LT(_MOUSE,KC_TAB)
#define LT_SYMB LT(_SYMBOLS,KC_SPC)

#define STLT STICKY_LAYER_TOGGLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_5x6(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
        KC_BSLS, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
        CW_TOGG, L_GUI_T, L_ALT_T, L_CTL_T, L_SFT_T, KC_G   ,          KC_H   , R_SFT_T, R_CTL_T, R_ALT_T, R_GUI_T, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                          KC_PGUP, KC_PGDN,                                              KC_LBRC, KC_RBRC,
                                     LT_CURS, LT_NUMB, LT_FUNC,     LT_SYST, LT_MOUS, LT_SYMB
        ),
	[_ENGRAM] = LAYOUT_5x6(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
        KC_BSLS, KC_B   , KC_Y   , KC_O   , KC_U   , KC_QUOT,          KC_SCLN, KC_L   , KC_D   , KC_W   , KC_V   , KC_Z   ,
        CW_TOGG, LEGUI_T, LEALT_T, LECTL_T, LESFT_T, KC_COMM,          KC_DOT , RESFT_T, RECTL_T, REALT_T, REGUI_T, KC_Q   ,
        KC_LSFT, KC_G   , KC_X   , KC_J   , KC_K   , KC_MINS,          KC_SLSH, KC_R   , KC_M   , KC_F   , KC_P   , KC_RSFT,
                          KC_PGUP, KC_PGDN,                                              KC_LBRC, KC_RBRC,
                                     LT_CURS, LT_NUMB, LT_FUNC,     LT_SYST, LT_MOUS, LT_SYMB
        ),
	[_RUSSIAN] = LAYOUT_5x6(
        RU_HARD, RU_1   , RU_2   , RU_3   , RU_4   , RU_5   ,          RU_6   , RU_7   , RU_8   , RU_9   , RU_0   , RU_MINS,
        RU_BSLS, RU_SHTI, RU_TSE , RU_U   , RU_KA  , RU_IE  ,          RU_EN  , RU_GHE , RU_SHA , RU_SHCH, RU_ZE  , RU_EQL ,
        CW_TOGG, LRGUI_T, LRALT_T, LRCTL_T, LRSFT_T, RU_PE  ,          RU_ER  , RRSFT_T, RRCTL_T, RRALT_T, RRGUI_T, RU_E   ,
        KC_LSFT, RU_YA  , RU_CHE , RU_ES  , RU_EM  , RU_I   ,          RU_TE  , RU_SOFT, RU_BE  , RU_YU  , RU_DOT , KC_RSFT,
                          KC_PGUP, KC_PGDN,                                              RU_YO  , RU_HA  ,
                                     LT_CURS, LT_NUMB, LT_FUNC,     LT_SYST, LT_MOUS, LT_SYMB
        ),
    /*
	[_RUSENGR] = LAYOUT_5x6(
        RU_HARD, RU_1   , RU_2   , RU_3   , RU_4   , RU_5   ,          RU_6   , RU_7   , RU_8   , RU_9   , RU_0   , RU_MINS,
        RU_BSLS, RU_SHTI, RU_TSE , RU_U   , RU_KA  , RU_IE  ,          RU_EN  , RU_GHE , RU_SHA , RU_SHCH, RU_ZE  , RU_EQL ,
        CW_TOGG, LRGUI_T, LRALT_T, LRCTL_T, LRSFT_T, RU_PE  ,          RU_ER  , RRSFT_T, RRCTL_T, RRALT_T, RRGUI_T, RU_E   ,
        KC_LSFT, RU_YA  , RU_CHE , RU_ES  , RU_EM  , RU_I   ,          RU_TE  , RU_SOFT, RU_BE  , RU_YU  , RU_DOT , KC_RSFT,
                          KC_PGUP, KC_PGDN,                                              RU_YO  , RU_HA  ,
                                     LT_CURS, LT_NUMB, LT_FUNC,     LT_SYST, LT_MOUS, LT_SYMB
        ),
     */
	[_CURSOR] = LAYOUT_5x6(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR ,          XXXXXXX   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX   , XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          LCTL(KC_X), KC_BSPC, KC_UP  , KC_DEL , LCTL(KC_Z), KC_INS ,
        XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,          LCTL(KC_C), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_Y), KC_PSCR,
        STLT   , XXXXXXX, XXXXXXX, XXXXXXX, KC_APP , DB_TOGG,          LCTL(KC_V), KC_HOME, KC_PGUP, KC_END , LCTL(KC_F), LCTL(KC_H),
                          XXXXXXX, XXXXXXX,                                                 KC_PGDN, LCTL(KC_G),
                                     _______, XXXXXXX, XXXXXXX,     LCTL(KC_L), LCTL(KC_A), SELECT_WORD
        ),
	[_NUMBERS] = LAYOUT_5x6(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR ,          KC_TILD, KC_CIRC, KC_HASH, KC_DLR, KC_AT  , KC_EXLM,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PERC, KC_7   , KC_8   , KC_9  , KC_COLN, KC_LT,
        KC_NUM , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,          KC_PPLS, KC_4   , KC_5   , KC_6  , KC_PMNS, KC_GT,
        STLT   , XXXXXXX, XXXXXXX, XXXXXXX, KC_APP , DB_TOGG,          KC_PAST, KC_1   , KC_2   , KC_3  , KC_PSLS, KC_PEQL,
                          XXXXXXX, XXXXXXX,                                              KC_LPRN, KC_RPRN,
                                     XXXXXXX, _______, XXXXXXX,     KC_COMM, KC_DOT, KC_0
        ),
	[_FKEYS] = LAYOUT_5x6(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR ,          KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_EJCT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_WHOM, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F13,
        KC_SCRL, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,          KC_CALC, KC_F4  , KC_F5  , KC_F6  , KC_F11 , KC_F14,
        STLT   , XXXXXXX, XXXXXXX, XXXXXXX, KC_APP , DB_TOGG,          KC_MYCM, KC_F1  , KC_F2  , KC_F3  , KC_F12 , KC_F15,
                          XXXXXXX, XXXXXXX,                                              KC_BRID, KC_BRIU,
                                     XXXXXXX, XXXXXXX, _______,     KC_MUTE, KC_VOLD, KC_VOLU
        ),
	[_SYMBOLS] = LAYOUT_5x6(
        KC_TILD, KC_COMM, KC_LPRN, KC_RPRN, KC_SCLN, KC_QUES,          EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        KC_AT  , KC_LCBR, KC_DQUO, KC_QUOT, KC_RCBR, KC_DOT ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_HASH, KC_CIRC, KC_EQL , KC_UNDS, KC_DLR , KC_ASTR,          XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
        KC_EXLM, KC_LT  , KC_PIPE, KC_MINS, KC_GT  , KC_SLSH,          DB_TOGG, KC_APP , XXXXXXX, XXXXXXX, XXXXXXX, STLT   ,
                          KC_AMPR, KC_PLUS,                                              KC_LBRC, KC_RBRC,
                                     KC_BSLS, KC_COLN, KC_PERC,     XXXXXXX, XXXXXXX, _______
        ),
	[_MOUSE] = LAYOUT_5x6(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, KC_ACL2, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ACL0, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,          XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
        XXXXXXX, KC_ACL1, XXXXXXX, KC_BTN4, KC_BTN5, XXXXXXX,          DB_TOGG, KC_APP , XXXXXXX, XXXXXXX, XXXXXXX, STLT   ,
                          KC_WH_U, KC_WH_D,                                              XXXXXXX, XXXXXXX,
                                     KC_BTN1, KC_BTN2, KC_BTN3,     XXXXXXX, _______, XXXXXXX
        ),
	[_SYS] = LAYOUT_5x6(
        KC_PWR , XXXXXXX, XXXXXXX, T_GAME , T_ENGR , RUS_ENG,          EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DB_TOGG, KC_APP , XXXXXXX, XXXXXXX, XXXXXXX, STLT   ,
                          KC_WAKE, KC_SLEP,                                              XXXXXXX, XXXXXXX,
                                     XXXXXXX, KC_PAUS, TURBO,       _______, XXXXXXX, XXXXXXX
        ),
	[_GAMING] = LAYOUT_5x6(
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
        KC_TAB , KC_R   , KC_Q   , KC_W   , KC_E   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
        KC_LSFT, KC_F   , KC_A   , KC_S   , KC_D   , KC_G   ,          KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                          KC_PGUP, KC_PGDN,                                              KC_LBRC, KC_RBRC,
                                     KC_SPC , KC_LALT, LT_FUNC,     LT_SYST, KC_BSPC, LT_SYMB
        ),
};

void switch_system_layout(uint8_t the_layer) {
    if ((IS_LAYER_ON(_RUSSIAN) && the_layer != _RUSSIAN) || (IS_LAYER_OFF(_RUSSIAN) && the_layer == _RUSSIAN)) {
    const uint8_t mods = get_mods() | get_oneshot_mods();
    const bool is_shift_pressed = mods & MOD_MASK_SHIFT;
    if (is_shift_pressed) {
      // here goes the workaround, since Shift+Caps turns Caps on, not switches the language
      unregister_code(KC_LSFT);
      tap_code(KC_CAPS);
      register_code(KC_LSFT);
    } else {
      tap_code(KC_CAPS);
    }
  }
}

/* #define TO_BINARY_PATTERN "%c%c%c%c%c%c Game:%c Sys:%c Mouse:%c Symb:%c Func:%c Numb:%c Curs:%c Russ:%c Engr:%c Qwer:%c" */
/* #define TO_BINARY(byte)  \ */
/* ((byte) & 0x01<<15 ? '1' : '0'), \ */
/* ((byte) & 0x01<<14 ? '1' : '0'), \ */
/* ((byte) & 0x01<<13 ? '1' : '0'), \ */
/* ((byte) & 0x01<<12 ? '1' : '0'), \ */
/* ((byte) & 0x01<<11 ? '1' : '0'), \ */
/* ((byte) & 0x01<<10 ? '1' : '0'), \ */
/* ((byte) & 0x01<<9 ? '1' : '0'), \ */
/* ((byte) & 0x01<<8 ? '1' : '0'), \ */
/* ((byte) & 0x01<<7 ? '1' : '0'), \ */
/* ((byte) & 0x01<<6 ? '1' : '0'), \ */
/* ((byte) & 0x01<<5 ? '1' : '0'), \ */
/* ((byte) & 0x01<<4 ? '1' : '0'), \ */
/* ((byte) & 0x01<<3 ? '1' : '0'), \ */
/* ((byte) & 0x01<<2 ? '1' : '0'), \ */
/* ((byte) & 0x01<<1 ? '1' : '0'), \ */
/* ((byte) & 0x01<<0 ? '1' : '0') */

/* void debug_state(uint16_t keycode, keyrecord_t* record, char* pre, char* post){ */
/*     if (pre!=NULL) dprint(pre); */
/*     dprintf("layer state: "TO_BINARY_PATTERN"\nkeycode: %x[%i]\n", */
/*             TO_BINARY((uint16_t)layer_state), */
/*             keycode, record->event.pressed */
/*             ); */
/*     dprintf("temporary_switch_off_russian_layer = %i\ntemporary_switch_off_gaming_layer = %i\n", */
/*             temporary_switch_off_russian_layer, temporary_switch_off_gaming_layer); */
/*     if (post!=NULL) dprint(post); */
/* } */

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) {
        return false;
    }
    if (!process_select_word(keycode, record, SELECT_WORD)) {
        return false;
    }
    if (!process_mouse_turbo_click(keycode, record, TURBO)) {
        return false;
    }

    switch (keycode) {
    // KC_CAPS change layout from latest used english to russian and back.
    // GAMING is also treated as separate english layout
    case RUS_ENG:
        if (!record->event.pressed) {
            if (IS_LAYER_ON(_RUSSIAN) || temporary_switch_off_russian_layer==1) {
                if (temporary_switch_off_russian_layer==0)
                    switch_system_layout(last_used_english_layer);
                layer_move(last_used_english_layer);
                temporary_switch_off_russian_layer=0;
            } else {
                switch_system_layout(_RUSSIAN);
                layer_move(_RUSSIAN);
            }
        }
        return false;
    case T_GAME:
        if (!record->event.pressed) {
            if (IS_LAYER_ON(_GAMING) || temporary_switch_off_gaming_layer==1 ) {
                if (temporary_switch_off_gaming_layer==0)
                    switch_system_layout(last_used_english_layout);
                layer_move(last_used_english_layout);
                last_used_english_layer=last_used_english_layout;
                temporary_switch_off_gaming_layer=0;
            } else {
                if(temporary_switch_off_russian_layer==1)
                    temporary_switch_off_russian_layer=0;
                switch_system_layout(_GAMING);
                layer_move(_GAMING);
                last_used_english_layer=_GAMING;
            }
        }
        return false;
    case T_ENGR:
        if (!record->event.pressed) {
            if (last_used_english_layer==_QWERTY) {
                switch_system_layout(_ENGRAM);
                last_used_english_layer=_ENGRAM;
                last_used_english_layout=_ENGRAM;
                layer_move(_ENGRAM);
            } else {
                switch_system_layout(_QWERTY);
                last_used_english_layer=_QWERTY;
                last_used_english_layout=_QWERTY;
                layer_move(_QWERTY);
            }
        }
        return false;
    }

    if (IS_LAYER_ON(_RUSSIAN) || temporary_switch_off_russian_layer==1 ||
            IS_LAYER_ON(_GAMING) || temporary_switch_off_gaming_layer==1) {
        int switch_layer = 0;
        switch (keycode) {
        case LT_CURS:
        case LT_FUNC:
        case LT_MOUS:
        case LT_NUMB:
        case LT_SYMB:
        case LT_SYST:
            switch_layer=1;
            break;
            /* default: */
            /*     const uint8_t mods = get_mods() | get_oneshot_mods(); */
            /*     if(mods & MOD_MASK_ALT || mods & MOD_MASK_CTRL || mods & MOD_MASK_GUI) { */
            /*         switch_to_english=1; */
            /*     } */
            /*     break; */
        }
        if (switch_layer) {
            if (record->event.pressed) {
                if (IS_LAYER_ON(_RUSSIAN)) {
                    switch_system_layout(last_used_english_layer);
                    layer_off(_RUSSIAN);
                    layer_on(last_used_english_layer);
                    temporary_switch_off_russian_layer=1;
                }
                if (IS_LAYER_ON(_GAMING)) {
                    layer_off(_GAMING);
                    layer_on(last_used_english_layout);
                    temporary_switch_off_gaming_layer=1;
                }
            } else {
                if (temporary_switch_off_russian_layer==1) {
                    switch_system_layout(_RUSSIAN);
                    layer_on(_RUSSIAN);
                    layer_off(last_used_english_layer);
                    temporary_switch_off_russian_layer=0;
                }
                if(temporary_switch_off_gaming_layer==1) {
                    layer_on(_GAMING);
                    layer_off(last_used_english_layout);
                    temporary_switch_off_gaming_layer=0;
                }
            }
        }
    }

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
    // Customise these values to desired behaviour
    /* debug_enable=true; */
    /* debug_matrix=true; */
    /* debug_keyboard=true; */
    //debug_mouse=true;

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
bool rgb_matrix_indicators_user(void) {

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
    case _CURSOR:
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
        break;

    case _NUMBERS:
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
        break;

    case _FKEYS:
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
        break;

    case _SYMBOLS:
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
        break;

    case _MOUSE:
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
        break;

    case _SYS:
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

    if (IS_LAYER_ON(_ENGRAM)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
    }

    if (IS_LAYER_ON(_RUSSIAN)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
    }

    if (IS_LAYER_ON(_GAMING)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, EXTRA_LAYER_COLOR);
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

    return true;
}
