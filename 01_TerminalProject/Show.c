#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


// #define DEBUG
#define DX 3

unsigned int min(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Argument 'file' is missing.\n");
        return 1;
    } else if (argc > 2) {
        printf("Too many arguments.\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Can't open file.\n");
        return 1;
    }

    size_t lines_cap = 8;
    char** lines = calloc(lines_cap, sizeof(*lines));

    size_t len = 0;
    ssize_t read;
    size_t lines_size = 0;
    size_t max_str_len = 0;

    while ((read = getline(&lines[lines_size], &len, fp)) != -1) {
        size_t cur_len = strlen(lines[lines_size]);
        if (max_str_len < cur_len) {
            max_str_len = cur_len;
        }
        lines_size++;
        if (lines_size == lines_cap) {
            lines_cap *= 2;
            lines = realloc(lines, sizeof(*lines) * lines_cap);
            for (size_t i = lines_size; i < lines_cap; i++) {
                lines[i] = NULL;
            }
        }
    }

    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();

    int win_height = LINES - 2*DX;
    int win_width = COLS - 2*DX;
    win = newwin(win_height, win_width, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

#ifdef DEBUG
    FILE* log = fopen("log.log", "w");
#endif

    unsigned int cur_str = 0;
    unsigned int cur_col = 0;
    int flag = 0;
    while (1) {
        werase(win);
        wprintw(win, "\n"); // for box border
        for (size_t i = cur_str; i < min(cur_str + win_height - DX + 1, lines_size); i++) {
            wprintw(win, " "); // for box border
            for (size_t j = cur_col; j < min(cur_col + win_width - DX, strlen(lines[i])); j++) {
                if (lines[i][j] == '\n') {
                    break;
                }
                wprintw(win, "%c", lines[i][j]);
            }
            wprintw(win, "\n");
        }
        box(win, 0, 0);
        wrefresh(win);
        switch (c = wgetch(win)) {
            case 27:
            case 'q':
                flag = 1;
                break;
            case KEY_LEFT:
            case 'h':
                if (cur_col) cur_col--;
                break;
            case ' ':
            case KEY_DOWN:
            case 'j':
                if (cur_str < lines_size - 1) cur_str++;
                break;
            case KEY_UP:
            case 'k':
                if (cur_str) cur_str--;
                break;
            case KEY_RIGHT:
            case 'l':
                if (cur_col < max_str_len - 2) cur_col++;
                break;
        }
#ifdef DEBUG
        fprintf(log, "Pressed: %c\n", c);
#endif
        if (flag) {
            break;
        }
    }
    endwin();

#ifdef DEBUG
    fclose(log);
#endif

    for (size_t i = 0; i < lines_cap; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
