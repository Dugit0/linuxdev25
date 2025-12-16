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

#include "roman.h"

#define _(string) gettext(string)
#define PACKAGE "guess"
#define LOCALEDIR "locale"


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
    char roman1[ROMAN_MAX_SIZE] = "";
    dec2rom(1, roman1, ROMAN_MAX_SIZE);
    char roman100[ROMAN_MAX_SIZE] = "";
    dec2rom(100, roman100, ROMAN_MAX_SIZE);

    printf(_("Think of a number between %s and %s.\n"),
            (roman_flag ? roman1 : "1"),
            (roman_flag ? roman100 : "100"));

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
