#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rhash.h>
#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

// Функция для вывода хеша в нужном формате
void print_hash(unsigned char *hash, int hash_len, int uppercase) {
    if (uppercase) {
        rhash_print_bytes(stdout, hash, hash_len, RHPR_HEX);
    } else {
        rhash_print_bytes(stdout, hash, hash_len, RHPR_BASE64);
    }
    printf("\n");
}

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    rhash_library_init(); // Инициализируем библиотеку

    while (1) {
#ifdef USE_READLINE
        // Используем readline, если определено
        if (isatty(fileno(stdin))) { // Проверяем, интерактивный ли ввод
             line = readline("rhasher> ");
        } else {
             if (getline(&line, &len, stdin) == -1) {
                 break;
             }
        }

        if (line == NULL) { // Ctrl+D
            break;
        }

        if (*line) {
            add_history(line);
        }
#else
        // Используем getline по умолчанию
        if (isatty(fileno(stdin))) {
             printf("rhasher> ");
             fflush(stdout);
        }
        if ((read = getline(&line, &len, stdin)) == -1) {
            break; // Ctrl+D
        }
#endif

        char *command = strtok(line, " \t\n");
        char *argument = strtok(NULL, " \t\n");

        if (command == NULL || argument == NULL) {
            fprintf(stderr, "Error: missing command or argument\n");
            continue;
        }

        int hash_id = 0;
        if (strcasecmp(command, "MD5") == 0) {
            hash_id = RHASH_MD5;
        } else if (strcasecmp(command, "SHA1") == 0) {
            hash_id = RHASH_SHA1;
        } else if (strcasecmp(command, "TTH") == 0) {
            hash_id = RHASH_TTH;
        } else {
            fprintf(stderr, "Error: unknown hash algorithm '%s'\n", command);
            continue;
        }

        int uppercase = isupper(command[0]);
        unsigned char digest[64]; // Буфер для результата

        if (argument[0] == '"') { // Считаем хеш строки
            char *str_to_hash = argument + 1;
            size_t str_len = strlen(str_to_hash);
            if (str_to_hash[str_len - 1] == '"') {
                 str_to_hash[str_len - 1] = '\0';
            }

            int res = rhash_msg(hash_id, str_to_hash, strlen(str_to_hash), digest);
            if (res < 0) {
                fprintf(stderr, "Error: failed to compute hash for string\n");
                continue;
            }
            print_hash(digest, rhash_get_digest_size(hash_id), uppercase);

        } else { // Считаем хеш файла
            int res = rhash_file(hash_id, argument, digest);
            if (res < 0) {
                fprintf(stderr, "Error: failed to compute hash for file '%s'\n", argument);
                continue;
            }
            print_hash(digest, rhash_get_digest_size(hash_id), uppercase);
        }
#ifdef USE_READLINE
        free(line);
        line = NULL;
#endif
    }

    if (line) {
        free(line);
    }
    printf("\n"); // Для красивого выхода по Ctrl+D
    return 0;
}
