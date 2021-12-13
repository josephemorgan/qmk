#include "/home/joe/dev/qmk_firmware/keyboards/ergodox_ez/ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "stdlib.h"
#include "print.h"

enum  {
	// Base layers
	_QWER,
	_GAME,
	// Overlay layers
	_RAISE,
	_LOWER,
	_ADJUST,
	TEMPLATE
};

enum custom_keycodes {
	KC_OSTREAM = SAFE_RANGE,
	KC_ISTREAM,
	KC_CPP_ARROW,
	KC_QMKINFO,
	KC_CLEAR_KEYBOARD
};

int RANDOM_SEEDED = 0;

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWER] = LAYOUT_ergodox(
			// Left Hand
			KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,KC_DEL,
			KC_EQUAL,KC_Q,KC_W,KC_E,KC_R,KC_T,RAISE,
			KC_ESCAPE,KC_A,KC_S,KC_D,KC_F,KC_G,
			OSM(MOD_LSFT),KC_Z,KC_X,KC_C,KC_V,KC_B,LOWER,
			KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,

			KC_LGUI,LCTL(KC_LALT),
			KC_LALT,
			KC_SPACE,KC_TAB,KC_LCTL,


			// Right Hand
			KC_INSERT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_CAPSLOCK,
			RAISE,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_MINUS,
			KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,
			LOWER,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_BSLASH,
			KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,

			LCTL(KC_LALT),KC_RGUI,
			KC_RALT,
			OSL(_RAISE),KC_BSPACE,KC_ENTER
				),

	[_RAISE] = LAYOUT_ergodox(
			// Left Hand - Function Keys
			_______,_______,_______,_______,_______,_______,RESET,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			KC_F11,KC_F12,KC_F13,KC_F14,KC_F15,

			_______,_______,
			_______,
			_______,_______,_______,


			// Right Hand - Arrow Keys
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,_______,_______,
			_______,KC_PGDN,KC_PGUP,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,_______,_______,
			KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,_______,_______,

			_______,_______,
			_______,
			_______,_______,_______
				),

	[_LOWER] = LAYOUT_ergodox(
			// Left Hand - Common Programming Keys
			_______,KC_F20,KC_F21,KC_F22,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,_______,
			_______,KC_OSTREAM,KC_ISTREAM,LSFT(KC_LBRC),LSFT(KC_RBRC),LSFT(KC_8),_______,
			_______,KC_AMPR,LSFT(KC_BSLASH),LSFT(KC_9),LSFT(KC_0),KC_BSLASH,
			_______,_______,KC_CPP_ARROW,KC_LBRC,KC_RBRC,KC_MINUS,_______,
			_______,_______,_______,LSFT(KC_COMMA),LSFT(KC_DOT),

			_______,_______,
			_______,
			KC_SPACE,KC_TAB,_______,


			// Right Hand - Numpad
			_______,KC_MEDIA_PREV_TRACK,KC_MEDIA_PREV_TRACK,KC_F8,KC_F9,KC_F10,KC_F11,
			_______,LSFT(KC_EQL),KC_7,KC_8,KC_9,KC_ASTR,KC_F12,
			KC_MINUS,KC_4,KC_5,KC_6,KC_SLASH,_______,
			_______,KC_AMPR,KC_1,KC_2,KC_3,KC_BSLASH,KC_COMMA,
			KC_0,KC_0,KC_DOT,KC_EQUAL,KC_QMKINFO,

			_______,_______,
			_______,
			_______,KC_BSPACE,KC_ENTER
				),

	[_ADJUST] = LAYOUT_ergodox(
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,

			_______,_______,
			_______,
			_______,_______,_______,

			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			TG(_GAME),_______,_______,_______,_______,

			_______,_______,
			_______,
			_______,_______,_______
			),


	[_GAME] = LAYOUT_ergodox(
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,KC_SCOLON,
			_______,_______,_______,_______,_______,_______,
			KC_LSHIFT,_______,_______,_______,_______,_______,KC_BSLASH,
			_______,_______,_______,_______,_______,

			_______,KC_NO,
			KC_LALT,
			_______, _______, KC_LCTRL,

			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			TG(_GAME),_______,_______,_______,_______,

			KC_NO, KC_NO,
			_______,
			_______,KC_BSPACE,_______
			),

	[TEMPLATE] = LAYOUT_ergodox(
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,

			_______,_______,
			_______,
			_______,_______,_______,

			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,_______,_______,
			_______,_______,_______,_______,_______,

			_______,_______,
			_______,
			_______,_______,_______
			),
};

