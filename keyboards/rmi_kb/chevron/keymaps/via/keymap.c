/* Copyright 2021 Ramon Imbao
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                                                                                           KC_VOLD, KC_MUTE, KC_VOLU,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           MO(1),            KC_BSPC,                   KC_RALT, KC_RGUI, KC_RCTL
    ),
    [1] = LAYOUT_all(
                                                                                                           _______, _______, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,          _______,
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    ),
    [2] = LAYOUT_all(
                                                                                                           _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    ),
    [3] = LAYOUT_all(
                                                                                                           _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    ),
};

keyevent_t encoder_ccw = {
    .key = (keypos_t){.row = 4, .col = 0},
    .pressed = false,
    .type = KEY_EVENT
};

keyevent_t encoder_cw = {
    .key = (keypos_t){.row = 4, .col = 1},
    .pressed = false,
    .type = KEY_EVENT
};

void matrix_scan_user(void) {
    if (encoder_ccw.pressed) {
        encoder_ccw.pressed = false;
        encoder_ccw.time = timer_read();
        action_exec(encoder_ccw);
    }

    if (encoder_cw.pressed) {
        encoder_cw.pressed = false;
        encoder_cw.time = timer_read();
        action_exec(encoder_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        encoder_cw.pressed = true;
        encoder_cw.time = timer_read();
        action_exec(encoder_cw);
        wait_ms(20);
    } else {
        encoder_ccw.pressed = true;
        encoder_ccw.time = timer_read();
        action_exec(encoder_ccw);
        wait_ms(20);
    }
    return true;
}
