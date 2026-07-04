#include QMK_KEYBOARD_H
#include "quantum.h"

// コンボの定義
enum combo_events {
  COMBO_LCLK,
  COMBO_RCLK,
  COMBO_FSCROLL,
  COMBO_LCLK_L1, // レイヤー1での左クリックコンボ
  COMBO_RCLK_L1  // レイヤー1での右クリックコンボ
};

// レイヤー0用（通常の文字入力状態）
const uint16_t PROGMEM combo_lclk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_rclk[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_fscroll[] = {LT(5, KC_D), LT(1, KC_F), COMBO_END};

// レイヤー1用（J=BTN1, K=BTN3, L=BTN2 として認識されるため、そのキーコードで同時押しを判定する）
const uint16_t PROGMEM combo_lclk_l1[] = {KC_BTN1, KC_BTN3, COMBO_END};
const uint16_t PROGMEM combo_rclk_l1[] = {KC_BTN3, KC_BTN2, COMBO_END};

combo_t key_combos[] = {
  [COMBO_LCLK] = COMBO(combo_lclk, KC_BTN1),
  [COMBO_RCLK] = COMBO(combo_rclk, KC_BTN2),
  [COMBO_FSCROLL] = COMBO(combo_fscroll, MO(5)),
  [COMBO_LCLK_L1] = COMBO(combo_lclk_l1, KC_BTN1),
  [COMBO_RCLK_L1] = COMBO(combo_rclk_l1, KC_BTN2),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // [0] default
  [0] = LAYOUT_universal(
    KC_TAB,         KC_Q,        KC_W,    KC_E,          KC_R,          KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_BSPC,
    LCTL_T(KC_ESC), KC_A,        KC_S,    LT(5, KC_D),   LT(1, KC_F),   KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    LT(5, KC_SCLN),KC_ENT,
    KC_LSFT,        KC_Z,        KC_X,    KC_C,          KC_V,          KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_ASTR,
    KC_LGUI,     KC_LALT, LT(3, KC_LNG2),LT(4, KC_EQL),   LT(2, KC_MINS), LT(4, KC_SPC), LT(3, KC_LNG1),KC_NO,KC_NO, LT(5, KC_GRV)
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
    // keyball_set_scroll_mode(get_highest_layer(state) == 5);
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


// keymap.c の末尾を以下に置き換え

uint16_t auto_mouse_timer = 0;
bool auto_mouse_active = false;

// マウスレイヤー（レイヤー1）滞在中に、自動解除を「無効化」したいキーの条件を指定
bool is_mouse_key(uint16_t keycode) {
    switch (keycode) {
        // マウスボタンおよびレイヤー1に配置されたコピペショートカットは解除の対象外
        case KC_BTN1:
        case KC_BTN2:
        case KC_BTN3:
        case KC_MS_U:
        case KC_MS_D:
        case KC_MS_L:
        case KC_MS_R:
        case LCTL(KC_C): // コピー
        case LCTL(KC_X): // 切り取り
        case LCTL(KC_V): // ペースト
            return true;
        default:
            return false;
    }
}

// キーが押された瞬間に割り込んで判定
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // 自動マウスレイヤーが有効、かつ押されたキーがマウス関連キー「以外」の場合
        if (auto_mouse_active && !is_mouse_key(keycode)) {
            layer_off(1); // 即座にレイヤー1を解除
            auto_mouse_active = false;
        }
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // トラックボールの移動またはクリックを検知
    // レイヤー5（スクロールレイヤー）が最上位の場合の処理
    if (layer_state_cmp(layer_state, 5)) {
        // トラックボールの移動量を高解像度スクロール量に変換する
        // ※OSのスクロール方向設定に合わせて符号（-）を反転させること
        // ※感度を変えたい場合は mouse_report.y * 2 のように定数を掛けること
        static float scroll_accum_v = 0.0;

        scroll_accum_v += -mouse_report.y * 0.1;

        mouse_report.v = (int8_t)scroll_accum_v; // 縦スクロール
        mouse_report.h = 0;  // 横スクロール
        
        scroll_accum_v -= mouse_report.v; // 剩余量を取り除く

        // カーソル自体の移動を無効化
        mouse_report.x = 0;
        mouse_report.y = 0;
        
        // このレイヤーでは自動マウスレイヤーの遷移処理をスキップ
        return mouse_report;
    }
    if (mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.buttons != 0) {
        // レイヤー5が最上位（スクロールモード中）の場合は遷移させない
        if (layer_state_cmp(layer_state, 5)) {
            return mouse_report;
        }

        if (!auto_mouse_active) {
            layer_on(1); // レイヤー1 (MOUSE) を有効化
            auto_mouse_active = true;
        }
        auto_mouse_timer = timer_read(); // タイマーリセット
    }

    // トラックボール操作が途切れてから 400ms 経過したら解除
    if (auto_mouse_active && timer_elapsed(auto_mouse_timer) > 400) {
        layer_off(1);
        auto_mouse_active = false;
    }

    return mouse_report;
}

// コンボが発動・解除された瞬間に割り込むQMK標準関数
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
            case COMBO_LCLK:
            case COMBO_RCLK:
            case COMBO_LCLK_L1:
            case COMBO_RCLK_L1:
                // 指定のコンボ成立時、自動マウスレイヤー中であれば即時解除
                if (auto_mouse_active) {
                    layer_off(1);
                    auto_mouse_active = false;
                }
                break;
        }
    }
}
// キーボード起動時に1回だけ実行される関数
void keyboard_post_init_user(void) {
    pointing_device_set_cpi(5); // 1000の部分を希望のDPIに変更する
}
