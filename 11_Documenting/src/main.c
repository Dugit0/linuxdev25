/** @mainpage Угадай число
 * **-r** -- переводит программу в римскую систему счисления
 */


/**
 * @file guess.c
 * @brief Программа для игры "Угадай число" с поддержкой римских цифр
 *
 * Программа использует двоичный поиск для угадывания числа в диапазоне 1-100
 * с возможностью отображения чисел в римской или десятичной системе счисления.
 * Поддерживает интернационализацию с помощью gettext.
 */


#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext(string)
#define PACKAGE "guess"
#define LOCALEDIR "locale"

/** Максимальный размер строки для римского числа */
ssize_t ROMAN_MAX_SIZE = 20;

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

/**
 * @brief Основная функция программы
 *
 * Программа играет в игру "Угадай число" используя двоичный поиск.
 * Поддерживает отображение чисел в римской или десятичной системе.
 *
 * @return 0 при успешном завершении, 1 при ошибке ввода
 *
 * @note Флаг roman_flag управляет форматом вывода чисел:
 *       - 1: римские числа
 *       - 0: десятичные числа
 *
 * @see dec2rom()
 * @see rom2dec()
 */
int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    bind_textdomain_codeset(PACKAGE, "UTF-8");

    int roman_flag = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
            printf(_("Guess the number\n\n-r - change program to roman mode\n"));
            return 0;
        } else if (!strcmp("-r", argv[i])) {
            roman_flag = 1;
        }
    }

    int low = 1;
    int high = 100;
    char response[10] = "";

    printf(_("Think of a number between %s and %s.\n"),
            (roman_flag ? roman[1] : "1"),
            (roman_flag ? roman[100] : "100"));

    while (low < high) {
        int guess = low + (high - low) / 2;
        char str_buf[10] = {};
        char roman_buf[ROMAN_MAX_SIZE] = {};
        sprintf(str_buf, "%d", guess);
        dec2rom(guess, roman_buf, ROMAN_MAX_SIZE);
        printf(_("Is your number greater than %s? (Yes/No)\n"),
                (roman_flag ? roman_buf : str_buf));

        while (1) {
            if (scanf("%s", response) != 1) {
                printf(_("\nInput closed unexpectedly. Exiting.\n"));
                return 1;
            }

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            if (strcmp(response, _("Yes")) == 0) {
                low = guess + 1;
                break;
            } else if (strcmp(response, _("No")) == 0) {
                high = guess;
                break;
            } else {
                printf(_("Invalid input. Please enter 'Yes' or 'No'.\n"));
            }
        }
    }

    char str_buf[10] = {};
    char roman_buf[ROMAN_MAX_SIZE] = {};
    sprintf(str_buf, "%d", low);
    dec2rom(low, roman_buf, ROMAN_MAX_SIZE);
    printf(_("Your number is %s!\n"),
            (roman_flag ? roman_buf : str_buf));
    return 0;
}
