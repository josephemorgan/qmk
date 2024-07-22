#ifndef _MORGANJ_KEYMAP_H
#define _MORGANJ_KEYMAP_H

#include "action_layer.h"
#include "buffer.h"

struct oled_state {
    uint16_t active_layers_and_mods;
    struct buffer* keypress_buffer;
};

void init(struct buffer*);
void destroy(void);
void try_render_oled(void);
uint16_t gen_active_layers_and_mods(void);

#endif
