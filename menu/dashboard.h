#ifndef dashboard_h
#define dashboard_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"

// Structure for dishes
typedef struct {
    int id;                   // Unique identifier
    char category[30];        // Category (e.g., "Main Course", "Dessert")
    char name[50];            // Name of the dish
    float price;              // Price
} Dish;

// Structure for drinks
typedef struct {
    int id;                   // Unique identifier
    char name[50];            // Name of the drink
    float price;              // Price
} Drink;

// Function prototypes
void addDish();
void addDrink();
void displayMenu();
void editDish();
void editDrink();
void deleteDish();
void deleteDrink();
int getNextDishID();
int getNextDrinkID();
void afficherInfosRestaurant();

// Binary file paths
const char *dishFilePath = "dishes.bin";
const char *drinkFilePath = "drinks.bin";

// Main function
// Menu function

// Function to get the next unique ID for a dish
int getNextDishID() {
    FILE *file = fopen(dishFilePath, "rb");
    if (!file) return 1; // If file doesn't exist, start IDs from 1

    Dish dish;
    fseek(file,  -(long)sizeof(Dish), SEEK_END);
    if (fread(&dish, sizeof(Dish), 1, file) == 1) {
        fclose(file);
        return dish.id + 1;
    }

    fclose(file);
    return 1;
}

// Function to get the next unique ID for a drink
int getNextDrinkID() {
    FILE *file = fopen(drinkFilePath, "rb");
    if (!file) return 1; // If file doesn't exist, start IDs from 1

    Drink drink;
    fseek(file, -(long)sizeof(Drink), SEEK_END);
    if (fread(&drink, sizeof(Drink), 1, file) == 1) {
        fclose(file);
        return drink.id + 1;
    }

    fclose(file);
    return 1;
}

// Add a new dish
void addDish() {
    FILE *file = fopen(dishFilePath, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Dish dish;
    dish.id = getNextDishID();

    printf("Enter Dish Details:\n");
    printf("Category: ");
    scanf("%s", dish.category);
    printf("Name: ");
    scanf(" %[^\n]s", dish.name);
    printf("Price: ");
    scanf("%f", &dish.price);

    fwrite(&dish, sizeof(Dish), 1, file);
    fclose(file);

    printf("Dish added successfully with ID %d!\n", dish.id);
}

// Add a new drink
void addDrink() {
    FILE *file = fopen(drinkFilePath, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Drink drink;
    drink.id = getNextDrinkID();

    printf("Enter Drink Details:\n");
    printf("Name: ");
    scanf(" %[^\n]s", drink.name);
    printf("Price: ");
    scanf("%f", &drink.price);

    fwrite(&drink, sizeof(Drink), 1, file);
    fclose(file);

    printf("Drink added successfully with ID %d!\n", drink.id);
}

// Display the menu
void displayMenu() {
    FILE *dishFile = fopen(dishFilePath, "rb");
    FILE *drinkFile = fopen(drinkFilePath, "rb");

    if (!dishFile || !drinkFile) {
        printf("Error opening files!\n");
        return;
    }

    Dish dish;
    Drink drink;

    printf("\n=========== MENU ===========\n");

    printf("\nDishes:\n");
    printf("No\tCategory\tName\t\t\tPrice\n");
    while (fread(&dish, sizeof(Dish), 1, dishFile)) {
        printf("%d\t%s\t\t%s\t\t$%.2f\n", dish.id, dish.category, dish.name, dish.price);
    }

    printf("\nDrinks:\n");
    printf("No\tName\t\t\tPrice\n");
    while (fread(&drink, sizeof(Drink), 1, drinkFile)) {
        printf("%d\t%s\t\t\t$%.2f\n", drink.id, drink.name, drink.price);
    }

    fclose(dishFile);
    fclose(drinkFile);
}

// Edit a dish
void editDish() {
    FILE *file = fopen(dishFilePath, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    Dish dish;
    int found = 0;

    printf("Enter the ID of the dish to edit: ");
    scanf("%d", &id);

    while (fread(&dish, sizeof(Dish), 1, file)) {
        if (dish.id == id) {
            found = 1;
            printf("Enter new details for Dish ID %d:\n", id);
            printf("Category: ");
            scanf("%s", dish.category);
            printf("Name: ");
            scanf(" %[^\n]s", dish.name);
            printf("Price: ");
            scanf("%f", &dish.price);

            fseek(file,  -(long)sizeof(Dish), SEEK_CUR);
            fwrite(&dish, sizeof(Dish), 1, file);
            printf("Dish updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Dish with ID %d not found.\n", id);
    }

    fclose(file);
}

// Edit a drink
void editDrink() {
    FILE *file = fopen(drinkFilePath, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    Drink drink;
    int found = 0;

    printf("Enter the ID of the drink to edit: ");
    scanf("%d", &id);

    while (fread(&drink, sizeof(Drink), 1, file)) {
        if (drink.id == id) {
            found = 1;
            printf("Enter new details for Drink ID %d:\n", id);
            printf("Name: ");
            scanf(" %[^\n]s", drink.name);
            printf("Price: ");
            scanf("%f", &drink.price);

            fseek(file, -(long)sizeof(Drink), SEEK_CUR);
            fwrite(&drink, sizeof(Drink), 1, file);
            printf("Drink updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Drink with ID %d not found.\n", id);
    }

    fclose(file);
}

// Delete a dish
void deleteDish() {
    FILE *file = fopen(dishFilePath, "rb");
    FILE *tempFile = fopen("temp.bin", "wb");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    Dish dish;
    int found = 0;

    printf("Enter the ID of the dish to delete: ");
    scanf("%d", &id);

    while (fread(&dish, sizeof(Dish), 1, file)) {
        if (dish.id == id) {
            found = 1;
            continue; // Skip writing this record to the temp file
        }
        fwrite(&dish, sizeof(Dish), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(dishFilePath);
    rename("temp.bin", dishFilePath);

    if (found) {
        printf("Dish deleted successfully!\n");
    } else {
        printf("Dish with ID %d not found.\n", id);
    }
}

// Delete a drink
void deleteDrink() {
    FILE *file = fopen(drinkFilePath, "rb");
    FILE *tempFile = fopen("temp.bin", "wb");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    Drink drink;
    int found = 0;

    printf("Enter the ID of the drink to delete: ");
    scanf("%d", &id);

    while (fread(&drink, sizeof(Drink), 1, file)) {
        if (drink.id == id) {
            found = 1;
            continue; // Skip writing this record to the temp file
        }
        fwrite(&drink, sizeof(Drink), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(drinkFilePath);
    rename("temp.bin", drinkFilePath);

    if (found) {
        printf("Drink deleted successfully!\n");
    } else {
        printf("Drink with ID %d not found.\n", id);
    }
}
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
#endif