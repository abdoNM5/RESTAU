#include <stdio.h>
#include <stdlib.h>
#include "headerrestau.h"
#include <string.h>
#include <conio.h>
int main()
{   setTextColor(13);
    printf("WELCOME TO THE OFFICIAL WEB SITE  OF RESTAU ID1");
    resetColor();
    setTextColor(13);
    setCursorPosition(3,5);
    printf("here is our MENU ");
    resetColor();
    displayBoissons();
    displayPetitDejeuner();
    displayDejeuner();
    displayDiner();
    setTextColor(4);
printf("LOGIN FORM \n");
  // Prompt for username
  char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    // Prompt for password with masking
    inputPassword(password);

    // Authenticate the user
    if (authenticate(username, password)) {
        printf("Authentication successful!\n");
    } else {
        printf("Authentication failed. Invalid username or password.\n");
    }
resetColor();

    setTextColor(4);
printf("HERE IS OUR CONTACT INFO IF YOU WANNA MAKE A RESERVATION \n");
printf("Tele : 0612345678  \n");
printf("Email:id1restau@gmail.com \n");
printf("ADRESS :BOUKIDAN AL HOCEIMA 422 \n");
    return 0;
}
