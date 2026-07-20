# Подключение lang shift

Подключение на примере клавиатуры Sofle

1. Скопируйте файлы lang_shift.c и lang_shift.h в папку вашей клавиатуры (qmk_firmware/keyboards/sofle)
2. В выбранном keymap в файле  rules.mk добавьте в конце строчку
```
SRC += ./lang_shift.c
```
3. В файле keymap.c добавьте заголовочный файл библиотеки
```
#include "lang_shift.h"
```
4. В файле keymap.c инициируйте библиотеку

```
void keyboard_post_init_user(){
    lang_shift_t ctx;
    ctx.language = ENGLISH;
    ctx.ch_lang_combo = ALTSHIFT;
    ls_app_ctx_init(&ctx);
}
```
5. На основном слое назначить клавишу переключения языка, точку и запятую
<pre><code>
[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     XXXXXXX,KC_N,    KC_M, KC_COMM,  <b>LS_DOT</b>, <b>LS_COMM</b>,  <b>LS_YU</b>,
                 KC_LGUI,KC_LALT,<b>LS_SW_LANG</b>, <b>TL_LOWR</b>, KC_ENT,      KC_SPC,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
),
</code></pre>
6. В отдельном слое задать символы
```
[_LOWER] = LAYOUT(
  _______,   _______,   _______,   _______,   _______,   _______,                       _______,   _______,   _______,   _______,  _______,  _______,
  LS_AT,    LS_HASH,    LS_LCBR,    LS_RCBR,    LS_GT,    LS_LT,                       LS_AMPR,    LS_PERC,    LS_COLN,    LS_SCLN,    LS_QUOT,  LS_DQUO,
  _______, LS_LBRC,   LS_RBRC, LS_LPRN,  LS_RPRN, LS_SLSH,                       LS_EXLM, LS_QUES, LS_DASH, LS_UNDR, LS_EQL, LS_PLUS,
  _______,  LS_PIPE, LS_DLR, LS_ASTR, LS_CIRC, LS_BSLS, _______,       _______, LS_GRV, LS_TILD, LS_CH_COMBO, LS_SW_KB_LANG, _______, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)
```

7. Компилите qmk compile -kb sofle -km lang_shift -e CONVERT_TO=rp2040_ce
