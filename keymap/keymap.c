#include QMK_KEYBOARD_H

enum my_layers {
	_BASE,
	_LOWER,
	_RAISE,
	_ADJUST,
};

#define LOWER  OSL(_LOWER)
#define RAISE  OSL(_RAISE)
#define ADJUST OSL(_ADJUST)
#define LANG   C(KC_SPC)
#define TMUX   C(KC_B)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT(
			KC_ESC,  KC_B,    KC_L,    KC_Y,    KC_X,                      KC_DLR,  KC_F,    KC_O,    KC_U,    KC_P,
			KC_M,    KC_A,    KC_N,    KC_I,    KC_J,                      KC_Z,    KC_R,    KC_E,    KC_H,    KC_T,
			KC_C,    KC_G,    KC_K,    KC_D,    KC_Q,    _______, _______, KC_CIRC, KC_S,    KC_COMM, KC_V,    KC_W,
			OS_LUI, OS_LALT, OS_LCTL, LOWER,   RAISE,   _______, _______, KC_SPC,  OS_LSFT, OS_RCTL, OS_RALT, OS_RGUI
			),

	[_LOWER] = LAYOUT(
			KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                   KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
			KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,                   KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
			KC_TAB,  KC_BSPC, LANG,    KC_ENT,  _______, _______, _______, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_0,
			_______, _______, _______, _______, ADJUST,  _______, _______, _______, _______, _______, _______, _______
			),

	[_RAISE] = LAYOUT(
			KC_GRV,  KC_LT,   KC_GT,   KC_COLN, KC_TILD,                   KC_AMPR, KC_PIPE, KC_PLUS, KC_ASTR, KC_QUES,
			KC_QUOT, KC_LPRN, KC_RPRN, KC_SCLN, KC_BSLS,                   KC_HASH, KC_EQL,  KC_UNDS, KC_DOT,  KC_DQT,
			KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_AT,   _______, _______, KC_PERC, KC_MINS, TMUX,    KC_SLSH, KC_EXLM,
			_______, _______, _______, ADJUST,  _______, _______, _______, KC_BSPC, KC_ENT,  _______, _______, _______
			),

	[_ADJUST] = LAYOUT(
			KC_MUTE, KC_BRID, KC_BRIU, KC_MPLY, _______,                   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F12,
			KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, _______,                   KC_CAPS, KC_F4,   KC_F5,   KC_F6,   KC_F11,
			_______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F10,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),
};

const key_override_t del_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[] = {
	&del_key_override,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case ADJUST:
			if (record->event.pressed) {
				layer_off(_LOWER);
				layer_off(_RAISE);
			}
			break;
	}
	return true;
}
