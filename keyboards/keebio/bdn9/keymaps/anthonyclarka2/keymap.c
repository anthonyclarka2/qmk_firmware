/* Copyright 2020 GhostSeven <work@ghost7.com>
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

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_PURPLE);
}

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum custom_keycodes {
    EMACSSAVE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case EMACSSAVE:
        if (record->event.pressed) {
            // when keycode EMACSSAVE is pressed
            SEND_STRING(SS_LCTL("xs"));
        } else {
            // when keycode EMACSSAVE is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |                       | Knob 2: Mouse Wheel Up/Down |
        | Press: Mute       | Emacs Ctrl-x, Ctrl-s  | Press: Home                 |
        | Hold: Layer 2     | Emacs Meta-x          | Ctrl-g                      |
        | Meta              | Super                 | Hyper                       |
     */
    [0] = LAYOUT(
        KC_MUTE, EMACSSAVE , KC_HOME,
        MO(1)  , RALT(KC_X), LCTL(KC_G),
        KC_RALT, KC_RGUI   , KC_HYPR
    ),
    /*
        | RESET          | Shift+CMD+B (Build VS Code) | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | PgUp           | End  | PgDn       |
     */
    [1] = LAYOUT(
        RESET  , S(G(KC_B)), KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_PGUP, KC_END , KC_PGDN
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
    return true;
}
