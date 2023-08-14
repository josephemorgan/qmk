#include <stddef.h>
#include "oled_driver.h"
#ifndef _KEYMAP_H_

void render_keyboard_state(void);
void oled_advance_char_count(size_t count) {
    for (size_t i = 0; i < count; ++i) {
        oled_advance_char();
    }
}

#endif // !_KEYMAP_H_
