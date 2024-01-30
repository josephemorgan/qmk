/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 * Copyright 2023 Joseph Morgan <j@jemorgan.dev>
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
#include <stdint.h>
#include <stdlib.h>
#include "action_util.h"
#include "config.h"
#include "keyboard.h"
#include "keycodes.h"
#include "modifiers.h"
#include "keymap.h"
#include "oled_driver.h"
#include "../../../../../users/jemorgan/buffer.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

#define RAISE MO(_NUMBER)
#define LOWER MO(_SYMBOL)
#define FUNCTION MO(_FUNCTION)

#define CTL_TAB MT(MOD_LCTL, KC_TAB)
#define CTL_ENT MT(MOD_RCTL, KC_ENT)
#define RSFT_BSLS MT(MOD_RSFT, KC_BSLS)
#define LCURL LSFT(KC_LBRC)
#define RCURL LSFT(KC_RBRC)

enum layers {
    _QWERTY = 0,
    _GAME,
    _NUMBER,
    _SYMBOL,
    _FUNCTION,
    _ADJUST
};

enum custom_keycodes {
    CAPSWORD = SAFE_RANGE,
    SNAKECASE,
    KVM_INPUT_ONE,
    KVM_INPUT_TWO,
    KVM_TOGGLE_MOUSE,
    KVM_TOGGLE_KEYBOARD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                 KC_Y,         KC_U,         KC_I,         KC_O,      KC_P,        KC_MINS,
            KC_ESC,         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                                                                 KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,     KC_QUOTE,
            MOD_LSFT,       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,        LOWER,       FUNCTION,     FUNCTION,        RAISE,       KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,     OSM(MOD_RSFT),
                                                        MO(_ADJUST),  MOD_LALT,     MOD_LGUI,     KC_SPC,      CTL_TAB,      CTL_ENT,     KC_BSPC,     MOD_RGUI,     MOD_RALT,        MO(_ADJUST)
            ),
    [_GAME] = LAYOUT(
            KC_ESC,  KC_LALT, KC_W, KC_E,      KC_R,  KC_T,                                                                 KC_Y,         KC_U,         KC_I,         KC_O,      KC_P,        KC_MINS,
            KC_TAB,  KC_LSFT, KC_S, KC_D,      KC_F,  KC_G,                                                                 KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,     KC_QUOTE,
            KC_HOME, KC_LCTL, KC_X, KC_C,      KC_V,  KC_B,  KC_F3,  KC_F4,             FUNCTION, RAISE,   KC_N,     KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,     OSM(MOD_RSFT),
                                    TG(_GAME), KC_F1, KC_F2, KC_SPC, CTL_TAB,           CTL_ENT,  KC_BSPC, MOD_RGUI, MOD_RALT,        MO(_ADJUST)
            ),
    [_SYMBOL] = LAYOUT(
            _______,   LSFT(KC_1),   LSFT(KC_2),   LSFT(KC_3),   LSFT(KC_4),   LSFT(KC_5),                                                           LSFT(KC_6),   LSFT(KC_7),   LSFT(KC_8),   LSFT(KC_9),   LSFT(KC_0),       KC_EQL,
            QK_CAPS_WORD_TOGGLE, _______,      _______,      _______,      _______,      _______,                                                              KC_LEFT,      KC_DOWN,        KC_UP,     KC_RIGHT,      _______, LSFT(KC_EQL),
            _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_HOME,      KC_PGDN,      KC_PGUP,       KC_END,      _______,      KC_BSLS,
            _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______
            ),
    [_NUMBER] = LAYOUT(
            KC_INS,         KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,       KC_DEL,
            _______, _______,        LCURL,      KC_LPRN,      KC_RPRN,        RCURL,                                                              _______,      _______,      _______,      _______,      _______,       KC_EQL,
            QK_CAPS_WORD_TOGGLE,      _______,      _______,      KC_LBRC,      KC_RBRC,       KC_EQL,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_BSLS,      _______,
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
            _______, TG(_GAME), DF(_QWERTY), _______, _______,                                      _______, _______, _______, _______, _______
            ),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    render_keyboard_state();
    return false;
}

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_NUMBER)) {
            if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_R);
                unregister_code(KC_LCTL);
            } else {
                tap_code(KC_U);
            }
        } else {
            if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_I);
                unregister_code(KC_LCTL);
            } else {
                register_code(KC_LCTL);
                tap_code(KC_O);
                unregister_code(KC_LCTL);
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

struct buffer *keyboard_buffer = NULL;
char *buffer_as_string = NULL;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode >= 0xe0 && keycode <= 0xe7) {
            add_keycode_to_buffer(keyboard_buffer, keycode);
        }

        switch (keycode) {
            case KVM_INPUT_ONE:
                if (record->event.pressed) {
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_1);
                    tap_code(KC_ENT);
                }
                break;
            case KVM_INPUT_TWO:
                if (record->event.pressed) {
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_2);
                    tap_code(KC_ENT);
                }
                break;
            case KVM_TOGGLE_KEYBOARD:
                if (record->event.pressed) {
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_K);
                    tap_code(KC_ENT);
                }
                break;
            case KVM_TOGGLE_MOUSE:
                if (record->event.pressed) {
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_RIGHT_CTRL);
                    tap_code(KC_M);
                    tap_code(KC_ENT);
                }
                break;
        }

    } else {
        if (IS_QK_BASIC(keycode) && (keycode < 0xe0 || keycode > 0xe7)) {
            add_keycode_to_buffer(keyboard_buffer, keycode);
        }
    }
    get_buffer_as_string(keyboard_buffer, buffer_as_string);
    return true;
}

void keyboard_post_init_user(void) {
    keyboard_buffer = create_empty_buffer();
    buffer_as_string = malloc(sizeof(char) * keyboard_buffer->max_length + 1);
}

void render_keyboard_state(void) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_ln("     Layer: Base    ", false);
            break;
        case _GAME:
            oled_write_ln("    Layer: Game     ", false);
            break;
        case _NUMBER:
            oled_write_ln("    Layer: Number   ", false);
            break;
        case _SYMBOL:
            oled_write_ln("    Layer: Symbol   ", false);
            break;
        case _FUNCTION:
            oled_write_ln("   Layer: Function  ", false);
            break;
        case _ADJUST:
            oled_write_ln("    Layer: Adjust   ", false);
            break;
        default:
            oled_write_ln("  Layer: Undefined  ", false);
    }

    oled_advance_page(true);

    oled_advance_char_count(1);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        oled_write("CTRL", true);
    } else {
        oled_write("CTRL", false);
    }

    oled_advance_char_count(4);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT) {
        oled_write("ALT", true);
    } else {
        oled_write("ALT", false);
    }


    oled_advance_char_count(4);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI) {
        oled_write("GUI", true);
    } else {
        oled_write("GUI", false);
    }

    oled_advance_page(false);
    oled_advance_char_count(8);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        oled_write_ln("SHIFT", true);
    } else {
        oled_write_ln("SHIFT", false);
    }
    if (keyboard_buffer->head) {
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_write(buffer_as_string, false);
        //struct node *current_node = keyboard_buffer->tail;
        //do {
        //    oled_write_char(current_node->data, false);
        //    current_node = current_node->next;
        //} while (current_node);
    }
}
