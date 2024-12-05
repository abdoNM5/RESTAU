#ifndef HOME_H
#define HOME_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Define ANSI color codes
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define WHITE       "\033[37m"

// Define ANSI codes for styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"

typedef struct Options {
    char **ops;
    int len;
    char *title;
} Options;

// Function to calculate the visible length of a string (ignoring ANSI codes)
int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;
    
    while (*text) {
        if (*text == '\033') {  // Start of escape sequence
            in_escape = 1;
        } else if (in_escape && *text == 'm') {  // End of escape sequence
            in_escape = 0;
        } else if (!in_escape) {
            len++;  // Count visible characters
        }
        text++;
    }
    
    return len;
}

// Function to center text with ANSI codes based on console width
void print_centered(const char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Calculate the console width
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate the visible text length (ignoring ANSI codes)
    int text_len = visible_length(text);

    // Calculate padding
    int padding = (console_width - text_len) / 2;

    // Print padding spaces
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Print the actual text with ANSI color codes
    printf("%s\n", text);
}

// Function to draw the menu with options
void draw(int op, Options options) {
    system("cls");  // Clear the screen
    char line[50];

    // Print the title centered
    sprintf(line, BOLD "%s\n" RESET, options.title);
    print_centered(line);

    // Display options
    for (int i = 0; i < options.len; i++) {
        if (i == op) {  // Highlight the selected option
            sprintf(line, ITALIC "%s%s%s" RESET, BOLD RED "[", options.ops[i], RED "]");
        } else {  // Non-selected options
            sprintf(line, ITALIC "%s%s%s" RESET, WHITE " ", options.ops[i], WHITE " ");
        }
        print_centered(line);
    }
}

// Function to handle menu selection with the up arrow
int select_menu(Options options) {
    int current_option = 0;  // Start with the first option selected
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Get the input handle

    // Set input mode to enable window input (for arrow keys)
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option, options);

    INPUT_RECORD input;
    DWORD events;

    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);  // Read input from console
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:  // Use the up arrow to scroll
                    current_option--;  // Move up
                    if (current_option < 0) {  // Wrap around to the last option
                        current_option = options.len - 1;
                    }
                    draw(current_option, options);
                    break;

                case VK_RETURN:  // Enter key pressed
                    return current_option;
            }
        }
    }
}

// Function to create options structure
Options util(char *titre, char **list_ops, int len) {
    Options options;

    options.title = titre;
    options.ops = list_ops;
    options.len = len;

    return options;
}

#endif
 