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


    return 0;
}
