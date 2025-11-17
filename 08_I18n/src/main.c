#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext(string)
#define PACKAGE "guess"
#define LOCALEDIR "locale"

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    bind_textdomain_codeset(PACKAGE, "UTF-8");

    int low = 1;
    int high = 100;
    char response[10] = "";

    printf(_("Think of a number between 1 and 100.\n"));

    while (low < high) {
        int guess = low + (high - low) / 2;
        printf(_("Is your number greater than %d? (Yes/No)\n"), guess);

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

    printf(_("Your number is %d!\n"), low);
    return 0;
}
