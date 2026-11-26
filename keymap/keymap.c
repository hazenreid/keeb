#include QMK_KEYBOARD_H

enum my_layers {
	_BASE,
	_LOWER,
	_RAISE,
	_ADJUST,
};

#define LOWER    OSL(_LOWER)
#define RAISE    OSL(_RAISE)
#define ADJUST   MO(_ADJUST)
#define TMUX_ADJ LT(_ADJUST, KC_B) // tap: Ctrl+B (tmux prefix), hold: ADJUST
#define LANG     C(KC_SPC)
#define TMUX     C(KC_B)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT(
			KC_B,    KC_U,    KC_O,    KC_F,    KC_CIRC,                   KC_Z,    KC_M,    KC_L,    KC_G,    KC_V,
			KC_R,    KC_I,    KC_E,    KC_N,    LANG,                      KC_J,    KC_A,    KC_T,    KC_SPC,  KC_D,
			KC_W,    KC_X,    KC_Y,    KC_S,    KC_AT,   _______, _______, KC_Q,    KC_H,    KC_K,    KC_C,    KC_P,
			OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, LOWER,   _______, _______, RAISE,   OS_LSFT, OS_RCTL, OS_RALT, OS_RGUI
			),

	[_LOWER] = LAYOUT(
			KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                   KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
			KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, DM_PLY2,                   KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
			KC_TAB,  KC_BSPC, KC_ESC,  KC_ENT,  DM_PLY1, _______, _______, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_0,
			_______, _______, _______, _______, _______, _______, _______, TMUX_ADJ,_______, _______, _______, _______
			),

	[_RAISE] = LAYOUT(
			KC_BSLS, KC_LCBR, KC_RCBR, KC_SLSH, KC_GRV,                    KC_PERC, KC_PIPE, KC_AMPR, KC_ASTR, KC_QUES,
			KC_LT,   KC_LPRN, KC_RPRN, KC_SCLN, KC_HASH,                   KC_DLR,  KC_COLN, KC_COMM, KC_UNDS, KC_GT,
			KC_EXLM, KC_MINS, KC_EQL,  KC_DOT,  KC_PLUS, _______, _______, KC_TILD, KC_DQT,  KC_LBRC, KC_RBRC, KC_QUOT,
			_______, _______, _______, _______, ADJUST,  _______, _______, _______, _______, _______, _______, _______
			),

	[_ADJUST] = LAYOUT(
			KC_MUTE, KC_BRID, KC_BRIU, KC_MPLY, DM_RSTP,                   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F12,
			KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, DM_REC2,                   KC_CAPS, KC_F4,   KC_F5,   KC_F6,   KC_F11,
			_______, _______, _______, _______, DM_REC1, _______, _______, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F10,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case TMUX_ADJ:
			// LT() can only tap basic keycodes, so send Ctrl+B ourselves on tap.
			if (record->tap.count && record->event.pressed) {
				tap_code16(TMUX);
				return false;
			}
			break;
	}
	return true;
}

const key_override_t del_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[] = {
	&del_key_override,
};
