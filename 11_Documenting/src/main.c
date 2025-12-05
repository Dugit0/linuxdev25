#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext(string)
#define PACKAGE "guess"
#define LOCALEDIR "locale"

char roman[101][11] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    bind_textdomain_codeset(PACKAGE, "UTF-8");

    int low = 1;
    int high = 100;
    char response[10] = "";
    int roman_flag = 1;

    printf(_("Think of a number between %s and %s.\n"),
            (roman_flag ? roman[1] : "1"),
            (roman_flag ? roman[100] : "100"));

    while (low < high) {
        int guess = low + (high - low) / 2;
        char str_buf[10] = {};
        sprintf(str_buf, "%d", guess);
        printf(_("Is your number greater than %s? (Yes/No)\n"),
                (roman_flag ? roman[guess] : str_buf));

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
    sprintf(str_buf, "%d", low);
    printf(_("Your number is %s!\n"),
            (roman_flag ? roman[low] : str_buf));
    return 0;
}
