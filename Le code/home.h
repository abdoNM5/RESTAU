#ifndef home_h
#define home_h
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h> 

#define RESET       "\033[0m"   // Reset all styles
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Bright versions of the colors
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// Background colors
#define BG_BLACK       "\033[40m"
#define BG_RED         "\033[41m"
#define BG_GREEN       "\033[42m"
#define BG_YELLOW      "\033[43m"
#define BG_BLUE        "\033[44m"
#define BG_MAGENTA     "\033[45m"
#define BG_CYAN        "\033[46m"
#define BG_WHITE       "\033[47m"

// Bright background colors
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"


// Define ANSI codes for styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define RESET       "\033[0m"

typedef struct Options{
    char **ops;
    int len;
    char *title;
}Options;

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


void draw(int op,Options options){
    system("cls"); 
    char line[50];
    sprintf(line, BRIGHT_YELLOW BOLD "%s\n" BOLD , options.title);
    print_centered(line);
    for (int i = 0 ; i <  options.len ; i++) { 
        if (i == (options.len - 1)){
            sprintf(line,ITALIC "%s%s%s" RESET , op == i ?RESET RED "[" : BG_RED " " , options.ops[i], op == i ? RESET RED "]" : RED " ");
        }else{
        sprintf(line,ITALIC "%s%s%s" RESET, op == i ?RESET YELLOW "[" : WHITE " " , options.ops[i], op == i ?RESET YELLOW "]" : WHITE " ");
        }
        print_centered(line);  
    }  
}

int select_menu(Options options) {
    int current_option = 0;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Get the input handle

    // Set input mode to enable window input (for arrow keys)
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option , options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);  // Read input from console
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option , options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len-1) {
                        current_option++;
                        draw(current_option , options);
                    }
                    break;
                case VK_RETURN:  // Enter key pressed
                    return current_option;
            }
        }
    }
}

Options util(char *titre ,char **list_ops){
    Options options;

     options.title = titre;
     options.ops = list_ops;
     options.len = sizeof(list_ops) / sizeof(list_ops[0]);

     return options;
}


#define GOTOXY(x, y) printf("\033[%d;%dH", (y), (x))

// Function to display "Veuillez patienter" with a loading animation
void veuillez_patientez() {
    const char *loading_symbols = "|/-\\"; // Spinning symbols
    const int delay = 100000; // Delay in microseconds (200ms)
    const char *colors[] = {RED, YELLOW, GREEN, CYAN, MAGENTA, BLUE}; // Array of colors
    const int color_count = 6; // Number of colors

    // Move cursor to x=40, y=19
    GOTOXY(40, 17);
    printf(BOLD CYAN "Please wait ! ..." RESET); // Styled "Veuillez patienter"
    fflush(stdout);

    for (int i = 0; i < 30; i++) { // Loop to simulate loading for a few seconds
        // Print spinner at the same position
        printf("\b%s%c" RESET, colors[i % color_count], loading_symbols[i % 4]);
        fflush(stdout); // Flush output to update the symbol instantly
        usleep(delay);  // Wait for a short period (200ms)
    }
   
}
void image(const char *filepath) {
    char commandI[512];

    // Format the command to open the image
    snprintf(commandI, sizeof(commandI), "start \"\" \"%s\"", filepath);

    // Execute the command
    int result = system(commandI);

    if (result != 0) {
        printf("Failed to open the image: %s\n", filepath);
    }
}
void openPDFInEdge(const char *filePath) {
    char command[512]; // Buffer to hold the PowerShell command

    // Format the command to open the PDF in Microsoft Edge
    snprintf(command, sizeof(command), "powershell -Command \"Start-Process 'msedge.exe' -ArgumentList '%s'\"", filePath);

    // Execute the command
    int result = system(command);

    // Check if the command was executed successfully
    if (result != 0) {
        printf("Failed to open the PDF in Microsoft Edge.\n");
    } 
}

 void chcp() {
    // Execute the "chcp 65001" command in PowerShell
    system("powershell -Command \"chcp 65001\"");

}

#endif 