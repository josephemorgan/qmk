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
#include "./ocean_animation.h"


enum layers {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _FUNCTION,
    _ADJUST
};

enum custom_keycodes {
    CAPSWORD = SAFE_RANGE,
    SNAKECASE
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define FUNCTION MO(_FUNCTION)
#define ADJUST MO(_ADJUST)

#define CTL_TAB MT(MOD_LCTL, KC_TAB)
#define CTL_ENT MT(MOD_RCTL, KC_ENT)

bool lighting_enabled = true;

// produces the key `tap` when tapped (i.e. pressed and released).
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            KC_GRV,   KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                      KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_MINS,
            KC_ESC, KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                      KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,KC_QUOTE,
            KC_LSFT, KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , LOWER, ADJUST,      FUNCTION, RAISE, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, MT(MOD_RSFT, KC_BSLS),
            ADJUST , KC_LALT, KC_LGUI, KC_SPC, CTL_TAB,     CTL_ENT, KC_BSPC, KC_RGUI, KC_RALT, KC_APP
            ),

    [_LOWER] = LAYOUT(
            _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                        LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_EQL, 
            _______, _______,    _______,    LSFT(KC_LBRC), LSFT(KC_RBRC), _______,                                      KC_LEFT,    KC_DOWN, KC_UP, KC_RIGHT, _______, LSFT(KC_EQL),
            _______, _______,    _______,    _______,    _______,    _______, _______, _______,   _______, _______, KC_HOME,    KC_PGDN, KC_PGUP, KC_END, LSFT(KC_BSLS), KC_BSLS,
            _______,    _______,    _______, _______, _______,   _______, _______, _______,    _______, _______
            ),

    [_RAISE] = LAYOUT(
            KC_INS,   KC_1 ,  KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,                 KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_DEL,
            _______, _______, LSFT(KC_LBRC), KC_LPRN, KC_RPRN, LSFT(KC_RBRC),                             _______, _______, _______, _______, _______, KC_EQL,
            _______, _______, _______,       KC_LBRC, KC_RBRC, KC_EQL,       _______, _______, _______, _______, _______, _______,        _______, _______, KC_BSLS, LSFT(KC_BSLS),
            _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______
            ),

    [_FUNCTION] = LAYOUT(
            _______,  KC_F1 ,  KC_F2,   KC_F3,   KC_F4,  KC_F5,                                       KC_F6,  KC_F7,    KC_F8,   KC_F9,   KC_F10, _______,
            _______,  KC_F11,  KC_F12,  KC_F13,  KC_F14, KC_F15,                                      KC_F16,  KC_F17,  KC_F18,  KC_F19, KC_F20, _______,
            _______,  KC_F21,  KC_F22,  KC_F23,  KC_F24, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
            ),

    [_ADJUST] = LAYOUT(
            _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
            _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
            _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
            _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
            ),

};

uint32_t oled_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_timer = timer_read32();
    return true;
}

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap._______c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

#define ANIMATION_FRAME_DURATION 1500
#define OLED_TIMEOUT_MS 30000
static uint32_t animation_timer = 0;
static int frame = 0;

void render_slave_animation(void) {
    if (timer_elapsed32(animation_timer) > ANIMATION_FRAME_DURATION) {
        ++frame;
        frame %= OCEAN_ANIMATION_FRAMES;
        animation_timer = timer_read32();
    }
    oled_write_raw_P(ocean_animation[frame], sizeof(ocean_animation[frame]));
}

void render_master_animation(void) {
    if (timer_elapsed32(animation_timer) > ANIMATION_FRAME_DURATION) {
        ++frame;
        frame %= OCEAN_ANIMATION_FRAMES;
        animation_timer = timer_read32();
    }
    oled_write_raw_P(ocean_animation[frame + 2], sizeof(ocean_animation[frame]));
}

bool oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT_MS) {
        oled_off();
        return false;
    }

    if (animation_timer == 0)
        animation_timer = timer_read();

    if (is_keyboard_master()) {
        if (lighting_enabled)
            render_master_animation();
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
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
        render_slave_animation();
        oled_set_cursor(0, 0);
        char wpm_str[10];
        sprintf(wpm_str, "Words/Minute:%03d", get_current_wpm());
        oled_write(wpm_str, false);
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code16(KC_TAB);
        } else {
            tap_code16(LSFT(KC_TAB));
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code16(KC_PGDN);
        } else {
            tap_code16(KC_PGUP);
        }
    }
    return false;
}
#endif
