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
#include QMK_KEYBOARD_H
#include <stdio.h>


enum layers {
    _QWERTY = 0,
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

bool lighting_enabled = true;

// produces the key `tap` when tapped (i.e. pressed and released).
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
      KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                 KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,      KC_MINS,
      KC_ESC,         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                                                                 KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,     KC_QUOTE,
     KC_LSFT,         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,        LOWER,       FUNCTION,     FUNCTION,        RAISE,         KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,    RSFT_BSLS,
                                                ADJUST,      KC_LALT,      KC_LGUI,       KC_SPC,      CTL_TAB,      CTL_ENT,      KC_BSPC,      KC_RGUI,      KC_RALT,       KC_APP
),
[_NUMBER] = LAYOUT(
      KC_INS,         KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,       KC_DEL,
     _______,      _______,        LCURL,      KC_LPRN,      KC_RPRN,        RCURL,                                                              _______,      _______,      _______,      _______,      _______,       KC_EQL,
     _______,      _______,      _______,      KC_LBRC,      KC_RBRC,       KC_EQL,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_BSLS,      _______,
                                               _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
),
[_SYMBOL] = LAYOUT(
     _______,   LSFT(KC_1),   LSFT(KC_2),   LSFT(KC_3),   LSFT(KC_4),   LSFT(KC_5),                                                           LSFT(KC_6),   LSFT(KC_7),   LSFT(KC_8),   LSFT(KC_9),   LSFT(KC_0),       KC_EQL,
     _______,      _______,      _______,      _______,      _______,      _______,                                                              KC_LEFT,      KC_DOWN,        KC_UP,     KC_RIGHT,      _______, LSFT(KC_EQL),
     _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_HOME,      KC_PGDN,      KC_PGUP,       KC_END,      _______,      KC_BSLS,
                                               _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
),
[_FUNCTION] = LAYOUT(
     _______,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,                                                                KC_F6,        KC_F7,        KC_F8,        KC_F9,       KC_F10,      _______,
     _______,       KC_F11,       KC_F12,       KC_F13,       KC_F14,       KC_F15,                                                               KC_F16,       KC_F17,       KC_F18,       KC_F19,       KC_F20,      _______,
     _______,       KC_F21,       KC_F22,       KC_F23,       KC_F24,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,
                                               _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
)
[_ADJUST] = LAYOUT(
-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,
-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,
-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,-------,
-------,-------,-------,-------,-------,-------,-------,-------,-------,      _______
)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
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
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        if (clockwise) {
            tap_code16(KC_TAB);
        } else {
            tap_code16(LSFT(KC_TAB));
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code16(KC_PGDN);
        } else {
            tap_code16(KC_PGUP);
        }
    }
    return false;
}
#endif
