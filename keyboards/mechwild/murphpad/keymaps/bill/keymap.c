/* Copyright 2021 Kyle McCreery
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

// Defines names for use in layer keycodes and the keymap

enum layer_names {
  _BASE,
  _FN1,
	_FN2,
	_FN3
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                  KC_F1,   	KC_F2,  	KC_F3,  	KC_MUTE,
				  KC_1, 	KC_2, 		KC_3, 		KC_4,
                  KC_Q,   	KC_W,  		KC_E,  		KC_R,
        MO(_FN1), KC_A,   	KC_S,  		KC_D,  		KC_F,
        KC_LSFT,  KC_Z,   	KC_X,  		KC_C,  		KC_V,
        KC_LCTL,  KC_TAB,   KC_TILDE, 	KC_LALT, 	KC_SPC,

                  KC_F5,   KC_F6,   KC_F7

    ),
    [_FN1] = LAYOUT(
					KC_F4, 		KC_F5, 		KC_F6, 		RGB_TOG,
					KC_5, 		KC_6, 		KC_7, 		KC_8,
					KC_T, 		KC_I, 		KC_O, 		KC_P,
        _______,  	KC_G, 		KC_H, 		KC_J,		KC_L,
        MO(_FN2),  	KC_B, 		KC_N, 		KC_M, 		KC_H,
        KC_ENT,  	KC_BSPC, 	_______, 	_______, 	KC_ESC,

                  _______, _______, _______

    ),
	  [_FN2] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        _______, RGB_RMOD, RGB_TOG, RGB_MOD, _______,
        _______, RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_SAD,  _______, RGB_SAI, _______,

                 _______, _______, _______

    ),
	  [_FN3] = LAYOUT(
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,

                  _______, _______, _______

    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
	if (clockwise) {
		tap_code(KC_VOLD);
		tap_code(KC_VOLD);
	} else {
		tap_code(KC_VOLU);
		tap_code(KC_VOLU);
	}
    return true;
}
#endif

#ifdef OLED_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;       // flips the display 270 degrees
	}

	static void render_logo(void) {     // Render MechWild "MW" Logo
		static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
		static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
		static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
		static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
		oled_set_cursor(0,0);
		oled_write_P(logo_1, false);
		oled_set_cursor(0,1);
		oled_write_P(logo_2, false);
		oled_set_cursor(0,2);
		oled_write_P(logo_3, false);
		oled_set_cursor(0,3);
		oled_write_P(logo_4, false);
	}

	void oled_task_user(void) {
		render_logo();
		oled_set_cursor(0,6);

		//oled_write_ln_P(PSTR("Layer"), false);

	oled_write_ln_P(PSTR("BILL"), false);
	oled_write_ln_P(PSTR(""), false);
	oled_write_ln_P(PSTR("GAME"), false);
	oled_write_ln_P(PSTR(""), false);
	oled_write_ln_P(PSTR("PAD"), false);
	oled_write_ln_P(PSTR(""), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FN1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case _FN2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case _FN3:
            oled_write_ln_P(PSTR("FN 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	}
#endif
