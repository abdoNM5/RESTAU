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
    {"ABDELKADER", "2005"} // Receptionist credentials
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
            password[index] = '\0'; // Terminer la chaine
            break;
        } else if (ch == '\b' && index > 0) { 
            printf("\b \b"); // Supprimer le dernier asterisque affiche
            index--;
        } else if (index < maxLength - 1) {
            putchar('*'); // Affiche un asterisque
            password[index] = ch; // Stocke le caractere
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
            name[index] = '\0'; // Terminer la chaine
            break;
        } else if (ch == '\b' && index > 0) { 
            printf("\b \b"); // Supprimer le dernier asterisque affiche
            index--;
        } else if (index < maxLength - 1) {
            putchar(ch); // Affiche un asterisque
            name[index] = ch; // Stocke le caractere
            index++;
        }
    }
    printf("\n");
}

void login(int a) {
    int m=0;
    char password[15],name[35];
    do{
    c_textcolor(6);
    c_gotoxy(40,12);
    if(a==1) printf("======== Identification Pour GERANT ======");
    else printf("======= Identification Pour RECEPTIONNISTE =======");
        if(m!=0){
        c_textcolor(4);
        c_gotoxy(40,14);
        printf("--Vos infos ne sont pas valides--\n\n");}
        c_textcolor(15);
        c_gotoxy(40,16);
        printf("***  L'identifiant   :");
        gitUsername(name,35);
        c_gotoxy(40,18);
        printf("***  Mot_De_Passe    :");
        maskPassword(password, 15);
        system("cls");
        m++;
    }while (authenticate(name,password) == 0);
}
#endif
