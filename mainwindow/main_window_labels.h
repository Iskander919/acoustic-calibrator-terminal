#ifndef MAIN_WINDOW_LABELS_H
#define MAIN_WINDOW_LABELS_H

// labels:
#define CONNECT_BUTTON_LABEL    "Соединиться"
#define SWITCH_TO_94_BTN_LABEL  "Переключить в режим 94 дБ"
#define SWITCH_TO_114_BTN_LABEL "Переключить в режим 114 дБ"
#define SET_COEFFS_BUTTON_LABEL "Отправить"
#define WRITE_MEM_BUTTON_LABEL  "Записать данные в память"
#define ERASE_MEM_BUTTON_LABEL  "Стереть память"
#define INFO_BUTTON_LABEL       "Справка"
#define CLOSE_BUTTON_LABEL      "Закрыть"
#define DEVICE_DATA_BUTTN_LABEL "Прочитать"
#define DEVICE_DATA_WRITE_BUTTON_LABEL "Записать"

#define CORRECTION_EDIT_LABEL   "Уровень"
#define P_EDIT_LABEL            "P"
#define I_EDIT_LABEL            "I"
#define D_EDIT_LABEL            "D"

#define DEVICE_NUMBER_LABEL     "Серийный номер"
#define SOFTWARE_VERSION_LABEL  "Версия ПО"
#define CHECKSUM_LABEL          "Контрольная сумма"

// mode labels:
#define MODE_94_LABEL           "94 dB"
#define MODE_114_LABEL          "114 dB"

#define CONNECTION_SUCCESS_LABEL "Установлено соединение по "
#define DATA_SENT_TO_RAM         "Данные записаны в RAM"
#define SWITCHED_TO_94_LABEL     "Переключен в режим 94 дБ"
#define SWITCHED_TO_114_LABEL    "Переключен в режим 114 дБ"
#define EEPROM_94_LABEL          "Данные записаны в EEPROM для режима 94 дБ"
#define EEPROM_114_LABEL         "Данные записаны в EEPROM для режима 114 дБ"
#define ID_WAS_WRITTEN           "Серийный номер записан в EEPROM"

#define NUMERIC_WARNING          "Все поля должны иметь числовое значение"
#define ID_NUMERIC_WARNING       "Серийный номер должен иметь целочисленное значение"



// dimensions:
#define MAIN_WINDOW_HEIGHT 500
#define MAIN_WINDOW_WIDTH  900

// fonts:
#define CONSOLE_FONT      "Courier"
#define CONSOLE_FONT_SIZE 11

// commands:
#define WRITE_DATA_TO_RAM_COMMAND_94  0x01
#define WRITE_DATA_TO_RAM_COMMAND_114 0x07
#define SWITCH_TO_94_COMMAND          0x05
#define SWITCH_TO_114_COMMAND         0x06
#define WRITE_94_TO_MEMORY_COMMAND    0x08
#define WRITE_114_TO_MEMORY_COMMAND   0x09
#define WRITE_DEVICE_ID_COMMAND       0x0A
#define READ_DEVICE_DATA_COMMAND      0x0B

// adc refs:
#define MODE_94_REF  2070
#define MODE_114_REF 3500

// default values for 94 dB:
#define P_DEFAULT    "0.0000001"
#define I_DEFAULT    "0.00000002"
#define D_DEFAULT    "0.00000002"
#define BIAS_DEFAULT "0.098"
// default values for 114 dB:
#define P_DEFAULT_114    "0.00001"
#define I_DEFAULT_114    "0.0000015"
#define D_DEFAULT_114    "0.00001"
#define BIAS_DEFAULT_114 "0.000245"

#endif // MAIN_WINDOW_LABELS_H
