#include QMK_KEYBOARD_H

enum my_layers {
	_HAZE,
	_QWERTY,
	_LOWER,
	_RAISE,
	_ADJUST,
	_MOUSE,
};

enum my_keycodes {
	LANG1 = SAFE_RANGE,
	LANG2,
};

#define LOWER LT(_LOWER, KC_SPC)
#define RAISE OSL(_RAISE)
#define MOUSE LT(_MOUSE, KC_BSPC)
#define DOTADJ LT(_ADJUST, KC_DOT)
#define ESCADJ LT(_ADJUST, KC_ESC)
#define TMUX C(KC_B)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_HAZE] = LAYOUT(
			KC_X,    KC_P,    KC_H,    KC_Y,    KC_DLR,                    KC_CIRC, KC_L,    KC_A,    KC_M,    KC_V,
			KC_S,    KC_T,    KC_R,    KC_E,    KC_Z,                      KC_Q,    KC_N,    KC_O,    KC_I,    KC_C,
			KC_J,    KC_B,    KC_D,    KC_U,    LANG1,   _______, _______, LANG2,   KC_F,    KC_G,    KC_K,    KC_W,
			OS_LGUI, OS_LALT, OS_LCTL, MOUSE,   LOWER,   _______, _______, RAISE,   OS_RSFT, OS_RCTL, OS_RALT, OS_RGUI
			),

	[_QWERTY] = LAYOUT(
			KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
			KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_DLR,
			KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, _______, _______, KC_B,    KC_N,    KC_M,    KC_CIRC,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	[_LOWER] = LAYOUT(
			KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                   KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
			KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,                   KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
			KC_ENT,  KC_DEL,  TMUX,    KC_TAB,  _______, _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_0,
			_______, _______, _______, _______, _______, _______, _______, DOTADJ,  CW_TOGG, _______, _______, _______
			),

	[_RAISE] = LAYOUT(
			KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_BSLS,                   KC_AT,   KC_AMPR, KC_QUES, KC_EXLM, KC_PIPE,
			KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_PERC,                   KC_HASH, KC_UNDS, KC_COMM, KC_DOT,  KC_DQT,
			KC_LT,   KC_PLUS, KC_MINS, KC_GT,   KC_TILD, _______, _______, KC_GRV,  KC_EQL,  KC_SLSH, KC_ASTR, KC_QUOT,
			_______, _______, _______, KC_ENT,  ESCADJ,  _______, _______, _______, _______, _______, _______, _______
			),

	[_ADJUST] = LAYOUT(
			KC_CAPS, _______, KC_INS,  KC_CAPS, _______,                   KC_F15,  KC_F7,   KC_F8,   KC_F9,   KC_F12,
			KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, _______,                   KC_F14,  KC_F4,   KC_F5,   KC_F6,   KC_F11,
			_______, KC_BRID, KC_BRIU, KC_MPLY, _______, _______, _______, KC_F13,  KC_F1,   KC_F2,   KC_F3,   KC_F10,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	[_MOUSE] = LAYOUT(
			MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,                   _______, MS_BTN4, MS_WHLU, MS_BTN5, _______,
			MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______,                   _______, MS_BTN1, MS_BTN3, MS_BTN2, _______,
			MS_BTN1, MS_BTN1, MS_BTN2, MS_BTN2, _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLR, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(record->event.pressed) {
		switch(keycode) {
			case LANG1:
				tap_code16(C(KC_SPC));
			case LANG2:
				if (get_highest_layer(default_layer_state) == _HAZE)
					set_single_persistent_default_layer(_QWERTY);
				else
					set_single_persistent_default_layer(_HAZE);
				return false;
		}
	}
	return true;
}
