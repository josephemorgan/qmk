#include <stdint.h>
#include <stdlib.h>
#include "action_util.h"
#include "config.h"
#include "keyboard.h"
#include "keycode_config.h"
#include "keycodes.h"
#include "modifiers.h"
#include "../../../../../users/jemorgan/oled.h"
#include "oled_driver.h"
#include "../../../../../users/jemorgan/buffer.h"
#include "keymap.h"
#include "quantum.h"
#include "./secrets.h"
#include QMK_KEYBOARD_H

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

struct buffer *keyboard_buffer = NULL;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                 KC_Y,         KC_U,         KC_I,         KC_O,      KC_P,        KC_TAB,
        KC_ESC,         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                                                                 KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,     KC_ENT,
        OSM(MOD_LSFT),       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,        LOWER,       FUNCTION,     FUNCTION,        RAISE,       KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,     OSM(MOD_RSFT),
        MO(_ADJUST),  OSM(MOD_LALT),     OSM(MOD_LGUI),     KC_SPC,      OSM(MOD_LCTL),      OSM(MOD_RCTL),     KC_BSPC,     OSM(MOD_RGUI),     OSM(MOD_RALT),        QK_LEAD
    ),
    [_GAME] = LAYOUT(
        _______, _______, _______,     _______, _______, _______,                                                _______, _______, _______, _______, _______, _______,
        _______, _______, _______,     _______, _______, _______,                                                _______, _______, _______, _______, _______, _______,
        KC_LSFT, _______, _______,     _______, _______, _______, MO(_NUMBER), MO(_FUNCTION),  _______, _______, _______, _______, _______, _______, _______, _______,
        MO(_ADJUST), KC_LALT,   KC_F6,     _______,       KC_LCTL,  _______, _______, _______, _______, _______
    ),
    [_SYMBOL] = LAYOUT(
        _______, LSFT(KC_1),   LSFT(KC_2),   LSFT(KC_3),   LSFT(KC_4),   LSFT(KC_5),                                                         LSFT(KC_6),   LSFT(KC_7),   LSFT(KC_8),   LSFT(KC_9),   LSFT(KC_0),       LSFT(KC_EQL),
        CWT,     _______,      _______,      _______,      _______,      _______,                                                            KC_LEFT,      KC_DOWN,        KC_UP,     KC_RIGHT,      KC_QUOTE, KC_EQL,
        _______, _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,    _______,    _______,    _______,      _______,       _ARROW,      KC_BSLS,      LSFT(KC_BSLS),
        _______,      _______,      _______,      _______,      _______,      _______,    _______,    _______,      _______,      _______
    ),
    [_NUMBER] = LAYOUT(
        KC_INS,      KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
        _______,   KC_MINS,   LCURL, KC_LPRN, KC_RPRN,  RCURL,                                          _______, _______, _______, _______, _______,  KC_EQL,
        CWT, CK_UNDRSC, KC_PLUS, KC_LBRC, KC_RBRC, KC_EQL,  _______, _______,     _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
    [_FUNCTION] = LAYOUT(
        _______,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,                                                                KC_F6,        KC_F7,        KC_F8,        KC_F9,       KC_F10,      _______,
        _______,       KC_F11,       KC_F12,       KC_F13,       KC_F14,       KC_F15,                                                               KC_F16,       KC_F17,       KC_F18,       KC_F19,       KC_F20,      _______,
        _______,       KC_F21,       KC_F22,       KC_F23,       KC_F24,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,
        _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
    ),
    [_ADJUST] = LAYOUT(
        _______, LCAG(KC_1), LCAG(KC_2), LCAG(KC_3), LCAG(KC_4), LCAG(KC_5),                                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______,    _______, _______,  _______, RGB_MODE_FORWARD, RGB_MODE_REVERSE, _______, _______, _______,
        _______, TG(_GAME), DF(_QWERTY), OS_TOGG, _______,                                      QK_LEAD, _______, _______, _______, _______
    ),
    [_TRANS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
    )
};
// clang-format on

void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_P, KC_W)) {
        SEND_STRING(WORK_PASS);
    }
    if (leader_sequence_two_keys(KC_P, KC_F)) {
        SEND_STRING(L_PASS);
    }
    if (leader_sequence_two_keys(KC_P, KC_B)) {
        SEND_STRING(BITWARDEN_PASS);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    try_render_oled();
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_GAME)) {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
        }
    } else if (index == 1) {
        if (IS_LAYER_ON(_ADJUST)) {
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
            } else if (get_mods() & MOD_BIT(KC_LALT)) {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
            } else {
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
            }
        } else {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
        }
    }
    return false;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 600) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode >= 0xe0 && keycode <= 0xe7) {
            add_keycode_to_buffer(keyboard_buffer, keycode);
        } else if (keycode >= KC_F1 && keycode <= KC_F12) {
            add_char_to_buffer(keyboard_buffer, 'F');
            add_char_to_buffer(keyboard_buffer, '1' + keycode - KC_F1);
        }
    } else {
        if (IS_QK_BASIC(keycode) && (keycode < 0xe0 || keycode > 0xe7)) {
            add_keycode_to_buffer(keyboard_buffer, keycode);
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    keyboard_buffer = create_empty_buffer();
    init(keyboard_buffer);
}
