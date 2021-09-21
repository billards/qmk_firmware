/* Copyright 2020 imchipwood
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
enum {
    TD_SLASH_CALC
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASH_CALC] = ACTION_TAP_DANCE_DOUBLE(KC_KP_SLASH, KC_CALCULATOR)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*		NUMPAD LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  / CALC |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    *    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    -    |
    |-------------|---------|---------|---------|---------|
    |     =/L     |    0    |    .    |   BKSP  |    +    |
    \-----------------------------------------------------'
	*/
    [0] = LAYOUT(
					KC_7,	KC_8,	KC_9,   	TD(TD_SLASH_CALC),
					KC_4,	KC_5,	KC_6,   	KC_KP_ASTERISK,
					KC_1,	KC_2,	KC_3,		KC_KP_MINUS,
	LT(2, KC_EQL),	KC_0,	KC_DOT,	KC_BSPACE,	KC_KP_PLUS
    ),
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    1    |    2    |    3    |    4    |
    |             |---------|---------|---------|---------|
    |             |    Q    |    W    |    E    |    R    |
    |             |---------|---------|---------|---------|
    |             |    A    |    S    |    D    |    F    |
    |-------------|---------|---------|---------|---------|
    |    SHIFT    |    C    |    L    |   CTRL  |  SPACE  |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    KC_1,	KC_2,	KC_3,		KC_4,
                    KC_Q,	KC_W,	KC_E,		KC_R,
                    KC_A,	KC_S,	KC_D,		KC_F,
        KC_LSHIFT,	KC_C,	MO(2),	KC_LCTRL,	KC_SPACE
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |    L0   |    L1   |    L2   |   RGB   |
    |             |---------|---------|---------|---------|
    |             |   TAB   |         |    `    |    H    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    Y    |
    |-------------|---------|---------|---------|---------|
    |     ESC     |    Z    |    L    |    X    |    T    |
    \-----------------------------------------------------'
    */
    [2] = LAYOUT(
                    TO(0),     	TO(1),  	TO(3),      RGB_TOG,
                    KC_TAB,    	_______,	KC_T,     	KC_Y,
                    _______,	_______,	_______,	KC_H,
        KC_ESCAPE,  KC_Z,       _______,	KC_X,       KC_GRAVE
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |    1    |    2    |    3    |   4   |
    |             |---------|---------|---------|---------|
    |             |    Q    |    W    |    E    |    R    |
    |             |---------|---------|---------|---------|
    |             |    A    |    S    |    D    |    F    |
    |-------------|---------|---------|---------|---------|
    |    LAYER    |    Z    |    X    |    C    |  SPACE  |
    \-----------------------------------------------------'
    */
    [3] = LAYOUT(
							KC_1,	KC_2,	KC_3,	KC_4,
							KC_Q,	KC_W,	KC_E,   KC_R,
							KC_A,	KC_S,	KC_D,   KC_F,
        LT(4, KC_ESCAPE),	KC_Z,	KC_X,	KC_C,   KC_SPACE
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |    5    |    6    |    7    |  P/ALT  |
    |             |---------|---------|---------|---------|
    |             |   TAB   |    T    |    I    |    O    |
    |             |---------|---------|---------|---------|
    |             | G/SHIFT |    H    |    J    |    L    |
    |-------------|---------|---------|---------|---------|
    |             |    V    |    B    |    N    |  M/CTRL |	
    \-----------------------------------------------------'
    */
    [4] = LAYOUT(
                    KC_5,     		KC_6,	KC_7,	LALT_T(KC_P),
                    KC_TAB,    		KC_T,	KC_I,	KC_O,
                    LSFT_T(KC_G),	KC_H,	KC_J,	KC_L,
        _______,    KC_V,       	KC_B,	KC_N,	LCTL_T(KC_M)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
*/
    return true;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    /*  Custom encoder control - handles CW/CCW turning of encoder
     *  Default behavior:
     *    main layer:
     *       CW: move mouse right
     *      CCW: move mouse left
     *    other layers:
     *       CW: = (equals/plus - increase slider in Adobe products)
     *      CCW: - (minus/underscore - decrease slider in adobe products)
     */
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                // main layer - move mouse right (CW) and left (CCW)
                if (clockwise) {
                    tap_code(KC_MS_R);
                } else {
                    tap_code(KC_MS_L);
                }
                break;

            default:
                // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
                if (clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
        }
    }
    return true;
}
