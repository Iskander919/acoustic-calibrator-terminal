#ifndef MAIN_WINDOW_LABELS_H
#define MAIN_WINDOW_LABELS_H

// labels:
#define CONNECT_BUTTON_LABEL    "Соединиться"
#define SWITCH_TO_94_BTN_LABEL  "Переключить в режим 94 дБ"
#define SWITCH_TO_114_BTN_LABEL "Переключить в режим 114 дБ"
#define SET_COEFFS_BUTTON_LABEL "Отправить"
#define WRITE_MEM_BUTTON_LABEL  "Записать данные в память"
#define ERASE_MEM_BUTTON_LABEL  "Стереть память"
#define CLOSE_BUTTON_LABEL      "Закрыть"

#define CORRECTION_EDIT_LABEL   "Уровень"
#define P_EDIT_LABEL            "P"
#define I_EDIT_LABEL            "I"
#define D_EDIT_LABEL            "D"

// mode labels:
#define MODE_94_LABEL           "94 dB"
#define MODE_114_LABEL          "114 dB"

#define CONNECTION_SUCCESS_LABEL "Установлено соединение по "
#define DATA_SENT_TO_RAM         "Данные записаны в RAM"
#define SWITCHED_TO_94_LABEL     "Переключен в режим 94 дБ"
#define SWITCHED_TO_114_LABEL    "Переключен в режим 114 дБ"

// dimensions:
#define MAIN_WINDOW_HEIGHT 400
#define MAIN_WINDOW_WIDTH  600

// fonts:
#define CONSOLE_FONT      "Courier"
#define CONSOLE_FONT_SIZE 11

// commands:
#define WRITE_DATA_TO_RAM_COMMAND_94  0x01
#define WRITE_DATA_TO_RAM_COMMAND_114 0x07
#define SWITCH_TO_94_COMMAND          0x05
#define SWITCH_TO_114_COMMAND         0x06

#endif // MAIN_WINDOW_LABELS_H
