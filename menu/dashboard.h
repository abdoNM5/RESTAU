#ifndef dashboard_h
#define dashboard_h
#include <stdio.h>
#include <conio.h>
#include "conio.h"
#include <windows.h>

void afficherInfosRestaurant() {
    system("cls"); 

  
    c_gotoxy(18, 2);
    c_textbackground(11);
    c_textcolor(0); 
    printf("============== Informations sur le Restaurant DragonWorrier ==============\n");

    c_textbackground(0);
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
    c_gotoxy(33,15);
    printf("asiatiques avec une ambiance moderne et relaxante.");

    c_gotoxy(20, 17);
    c_textcolor(14); 
    printf("Specialites: ");
    c_textcolor(15); 
    printf("Sushi en la francaise, Poulet au curry vert, Nouilles");
    c_gotoxy(33,18);
    printf("sautees aux legumes.");

    c_gotoxy(20, 20);
    c_textcolor(14); 
    printf("Options de paiement: ");
    c_textcolor(15); 
    printf("Cartes bancaires, especes, paiement mobile");

    c_gotoxy(20, 22);
    c_textcolor(14); 
    printf("Options de commande: ");
    c_textcolor(15); 
    printf("Reservation, Commande in , en porter , livraison");

    c_gotoxy(20, 24);
    c_textcolor(14); 
    printf("Avis des clients: ");
    c_textcolor(15); 
    printf("\"Excellente cuisine avec un service impeccable!\"");
    c_gotoxy(38,25);
    printf(" - Marie L.MIEIC");

    c_gotoxy(20, 27);
    c_textcolor(14); 
    printf("Contact: ");
    c_textcolor(15); 
    printf("+33 1 23 45 67 89");

    c_gotoxy(20, 29);
    c_textcolor(14); 
    printf("Facebook: ");
    c_textcolor(15); 
    printf("DRAGON'S CHEFS");

    c_gotoxy(20, 31);
    c_textcolor(14); 
    printf("Instagram: ");
    c_textcolor(15); 
    printf("ChefSOFDRAGON92");
    c_textcolor(6); 

    c_gotoxy(75, 31);
    printf("Appuyez sur une touche pour quitter...");
    c_getch();
}


