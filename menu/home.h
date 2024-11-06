#ifndef home_h
#define home_h
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define WHITE       "\033[37m"
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"

typedef struct Options {
    char **ops;
    int len;
    char *title;
} Options;

int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;

    while (*text) {
        if (*text == '\033') {
            in_escape = 1;
        } else if (in_escape && *text == 'm') {
            in_escape = 0;
        } else if (!in_escape) {
            len++;
        }
        text++;
    }

    return len;
}

void print_centered(const char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int text_len = visible_length(text);
    int padding = (console_width - text_len) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    printf("%s\n", text);
}

void draw(int op, Options options) {
    system("cls");
    char line[100];
    sprintf(line, MAGENTA BOLD "%s\n" RESET, options.title);
    print_centered(line);

    for (int i = 0; i < options.len; i++) {
        const char *color;
        if (strcmp(options.ops[i], "client") == 0) {
            color = GREEN;
        } else if (strcmp(options.ops[i], "receptionist") == 0 || strcmp(options.ops[i], "manager") == 0) {
            color = BLUE;
        } else if (strcmp(options.ops[i], "exit") == 0) {
            color = RED;
        } else {
            color = WHITE;
        }

        if (op == i) {
            sprintf(line, "%s" BOLD "[ %s ]" RESET, color, options.ops[i]);
        } else {
            sprintf(line, "%s  %s  " RESET, color, options.ops[i]);
        }

        print_centered(line);
    }
}

int select_menu(Options options) {
    int current_option = options.len - 1;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option, options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option, options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len - 1) {
                        current_option++;
                        draw(current_option, options);
                    }
                    break;
                case VK_RETURN:
                    if (strcmp(options.ops[current_option], "exit") == 0) {
                        return -1;  // Return -1 to indicate exit
                    }
                    return current_option;
            }
        }
    }
}
#endif 