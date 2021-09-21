/* Copyright 2021 gtips
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
    //_LOWER,
};

// Tap Dance declarations
enum {
    TD_MUTE_PLAY,
	TD_NEXT_PREV
};

enum custom_keycodes {
    NAMEPRINT = SAFE_RANGE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_MUTE_PLAY] = ACTION_TAP_DANCE_DOUBLE(KC_MUTE, KC_MPLY),
	[TD_NEXT_PREV] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_MPRV)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case NAMEPRINT:
        if (record->event.pressed) {
            // when keycode NAMEPRINT is pressed
            SEND_STRING("bill.kalominidis");
        } else {
            // when keycode NAMEPRINT is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_reviung5(
        /*TG(_LOWER)*/RGB_TOG,       NAMEPRINT,       TD(TD_NEXT_PREV),       TD(TD_MUTE_PLAY),    KC_ESCAPE
    )//,
    //[_LOWER] = LAYOUT_reviung5(
    //    _______,       RGB_TOG,    NAMEPRINT,    _______,    _______
    //)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
	  tap_code((clockwise == true) ? KC_VOLU : KC_VOLD);
	  tap_code((clockwise == true) ? KC_VOLU : KC_VOLD);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    //case _LOWER:
    //    rgblight_setrgb (RGB_TEAL);
    //    break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_PURPLE);
        break;
    }
  return state;
}
