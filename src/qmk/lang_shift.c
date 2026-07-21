#include "lang_shift.h"

static bool _pressed = false; // Повтор клавише при долгом нажатии

// Прячем контекст в статической переменной -> структура недоступна в программе
static lang_shift_t ls_ctx;

// Инициализация контекта
void ls_app_ctx_init(lang_shift_t *ctx) {
    ls_ctx.language      = ctx->language;
    ls_ctx.ch_lang_combo = ctx->ch_lang_combo;
}

// Переключаем язык в клавиатуре
void ls_sw_kb_language(void) {
    if (ls_ctx.language == RUSSIAN) {
        ls_ctx.language = ENGLISH;
    } else if (ls_ctx.language == ENGLISH) {
        ls_ctx.language = RUSSIAN;
    }
}

// Возвращает текущий язык
ls_lang_t ls_get_language() {
    return ls_ctx.language;
}

// Возвращает текущее комбо по переключению языка в OS
ls_ch_lang_combo_t ls_ch_lang_combo() {
    return ls_ctx.ch_lang_combo;
}

// Переключаем на следующее комбо по переключению языка в OS
void ls_next_ch_lang_combo(void) {
    ls_ctx.ch_lang_combo++;
    if (ls_ctx.ch_lang_combo > (LS_CH_LANG_COMBO_COUNT - 1)) {
        ls_ctx.ch_lang_combo = 0;
    }
}

// Переключаем язык в OS
void ls_sw_os_language(int delay) {
    if (ls_ctx.ch_lang_combo == WINSPACE) {
        // Если переключение языка в системе WIN+SPACE
        register_code16(KC_LWIN);
        register_code16(KC_SPC);
        unregister_code16(KC_LWIN);
        unregister_code16(KC_SPC);
    } else if (ls_ctx.ch_lang_combo == ALTSHIFT) {
        // Если переключение языка в системе ALT+SHIFT
        register_code16(KC_LALT);
        register_code16(KC_LSFT);
        unregister_code16(KC_LALT);
        unregister_code16(KC_LSFT);
    } else if (ls_ctx.ch_lang_combo == CTRLSHIFT) {
        // Если переключение языка в системе CTRL+SHIFT
        register_code16(KC_LCTL);
        register_code16(KC_LSFT);
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LSFT);
    }
    if (delay > 0) {
        SEND_STRING(SS_DELAY(OS_LANG_DELAY));
    }
}

// Переключаем язык в OS и клавиатуре
void ls_switch_language(void) { // Если переключение языка в системе ALT+SHIFT
    ls_sw_os_language(OS_LANG_DELAY);
    ls_sw_kb_language();
}

// Для отправки кейкода меняем язык в OS
void ls_int_sw_lang(uint16_t EN_KC, uint16_t RU_KC, keyrecord_t *record) {
    if (record->event.pressed) {
        if (ls_ctx.language == RUSSIAN) {
            register_code16(RU_KC);
        } else if (ls_ctx.language == ENGLISH) {
            register_code16(EN_KC);
        }
    } else {
        if (ls_ctx.language == RUSSIAN) {
            unregister_code16(RU_KC);
        } else if (ls_ctx.language == ENGLISH) {
            unregister_code16(EN_KC);
        }
    }
}

// Для отправки кейкода не нужно переключать язык в OS
void ls_int_same_lang(uint16_t KC, keyrecord_t *record) {
    if (record->event.pressed) {
        if (ls_ctx.language == RUSSIAN) {
            if (!_pressed) {
                ls_sw_os_language(OS_LANG_DELAY);
                _pressed = !_pressed;
            }
            register_code16(KC);
        } else if (ls_ctx.language == ENGLISH) {
            register_code16(KC);
        }
    } else {
        if (ls_ctx.language == RUSSIAN) {
            if (_pressed) {
                ls_sw_os_language(OS_LANG_DELAY);
                _pressed = !_pressed;
            }
            unregister_code16(KC);
        } else if (ls_ctx.language == ENGLISH) {
            unregister_code16(KC);
        }
    }
}

void ls_sent_alt_code(keyrecord_t *record, uint16_t KC1, uint16_t KC2, uint16_t KC3, uint16_t KC4){
        if (record->event.pressed){
            register_code(KC_LALT);
            register_code(KC1);
            register_code(KC2);
            register_code(KC3);
            register_code(KC4);
        } else {
            unregister_code(KC_LALT);
            unregister_code(KC1);
            unregister_code(KC2);
            unregister_code(KC3);
            unregister_code(KC4);
        }
} 

