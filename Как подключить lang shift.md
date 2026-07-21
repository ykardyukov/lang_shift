# Подключение lang shift

Подключение на примере клавиатуры [Sofle](https://github.com/qmk/qmk_firmware/tree/master/keyboards/sofle)

1. Скопируйте файлы `lang_shift.c` и `lang_shift.h` в корневую папку вашей клавиатуры, на одном уровне с файлом `info.json` (`qmk_firmware/keyboards/sofle`)
<pre><code>
-rw-r--r-- 1  5111 июл  1 15:58 info.json
drwxr-xr-x 1     0 июл 20 22:01 keymaps
-rw-r--r-- 1  9520 июл 20 20:07 <b>lang_shift.c</b>
-rw-r--r-- 1  2365 июл 20 20:09 <b>lang_shift.h</b>
-rw-r--r-- 1  1846 июл  1 15:58 readme.md
drwxr-xr-x 1     0 июл 20 22:00 rev1
-rw-r--r-- 1  4039 июл  1 15:58 sofle.c
</code></pre>
2. В `rules.mk` в папке `keymaps` добавьте в конце строчку. При сборке компилятор включит указанный файл вместе с `keymap.c`
```C
SRC += ./lang_shift.c
```
3. В `файле keymap.c` добавьте заголовочный файл `lang_shift.h`
```C
#include "lang_shift.h"
```
4. В файле `keymap.c` определите callback-функцию `keyboard_post_init_user()`, ее вызовет QMK после окончания инициализации клавиатуры:
   - `ctx.language` - текущий язык в клавиатуре. Рекомендуется ставить таким же, что и основной язык в OS. Возможные значения ENGLISH или RUSSIAN
   - `ctx.ch_lang_combo` = комбинация клавиш, которая переключает язык в OS (ALTSHIFT, WINSPACE, CTRLSHIFT)

```C
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
<pre><code>
[_LOWER] = LAYOUT(
  _______,   _______,   _______,   _______,   _______,   _______,                       _______,   _______,   _______,   _______,  _______,  _______,
  LS_AT,    LS_HASH,    LS_LCBR,    LS_RCBR,    LS_GT,    LS_LT,                       LS_AMPR,    LS_PERC,    LS_COLN,    LS_SCLN,    LS_QUOT,  LS_DQUO,
  _______, LS_LBRC,   LS_RBRC, LS_LPRN,  LS_RPRN, LS_SLSH,                       LS_EXLM, LS_QUES, LS_DASH, LS_UNDR, LS_EQL, LS_PLUS,
  _______,  LS_PIPE, LS_DLR, LS_ASTR, LS_CIRC, LS_BSLS, _______,       _______, LS_GRV, LS_TILD, LS_CH_COMBO, LS_SW_KB_LANG, _______, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)
</code></pre>

7. Добавьте вызов функции `ls_process_record_user` в `process_record_user`
```C
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    ls_process_record_user(keycode, record);
```
8. Компилите `qmk compile -kb sofle -km lang_shift -e CONVERT_TO=rp2040_ce`
