/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "matrix.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include <stdio.h>


enum layers {
    _QWERTY = 0,
    _BLOCK_OSM,
    _NUMBER,
    _SYMBOL,
    _FUNCTION,
    _ADJUST
};

enum custom_keycodes {
    CAPSWORD = SAFE_RANGE,
    SNAKECASE
};

#define RAISE MO(_NUMBER)
#define LOWER MO(_SYMBOL)
#define FUNCTION MO(_FUNCTION)

#define CTL_TAB MT(MOD_LCTL, KC_TAB)
#define CTL_ENT MT(MOD_RCTL, KC_ENT)
#define RSFT_BSLS MT(MOD_RSFT, KC_BSLS)
#define LCURL LSFT(KC_LBRC)
#define RCURL LSFT(KC_RBRC)

// produces the key `tap` when tapped (i.e. pressed and released).
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                 KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,      KC_MINS,
            KC_ESC,         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                                                                 KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,     KC_QUOTE,
            OSM(MOD_LSFT),  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,        LOWER,       FUNCTION,     FUNCTION,        RAISE,       KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,    OSM(MOD_RSFT),
            MO(_ADJUST),      KC_LALT,      KC_LGUI,       KC_SPC,        CTL_TAB,      CTL_ENT,      KC_BSPC,    KC_RGUI,      KC_RALT,      MO(_ADJUST) 
            ),
    [_BLOCK_OSM] = LAYOUT(
            _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
            KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT,
            _______, KC_LALT, KC_LGUI, _______, _______, _______, _______, KC_RGUI, KC_RALT, _______
            ),
    [_SYMBOL] = LAYOUT(
            _______,   LSFT(KC_1),   LSFT(KC_2),   LSFT(KC_3),   LSFT(KC_4),   LSFT(KC_5),                                                           LSFT(KC_6),   LSFT(KC_7),   LSFT(KC_8),   LSFT(KC_9),   LSFT(KC_0),       KC_EQL,
            QK_CAPS_WORD_TOGGLE, _______,      _______,      _______,      _______,      _______,                                                              KC_LEFT,      KC_DOWN,        KC_UP,     KC_RIGHT,      _______, LSFT(KC_EQL),
            _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_HOME,      KC_PGDN,      KC_PGUP,       KC_END,      _______,      KC_BSLS,
            _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
            ),
    [_NUMBER] = LAYOUT(
            KC_INS,         KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,       KC_DEL,
            QK_CAPS_WORD_TOGGLE, _______,        LCURL,      KC_LPRN,      KC_RPRN,        RCURL,                                                              _______,      _______,      _______,      _______,      _______,       KC_EQL,
            _______,      _______,      _______,      KC_LBRC,      KC_RBRC,       KC_EQL,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_BSLS,      _______,
            _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
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
            _______, _______, _______, _______, TG(_BLOCK_OSM),    _______, _______,  _______, _______, _______
            ),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case _BLOCK_OSM:
                oled_write_P(PSTR("Block OSM\n"), false);
                break;
            case _NUMBER:
                oled_write_P(PSTR("Number\n"), false);
                break;
            case _SYMBOL:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
    } else {
        char wpm_str[32];
        sprintf(wpm_str, "Words/Minute:%03d", get_current_wpm());
        oled_write(wpm_str, false);
    }
    return false;
}

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_NUMBER)) {
            if (clockwise) {
                register_code(KC_LSFT);
                tap_code(KC_R);
                unregister_code(KC_LSFT);
            } else {
                tap_code(KC_U);
            }
        } else {
            if (clockwise) {
                tap_code(KC_MS_BTN4);
            } else {
                tap_code16(KC_MS_BTN5);
            }
        }
    } else if (index == 1) {
        if (IS_LAYER_ON(_ADJUST)) {
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
        } else {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(LSFT(KC_TAB));
            }
        }
    }
    return false;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
