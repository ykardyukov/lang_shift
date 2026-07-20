#pragma once
#include QMK_KEYBOARD_H
#define OS_LANG_DELAY 20 // Задержка в ms после переключения языка в OS

typedef enum { ENGLISH, RUSSIAN } ls_lang_t; // Поддерживаемые языки

typedef enum { ALTSHIFT, WINSPACE, CTRLSHIFT } ls_ch_lang_combo_t; // Поддерживаемые комбинации переключения языка

#define LS_CH_LANG_COMBO_COUNT 3

typedef struct {
    ls_lang_t          language;      // Язык в клавиатуре
    ls_ch_lang_combo_t ch_lang_combo; // Комбинация переключения языка в OS
} lang_shift_t; // Структура

enum custome_keycodes {
    LS_SW_LANG = SAFE_RANGE, // Переключить язык в OS и KB
    LS_CH_COMBO,             // Изменить комбинацию переключения языков
    LS_SW_KB_LANG,           // Переключить язык в KB
    LS_AT,                   // @
    LS_HASH,                 // #
    LS_LCBR,                 // {
    LS_RCBR,                 // }
    LS_GT,                   // >
    LS_LT,                   // <
    LS_LBRC,                 // [
    LS_RBRC,                 // ]
    LS_LPRN,                 // (
    LS_RPRN,                 // )
    LS_SLSH,                 // /
    LS_PIPE,                 // |
    LS_DLR,                  // $
    LS_ASTR,                 // &
    LS_CIRC,                 // ^
    LS_BSLS,                 // \ (backslash)
    LS_AMPR,                 // &
    LS_PERC,                 // %
    LS_COLN,                 // :
    LS_SCLN,                 // ;
    LS_QUOT,                 // '
    LS_DQUO,                 // "
    LS_EXLM,                 // !
    LS_QUES,                 // ?
    LS_DASH,                 // -
    LS_UNDR,                 // _
    LS_EQL,                  // =
    LS_PLUS,                 // +
    LS_DOT,                  // .
    LS_COMM,                 // ,
    LS_GRV,                  // `
    LS_TILD,                 // ~
    LS_YU                    // ю
};

void               ls_ctx_init(void);
void               ls_app_ctx_init(lang_shift_t *ctx);
ls_lang_t          ls_get_language(void);
ls_ch_lang_combo_t ls_ch_lang_combo(void);
void               ls_switch_language(void);

bool ls_process_record_user(uint16_t keycode, keyrecord_t *record);
