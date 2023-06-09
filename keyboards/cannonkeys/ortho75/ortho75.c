
#include "quantum.h"

#define MEDIA_KEY_DELAY 10

uint8_t layer = 0;

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    layer = get_highest_layer(state);
    return state;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    uint16_t mapped_code = 0;
    if (index == 0) {
        if (clockwise) {
            switch (layer) {
                case 0:
                default:
                    mapped_code = KC_VOLU;
                    break;
                case 1:
                    mapped_code = KC_MEDIA_NEXT_TRACK;
                    break;
                case 2:
                    mapped_code = KC_PGDN;
                    break;
            }
        } else {
            switch (layer) {
                case 0:
                default:
                    mapped_code = KC_VOLD;
                    break;
                case 1:
                    mapped_code = KC_MEDIA_PREV_TRACK;
                    break;
                case 2:
                    mapped_code = KC_PGUP;
                    break;
            }
        }
        uint16_t held_keycode_timer = timer_read();
        register_code(mapped_code);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) { /* no-op */
        }
        unregister_code(mapped_code);
    }
    return true;
}
