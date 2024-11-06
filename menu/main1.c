#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "identif.h"
#include <windows.h>
#include "home.h"
#include "manager.h"

int main() {
    Options options;
    char *MAIN_OPTIONS[] = {
        "client",
        "receptionist",
        "manager",
        "exit"
    };

    options.title = "MAIN MENU";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    if (option == -1) {
        printf("Exiting program.\n");
        return 0;
    }
    else if (option==2)
    {   
        login(1);
        system("cls");
        Options options;
        char *MAIN_OPTIONS[] = {
            "employers",
            "stoke",
            "raport",
            "exit"
        };

        options.title = "MAIN MENU";
        options.ops = MAIN_OPTIONS;
        options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

        int option = select_menu(options);
        printf("# selected: %s\n", options.ops[option]);
    }
    
    return 0;
}