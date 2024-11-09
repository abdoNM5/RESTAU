#ifndef dashboard_h
#define dashboard_h
#include <stdio.h>
#include <conio.h>
#include "conio.h"
#include <windows.h>

void afficherInfosRestaurant() {
    system("cls"); 

  
    c_gotoxy(18, 2);
    c_textcolor(11); 
    printf("========= Informations sur le Restaurant DragonWorrier =========\n");

    
    c_gotoxy(20, 4);
    c_textcolor(14); 
    printf("Nom du restaurant: ");
    c_textcolor(15); 
    printf("DragonWorrier");

  
    c_gotoxy(20, 6);
    c_textcolor(14); 
    printf("Adresse: ");
    c_textcolor(15); 
    printf("123 Rue de la Paix, Paris, France");

  
    c_gotoxy(20, 8);
    c_textcolor(14); 
    printf("Type de cuisine: ");
    c_textcolor(15); 
    printf("Fusion asiatique");

   
    c_gotoxy(20, 10);
    c_textcolor(14); 
    printf("Note: ");
    c_textcolor(15); 
    printf("4.3/5");

   
    c_gotoxy(20, 12);
    c_textcolor(14); 
    printf("Horaires: ");
    c_textcolor(15); 
    printf("Lun - Dim: 12h00 - 23h00");

    c_gotoxy(20, 14);
    c_textcolor(14); 
    printf("Description: ");
    c_textcolor(15); 
    printf("Restaurant tendance offrant des plats fusion ");
    c_gotoxy(31,15);
    printf("asiatiques avec une ambiance moderne et relaxante.");

    c_gotoxy(20, 17);
    c_textcolor(14); 
    printf("Specialites: ");
    c_textcolor(15); 
    printf("Sushi en la francaise, Poulet au curry vert, Nouilles");
    c_gotoxy(31,18);
    printf("sautees aux legumes.");

    c_gotoxy(20, 20);
    c_textcolor(14); 
    printf("Options de paiement: ");
    c_textcolor(15); 
    printf("Cartes bancaires, especes, paiement mobile");

    c_gotoxy(20, 22);
    c_textcolor(14); 
    printf("Avis des clients: ");
    c_textcolor(15); 
    printf("\"Excellente cuisine avec un service impeccable!\"");
    c_gotoxy(38,23);
    printf(" - Marie L.MIEIC");

    c_gotoxy(20, 25);
    c_textcolor(14); 
    printf("Contact: ");
    c_textcolor(15); 
    printf("+33 1 23 45 67 89");

    c_gotoxy(20, 27);
    c_textcolor(14); 
    printf("Facebook: ");
    c_textcolor(15); 
    printf("DRAGON'S CHEFS");

    c_gotoxy(20, 29);
    c_textcolor(14); 
    printf("Instagram: ");
    c_textcolor(15); 
    printf("ChefSOFDRAGON92");
    c_textcolor(6); 

    c_gotoxy(23, 31);
    printf("Appuyez sur n'importe quelle touche pour quitter...");
    c_getch();
}





#endif