void displayMenuTable() {
    system("cls"); 

    c_gotoxy(7, 1);
    c_textcolor(15); 
    c_textbackground(11);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    c_gotoxy(7, 2);
    c_textcolor(0);
    printf
    ("             ========= MENU OF DRAGANWORRIER RESTAURANT =========               ");
    c_gotoxy(7, 3);
    c_textcolor(15);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    c_textbackground(0);
    
    c_gotoxy(10, 5);
    c_textcolor(14); 
    printf("No.");
    c_gotoxy(20, 5);
    printf("Category");
    c_gotoxy(40, 5);
    printf("Dish Name");
    c_gotoxy(65, 5);
    printf("Price (USD)");

    c_textcolor(0); 
    c_textbackground(11);
    c_gotoxy(7, 6);
    printf("=======================================================================");
    c_textbackground(0);
    c_textcolor(14); c_gotoxy(10, 7); printf("1"); c_textcolor(15); c_gotoxy(20, 7); printf("Appetizer"); c_gotoxy(40, 7); printf("Thai Salad"); c_textcolor(2); c_gotoxy(65, 7); printf("8.50 USD");
    c_textcolor(14); c_gotoxy(10, 8); printf("2"); c_textcolor(15); c_gotoxy(20, 8); printf("Appetizer"); c_gotoxy(40, 8); printf("Chicken Gyoza"); c_textcolor(2); c_gotoxy(65, 8); printf("7.00 USD");
    c_textcolor(14); c_gotoxy(10, 9); printf("3"); c_textcolor(15); c_gotoxy(20, 9); printf("Appetizer"); c_gotoxy(40, 9); printf("Spring Rolls"); c_textcolor(2); c_gotoxy(65, 9); printf("6.00 USD");
    c_textcolor(14); c_gotoxy(10, 10); printf("4"); c_textcolor(15); c_gotoxy(20, 10); printf("Appetizer"); c_gotoxy(40, 10); printf("Tempura"); c_textcolor(2); c_gotoxy(65, 10); printf("8.00 USD");

// Main Courses
    c_textcolor(14); c_gotoxy(10, 11); printf("5"); c_textcolor(15); c_gotoxy(20, 11); printf("Main Course"); c_gotoxy(40, 11); printf("Green Curry Chicken"); c_textcolor(2); c_gotoxy(65, 11); printf("14.50 USD");
    c_textcolor(14); c_gotoxy(10, 12); printf("6"); c_textcolor(15); c_gotoxy(20, 12); printf("Main Course"); c_gotoxy(40, 12); printf("Stir-fried Vegetables"); c_textcolor(2); c_gotoxy(65, 12); printf("13.00 USD");
    c_textcolor(14); c_gotoxy(10, 13); printf("7"); c_textcolor(15); c_gotoxy(20, 13); printf("Main Course"); c_gotoxy(40, 13); printf("Salmon Teriyaki"); c_textcolor(2); c_gotoxy(65, 13); printf("15.00 USD");
    c_textcolor(14); c_gotoxy(10, 14); printf("8"); c_textcolor(15); c_gotoxy(20, 14); printf("Main Course"); c_gotoxy(40, 14); printf("Beef Bulgogi"); c_textcolor(2); c_gotoxy(65, 14); printf("16.00 USD");
    c_textcolor(14); c_gotoxy(10, 15); printf("9"); c_textcolor(15); c_gotoxy(20, 15); printf("Main Course"); c_gotoxy(40, 15); printf("Shrimp Pad Thai"); c_textcolor(2); c_gotoxy(65, 15); printf("14.00 USD");
    c_textcolor(14); c_gotoxy(10, 16); printf("10"); c_textcolor(15); c_gotoxy(20, 16); printf("Main Course"); c_gotoxy(40, 16); printf("Spicy Tuna Roll"); c_textcolor(2); c_gotoxy(65, 16); printf("12.50 USD");
    c_textcolor(14); c_gotoxy(10, 17); printf("11"); c_textcolor(15); c_gotoxy(20, 17); printf("Main Course"); c_gotoxy(40, 17); printf("Sushi Platter"); c_textcolor(2); c_gotoxy(65, 17); printf("18.00 USD");
    c_textcolor(14); c_gotoxy(10, 18); printf("12"); c_textcolor(15); c_gotoxy(20, 18); printf("Main Course"); c_gotoxy(40, 18); printf("Chicken Katsu"); c_textcolor(2); c_gotoxy(65, 18); printf("13.50 USD");
    c_textcolor(14); c_gotoxy(10, 19); printf("13"); c_textcolor(15); c_gotoxy(20, 19); printf("Main Course"); c_gotoxy(40, 19); printf("BBQ Pork Ribs"); c_textcolor(2); c_gotoxy(65, 19); printf("16.50 USD");

// Desserts
    c_textcolor(14); c_gotoxy(10, 20); printf("14"); c_textcolor(15); c_gotoxy(20, 20); printf("Dessert"); c_gotoxy(40, 20); printf("Mochi Ice Cream"); c_textcolor(2); c_gotoxy(65, 20); printf("6.50 USD");
    c_textcolor(14); c_gotoxy(10, 21); printf("15"); c_textcolor(15); c_gotoxy(20, 21); printf("Dessert"); c_gotoxy(40, 21); printf("Matcha Tart"); c_textcolor(2); c_gotoxy(65, 21); printf("7.00 USD");
    c_textcolor(14); c_gotoxy(10, 22); printf("16"); c_textcolor(15); c_gotoxy(20, 22); printf("Dessert"); c_gotoxy(40, 22); printf("Mango Soup"); c_textcolor(2); c_gotoxy(65, 22); printf("6.00 USD");
    c_textcolor(14); c_gotoxy(10, 23); printf("17"); c_textcolor(15); c_gotoxy(20, 23); printf("Dessert"); c_gotoxy(40, 23); printf("Green Tea Cheesecake"); c_textcolor(2); c_gotoxy(65, 23); printf("7.50 USD");
    c_textcolor(14); c_gotoxy(10, 24); printf("18"); c_textcolor(15); c_gotoxy(20, 24); printf("Dessert"); c_gotoxy(40, 24); printf("Chocolate Lava Cake"); c_textcolor(2); c_gotoxy(65, 24); printf("8.00 USD");
    c_textcolor(14); c_gotoxy(10, 25); printf("19"); c_textcolor(15); c_gotoxy(20, 25); printf("Dessert"); c_gotoxy(40, 25); printf("Vanilla Panna Cotta"); c_textcolor(2); c_gotoxy(65, 25); printf("7.00 USD");
    c_textcolor(14); c_gotoxy(10, 26); printf("20"); c_textcolor(15); c_gotoxy(20, 26); printf("Dessert"); c_gotoxy(40, 26); printf("Caramel Flan"); c_textcolor(2); c_gotoxy(65, 26); printf("6.50 USD");
    c_textcolor(14); c_gotoxy(10, 27); printf("21"); c_textcolor(15); c_gotoxy(20, 27); printf("Dessert"); c_gotoxy(40, 27); printf("Fruit Parfait"); c_textcolor(2); c_gotoxy(65, 27); printf("5.50 USD");
    c_textcolor(14); c_gotoxy(10, 28); printf("22"); c_textcolor(15); c_gotoxy(20, 28); printf("Dessert"); c_gotoxy(40, 28); printf("Matcha Roll Cake"); c_textcolor(2); c_gotoxy(65, 28); printf("6.50 USD");

    c_textbackground(11);
    c_textcolor(0);
    c_gotoxy(7, 29);
    printf("=======================================================================");
    c_textbackground(0);
    
    c_gotoxy(85, 10);
    c_textcolor(14); 
    printf("Drink Options:");

    c_textcolor(15);  c_gotoxy(85, 11); printf("- Matcha Green Tea: ");c_textcolor(2); printf("3.00 USD");
    c_textcolor(15);  c_gotoxy(85, 12); printf("- Homemade Lemonade: ");c_textcolor(2); printf("4.50 USD");
    c_textcolor(15);  c_gotoxy(85, 13); printf("- Mineral Water: ");c_textcolor(2); printf("2.00 USD");
    c_textcolor(15);  c_gotoxy(85, 14); printf("- Coconut Water: ");c_textcolor(2); printf("3.50 USD");
    c_textcolor(15);  c_gotoxy(85, 15); printf("- Sparkling Water: ");c_textcolor(2); printf("3.00 USD");
    c_textcolor(15);  c_gotoxy(85, 16); printf("- Iced Coffee: ");c_textcolor(2); printf("4.00 USD");
    c_textcolor(15);  c_gotoxy(85, 17); printf("- Mango Smoothie: ");c_textcolor(2); printf("5.00 USD");
    c_textcolor(15);  c_gotoxy(85, 18); printf("- Berry Iced Tea: ");c_textcolor(2); printf("4.50 USD");

    
    c_gotoxy(90, 31);
    c_textcolor(6); 
    printf("Press any key to exit...");
    c_getch();
    c_textcolor(15); 
}

#endif