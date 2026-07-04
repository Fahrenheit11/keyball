#include QMK_KEYBOARD_H
#include "quantum.h"

// コンボの定義
enum combo_events {
  COMBO_LCLK,
  COMBO_RCLK,
  COMBO_FSCROLL
};

const uint16_t PROGMEM combo_lclk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_rclk[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_fscroll[] = {LT(5, KC_D), LT(1, KC_F), COMBO_END};

combo_t key_combos[] = {
  [COMBO_LCLK] = COMBO(combo_lclk, KC_BTN1),
  [COMBO_RCLK] = COMBO(combo_rclk, KC_BTN2),
  [COMBO_FSCROLL] = COMBO(combo_fscroll, MO(5)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // [0] default
  [0] = LAYOUT_universal(
    KC_TAB,         KC_Q,        KC_W,    KC_E,          KC_R,          KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_BSPC,
    LCTL_T(KC_ESC), KC_A,        KC_S,    LT(5, KC_D),   LT(1, KC_F),   KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    LT(5, KC_SCLN),KC_ENT,
    KC_LSFT,        KC_Z,        KC_X,    KC_C,          KC_V,          KC_B,       KC_ASTR, KC_N,    KC_M,    KC_COMM, KC_DOT,        KC_SLSH,
                    KC_LGUI,     KC_LALT, LT(3, KC_LNG2),LT(4, KC_EQL), KC_NO,      KC_NO,   LT(2, KC_MINS), LT(4, KC_SPC), LT(3, KC_LNG1), LT(5, KC_GRV)
  ),

  // [1] MOUSE
  [1] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______, LCTL(KC_V), LCTL(KC_V), _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, LCTL(KC_C), KC_BTN1,    KC_BTN3, KC_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______, LCTL(KC_X), _______,    _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  // [2] FUNCTION
  [2] = LAYOUT_universal(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_GRV,  _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  _______,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, _______, _______, _______, _______, _______,
             KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______
  ),

  // [3] SYMBOL
  [3] = LAYOUT_universal(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_GRV,  _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT, KC_LBRC, KC_RBRC, KC_RGHT, KC_QUOT, KC_DEL,
    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, KC_BSLS,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  // [4] NUM
  [4] = LAYOUT_universal(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_GRV,  _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  // [5] SCROLL (ZMKのscrool_subとSCROLLを統合)
  [5] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // レイヤー5 (SCROLL) が最上位の時にスクロールモードを有効化
    keyball_set_scroll_mode(get_highest_layer(state) == 5);
    return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
