#ifndef _JEMORGAN_KEYMAP_H
#define _JEMORGAN_KEYMAP_H

#include <stddef.h>
#include "oled_driver.h"
#include "quantum_keycodes.h"

#define RAISE OSL(_NUMBER)
#define LOWER OSL(_SYMBOL)
#define FUNCTION OSL(_FUNCTION)
#define CWT QK_CAPS_WORD_TOGGLE
#define CK_UNDRSC LSFT(KC_MINS)

#define LCURL LSFT(KC_LBRC)
#define RCURL LSFT(KC_RBRC)


enum layers {
    _QWERTY = 0,
    _GAME,
    _SYMBOL,
    _NUMBER,
    _FUNCTION,
    _ADJUST,
    _TRANS
};

enum custom_keycodes {
    _ARROW = SAFE_RANGE
};

#endif // !_KEYMAP_H_
