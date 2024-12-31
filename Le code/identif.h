
#ifndef identif
#define identif
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "conio.h"

typedef struct {
    char username[35];
    char password[15];
} User;
User users[2] = {
    {"ABDELKABIR", "2004"},   // Manager credentials
    {"ABDELKADER", "2005"}    // Receptionist credentials
};

int authenticate(char *username, char *password) {
    int usernameValid = 0; // Flag for username validation
    int passwordValid = 0; // Flag for password validation

    for (int i = 0; i < 2; i++) {
        if (strcmp(users[i].username, username) == 0) {
            usernameValid = 1; // Username is valid
        }
        if (strcmp(users[i].password, password) == 0) {
            passwordValid = 1; // Password is valid
        }
    }
    return (usernameValid * passwordValid);
}

void maskPassword(char *password, int maxLength) {
    int index = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            password[index] = '\0'; // Terminate the string
            break;
        } else if (ch == '\b' && index > 0) {
            printf("\b \b"); // Erase the last asterisk
            index--;
        } else if (index < maxLength - 1) {
            putchar('*'); // Display an asterisk
            password[index] = ch; // Store the character
            index++;
        }
    }

    printf("\n");
}

void gitUsername(char *name, int maxLength) {
    int index = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            name[index] = '\0'; // Terminate the string
            break;
        } else if (ch == '\b' && index > 0) {
            printf("\b \b"); // Erase the last character
            index--;
        } else if (index < maxLength - 1) {
            putchar(ch); // Display the character
            name[index] = ch; // Store the character
            index++;
        }
    }
    printf("\n");
}

void drawEmptyBox(int x, int y, int width) {
    // Top border
    c_gotoxy(x, y);
    printf("╭");
    for (int i = 0; i < width; i++) printf("─");
    printf("╮");

    // Empty middle line
    c_gotoxy(x, y + 1);
    printf("│");
    for (int i = 0; i < width; i++) printf(" ");
    printf("│");

    // Bottom border
    c_gotoxy(x, y + 2);
    printf("╰");
    for (int i = 0; i < width; i++) printf("─");
    printf("╯");
}

void login(int a) {
    int m = 0;
    char password[15], name[35];
    do {
        system("cls");

        // Title
        c_textcolor(6);
        c_gotoxy(40, 12);
        if (a == 1)
            printf("======== Identification Pour GERANT ======");
        else
            printf("======= Identification Pour RECEPTIONNISTE =======");

        // Error Message
        if (m != 0) {
            c_textcolor(4);
            c_gotoxy(40, 14);
            printf("--Vos infos ne sont pas valides--\n\n");
        }

        // "Identifiant" Label and Box
        c_textcolor(15);
        c_gotoxy(40, 16);
        printf("Identifiant:");
        drawEmptyBox(60, 15, 30); // Draw rectangle at fixed position
        c_gotoxy(62, 16);         // Position cursor inside the box for input
        gitUsername(name, 35);

        // "Mot de Passe" Label and Box
        c_gotoxy(40, 20);
        printf("Mot de Passe:");
        drawEmptyBox(60, 19, 30); // Draw rectangle at fixed position
        c_gotoxy(62, 20);         // Position cursor inside the box for input
        maskPassword(password, 15);

        m++;
    } while (authenticate(name, password) == 0);
}
#endif