// Эту функцию нужно вызвать в process_record_user
bool ls_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LS_SW_LANG: {
            if (record->event.pressed) {
                ls_switch_language();
            }
            return false;
        }

        case LS_CH_COMBO: {
            if (record->event.pressed) {
                ls_next_ch_lang_combo();
            }
            return false;
        }
        case LS_SW_KB_LANG: {
            if (record->event.pressed) {
                ls_sw_kb_language();
            }
            return false;
        }
        case LS_COMM: {
            ls_int_sw_lang(KC_COMM, S(KC_SLSH), record);
            return false;
        }
        case LS_DOT: {
            ls_int_sw_lang(KC_DOT, KC_SLSH, record);
            return false;
        }
        case LS_QUES: {
            ls_int_sw_lang(KC_QUES, S(KC_7), record);
            return false;
        }
        case LS_EXLM: {
            ls_int_sw_lang(KC_EXLM, S(KC_1), record);
            return false;
        }
        case LS_DQUO: {
            ls_int_sw_lang(S(KC_QUOT), S(KC_2), record);
            return false;
        }
        case LS_QUOT: {
            ls_int_same_lang(KC_QUOT, record);
            return false;
        }
        case LS_SCLN: {
            ls_int_sw_lang(KC_SCLN, S(KC_4), record);
            return false;
        }
        case LS_COLN: {
            ls_int_sw_lang(KC_COLN, S(KC_6), record);
            return false;
        }
        case LS_PERC: {
            ls_int_sw_lang(KC_PERC, S(KC_5), record);
            return false;
        }
        case LS_AMPR: {
            ls_int_same_lang(KC_AMPR, record);
            return false;
        }
        case LS_GRV: {
            ls_int_same_lang(KC_GRV, record);
            return false;
        }
        case LS_TILD: {
            ls_int_same_lang(S(KC_GRV), record);
            return false;
        }
        case LS_AT: {
            ls_int_same_lang(KC_AT, record);
            return false;
        }
        case LS_HASH: {
            ls_int_same_lang(KC_HASH, record);
            return false;
        }
        case LS_LCBR: {
            ls_int_same_lang(KC_LCBR, record);
            return false;
        }
        case LS_RCBR: {
            ls_int_same_lang(KC_RCBR, record);
            return false;
        }
        case LS_LT: {
            ls_int_same_lang(KC_LT, record);
            return false;
        }
        case LS_GT: {
            ls_int_same_lang(KC_GT, record);
            return false;
        }
        case LS_LBRC: {
            ls_int_same_lang(KC_LBRC, record);
            return false;
        }
        case LS_RBRC: {
            ls_int_same_lang(KC_RBRC, record);
            return false;
        }
        case LS_LPRN: {
            // sw_lang(KC_LPRN, record);
            ls_int_sw_lang(KC_LPRN, S(KC_9), record);
            return false;
        }
        case LS_RPRN: {
            // sw_lang(KC_RPRN, record);
            ls_int_sw_lang(KC_RPRN, S(KC_0), record);
            return false;
        }
        case LS_SLSH: {
            ls_int_sw_lang(KC_SLSH, KC_PSLS, record);
            return false;
        }
        case LS_PIPE: {
            ls_int_same_lang(KC_PIPE, record);
            return false;
        }
        case LS_DLR: {
            ls_int_same_lang(KC_DLR, record);
            return false;
        }
        case LS_ASTR: {
            ls_int_sw_lang(KC_ASTR, KC_PAST, record);
            return false;
        }
        case LS_CIRC: {
            ls_int_same_lang(KC_CIRC, record);
            return false;
        }
        case LS_BSLS: {
            if (record->event.pressed) {
                register_code16(KC_BSLS);
            } else {
                unregister_code16(KC_BSLS);
            }
            return false;
        }
        case LS_DASH: {
            if (record->event.pressed) {
                register_code16(KC_MINS);
            } else {
                unregister_code16(KC_MINS);
            }
            return false;
        }
        case LS_UNDR: {
            if (record->event.pressed) {
                register_code16(S(KC_MINS));
            } else {
                unregister_code16(S(KC_MINS));
            }
            return false;
        }
        case LS_EQL: {
            if (record->event.pressed) {
                register_code16(KC_EQL);
            } else {
                unregister_code16(KC_EQL);
            }
            return false;
        }

        case LS_PLUS: {
            if (record->event.pressed) {
                register_code16(S(KC_EQL));
            } else {
                unregister_code16(S(KC_EQL));
            }
            return false;
        }
        // Обработка буквы "Ю" в русской раскладке. Если включен русский язык, тогда регистрируем KC_DOT, что соответствует букве Ю в русской раскладке.
        case LS_YU: {
            if (record->event.pressed) {
                if (ls_ctx.language == RUSSIAN) {
                    register_code(KC_DOT);
                    return false;
                } else {
                    register_code(KC_RBRC);
                }
            } else {
                if (ls_ctx.language == RUSSIAN) {
                    unregister_code(KC_DOT);
                    return false;
                } else {
                    unregister_code(KC_RBRC);
                }
            }
            return true;
        }
    }

    return true;
}
