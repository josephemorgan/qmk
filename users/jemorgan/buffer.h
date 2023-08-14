#ifndef _buffer_h_
#include <stdint.h>
#include "./utilities.h"

struct node {
    char data;
    struct node *next;
    struct node *previous;
};

struct buffer {
    struct node *head;
    struct node *tail;
    uint8_t length;
    uint8_t max_length;
};

struct buffer * const create_empty_buffer(void);
struct buffer * const create_buffer_with_char(const char);
struct buffer * const add_char_to_buffer(struct buffer*, const char);
struct buffer * const add_keycode_to_buffer(struct buffer*, uint16_t);
size_t get_buffer_as_string(const struct buffer*, char *);
void free_buffer(const struct buffer*);

#endif // !_buffer_h_