void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot mods GUI");
  }
  if (!mods) {
    println("Oneshot mods off");
  }
}

void oneshot_layer_changed_user(uint8_t layer) {
	if (layer == _LOWER) {
		print("Oneshot Layer LOWER active\n");
	} else if (layer == _RAISE) {
		print("Oneshot Layer RAISE active\n");
	} else if (!layer) {
		print("Oneshot layer off\n");
	}
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
	if (keycode == 21506) {
		if (record->event.pressed) {
			uprintf("Depressed Layer Key\n");
		} else {
			uprintf("Released Layer Key\n");
		}
	} else if (keycode == 21761) {
		if (record->event.pressed) {
			uprintf("Depressed OSM CTRL Key\n");
		} else {
			uprintf("Released OSM CTRL Key\n");
		}
	} else {
		if (record->event.pressed) {
			uprintf("Depressed Keycode %d\n", keycode);
		} else {
			uprintf("Released Keycode %d\n", keycode);
		}
	}
	switch (keycode) {
	case KC_OSTREAM:
		if (record->event.pressed) {
			SEND_STRING("<<");
		} else {}
		break;
	case KC_ISTREAM:
		if (record->event.pressed) {
			SEND_STRING(">>");
		} else {}
		break;
	case KC_CPP_ARROW:
		if (record->event.pressed) {
			SEND_STRING("->");
		} else {}
		break;
	case KC_QMKINFO:
		if (record->event.pressed) {
			SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
		}
	case KC_CLEAR_KEYBOARD:
		if (record->event.pressed) {
			clear_keyboard();
		}
	}
	return true;
}

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch(id) {
	case 0:
		if (record->event.pressed) {
			SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
		}
		break;
	}
	return MACRO_NONE;
};

void generate_12_char_password(char* password)
{
	if (!RANDOM_SEEDED) {
		srand(TCNT0);
		RANDOM_SEEDED = 1;
	}

	for (int i = 0; i < 12; ++i) {
		password[i] = (rand() % 90) + 33;
	}

	password[13] = '\0';
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		leading = false;
		leader_end();

		SEQ_ONE_KEY(KC_R) {
			char password[13];
			generate_12_char_password(password);
			send_string(password);
		}
		// Username
		SEQ_TWO_KEYS(KC_U, KC_G) {
			SEND_STRING("josephemorgan91");
		}

		SEQ_TWO_KEYS(KC_U, KC_S) {
			SEND_STRING("josephmorgan");
		}

		// Email
		SEQ_TWO_KEYS(KC_E, KC_G) {
			SEND_STRING("josephemorgan91@gmail.com");
		}

		SEQ_TWO_KEYS(KC_E, KC_P) {
			SEND_STRING("jm@josephmorgan.net");
		}

		SEQ_TWO_KEYS(KC_P, KC_F) {
			SEND_STRING("f1reandbl00d");
		}

		SEQ_TWO_KEYS(KC_P, KC_S) {
			SEND_STRING("Pollyanna75.");
		}

		// Clear all modifiers and held keys
		SEQ_ONE_KEY(KC_C) {
			clear_keyboard();
		}
	}
}

void keyboard_post_init_user(void) {
	debug_enable = true;
	print("Test String");

}

uint32_t layer_state_set_user(uint32_t state) {

	uint8_t layer = biton32(state);

	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();
	switch (layer) {
	case _GAME:
		ergodox_right_led_1_on();
		ergodox_right_led_2_on();
		ergodox_right_led_3_on();
		break;
	case _ADJUST:
		ergodox_right_led_1_on();
		break;
	case _RAISE:
		ergodox_right_led_2_on();
		break;
	case _LOWER:
		ergodox_right_led_3_on();
		break;
	}
	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};
