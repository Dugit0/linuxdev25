#include "roman.h"
#include <string.h>

static const char* roman[101] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
 * @brief Преобразует десятичное число в римское
 *
 * @param[in] num Десятичное число для преобразования (1-100)
 * @param[out] result Буфер для результата
 * @param[in] n Размер буфера result
 *
 * @return Указатель на result в случае успеха, NULL в случае ошибки
 *
 * @warning result должен быть достаточно большим для хранения римского числа
 *
 * @note Для num вне диапазона 1-100 возвращает NULL
 *
 * @see ROMAN_MAX_SIZE
 */
char* dec2rom(int num, char* result, size_t n) {
    if (num < 1 || num > 100) {
        return NULL;
    } else {
        for (size_t i = 0; i < n; i++) {
            result[i] = 0;
        }
        strcpy(result, roman[num]);
        return result;
    }
}


/**
 * @brief Преобразует римское число в десятичное
 *
 * @param[in] num Строка с римским числом
 *
 * @return Десятичное число (1-100) или -1 в случае ошибки
 *
 * @note Возвращает -1 если:
 *       - число некорректно
 *       - число вне диапазона 1-100
 */
int rom2dec(const char* num) {
    for (int i = 1; i <= 100; i++) {
        if (strcmp(num, roman[i]) == 0) {
            return i;
        }
    }
    return -1;
}
