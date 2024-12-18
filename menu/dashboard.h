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
    int id;  
    char category[30];                 // Unique identifier
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
        c_textcolor(4); // Red for error
        c_gotoxy(50, 20);
        printf("Error opening file!\n");
        c_textcolor(15); // Reset to default
        return;
    }

    Dish dish;
    dish.id = getNextDishID(); // Assuming this function handles the ID incrementation.

    c_textcolor(14); // Yellow for prompts
    c_gotoxy(50, 12);
    printf("Enter Dish Details:");

    c_gotoxy(32, 14);
    printf("Category: ");
    c_textcolor(15); // White for input
    scanf("%s", dish.category);
    
    c_textcolor(14); // Yellow for prompts
    c_gotoxy(32, 15);
    printf("Name: ");
    c_textcolor(15); // White for input
    scanf(" %[^\n]s", dish.name);
    
    c_textcolor(14); // Yellow for prompts
    c_gotoxy(32, 16);
    printf("Price: ");
    c_textcolor(15); // White for input
    scanf("%f", &dish.price);

    fwrite(&dish, sizeof(Dish), 1, file);
    fclose(file);

    c_textcolor(10); // Green for success
    c_gotoxy(50, 18);
    printf("Dish added successfully with ID %d!\n", dish.id);
    c_textcolor(15); // Reset to default
}


// Add a new drink
void addDrink() {
    FILE *file = fopen(drinkFilePath, "ab");
    if (!file) {
        c_textcolor(4); // Red for error
        c_gotoxy(50, 20);
        printf("Error opening file!\n");
        c_textcolor(15); // Reset to default
        return;
    }

    Drink drink;
    drink.id = getNextDrinkID(); // Assuming this function handles the ID incrementation.

    c_textcolor(14); // Yellow for prompts
    c_gotoxy(50, 12);
    printf("Enter Drink Details:");

    c_gotoxy(32, 14);
    printf("Category: ");
    c_textcolor(15); // White for input
    scanf("%s", drink.category);
    
    c_textcolor(14); // Yellow for prompts
    c_gotoxy(32, 15);
    printf("Name: ");
    c_textcolor(15); // White for input
    scanf(" %[^\n]s", drink.name);
    
    c_textcolor(14); // Yellow for prompts
    c_gotoxy(32, 16);
    printf("Price: ");
    c_textcolor(15); // White for input
    scanf("%f", &drink.price);

    fwrite(&drink, sizeof(Drink), 1, file);
    fclose(file);

    c_textcolor(10); // Green for success
    c_gotoxy(50, 18);
    printf("Drink added successfully with ID %d!\n", drink.id);
    c_textcolor(15); // Reset to default
}


void displayMenu1() {
    FILE *dishFile = fopen(dishFilePath, "rb");
    FILE *drinkFile = fopen(drinkFilePath, "rb");

    if (!dishFile || !drinkFile) {
        c_textcolor(4); // Red for errors
        c_gotoxy(50, 20);
        printf("Error: Unable to open menu files!");
        c_textcolor(15); // Reset to default
        return;
    }

    Dish dish;
    Drink drink;
    char currentCategory[50] = "";

    // Step 1: Display Dishes
    c_clrscr(); // Clear screen
    c_textcolor(14); // Yellow for title
    c_gotoxy(40, 12);
    printf("================= DISHES MENU =================");

    int y = 13;
    strcpy(currentCategory, "");

    // Draw table header
    c_textcolor(11); // Cyan for header
    c_gotoxy(35, y++);
    printf("-----------------------------------------------------------------");
    c_gotoxy(35, y++);
    printf("| %-5s | %-15s | %-25s | %-7s |", "ID", "Category", "Dish Name", "Price");
    c_gotoxy(35, y++);
    printf("-----------------------------------------------------------------");

    // Start displaying dishes
    while (fread(&dish, sizeof(Dish), 1, dishFile)) {
        if (strcmp(currentCategory, dish.category) != 0) {
            // New category row
            strcpy(currentCategory, dish.category);
            c_textcolor(14); // Yellow for category
            c_gotoxy(35, y++);
            printf("| %-5s | %-15s | %-25s | %-7s |", "", currentCategory, "", "");
        }
        c_textcolor(15); // White for dish details
        c_gotoxy(35, y++);
        printf("| %-5d | %-15s | %-25s |%-6.2f DH|", dish.id, "", dish.name, dish.price);

        if (y > 30) { // Check Y limit (now 30)
            c_textcolor(9); // Navigation prompt
            c_gotoxy(50, 32);
            printf("Press any key to scroll down...");
            c_getch();
            c_clrscr();
            y = 13; // Reset position
            c_textcolor(14); // Reprint title
            c_gotoxy(40, 12);
            printf("================== DISHES MENU =================");
            c_textcolor(11); // Redraw header
            c_gotoxy(35, y++);
            printf("-----------------------------------------------------------------");
            c_gotoxy(35, y++);
            printf("| %-5s | %-15s | %-25s | %-7s |", "ID", "Category", "Dish Name", "Price");
            c_gotoxy(35, y++);
            printf("-----------------------------------------------------------------");
        }
    }
    c_gotoxy(35, y++);
    c_textcolor(11); // Cyan for footer border
    printf("-----------------------------------------------------------------");

    fclose(dishFile);

    // Wait for key press to move to Drinks
    c_textcolor(10); // Green for navigation prompt
    c_gotoxy(50, y + 1);
    printf("Press any key to view Drinks...");
    c_getch();
    c_clrscr();

    // Step 2: Display Drinks
    c_textcolor(14); // Yellow for title
    c_gotoxy(40, 12);
    printf("=============== DRINKS MENU ===============");

    y = 13;
    strcpy(currentCategory, "");

    // Draw table header for drinks
    c_textcolor(11); // Cyan for header
    c_gotoxy(35, y++);
    printf("------------------------------------------------------------------");
    c_gotoxy(35, y++);
    printf("| %-5s | %-15s | %-25s | %-7s |", "ID", "Category", "Drink Name", "Price");
    c_gotoxy(35, y++);
    printf("------------------------------------------------------------------");

    // Start displaying drinks
    while (fread(&drink, sizeof(Drink), 1, drinkFile)) {
        if (strcmp(currentCategory, drink.category) != 0) {
            // New category row
            strcpy(currentCategory, drink.category);
            c_textcolor(14); // Yellow for category
            c_gotoxy(35, y++);
            printf("| %-5s | %-15s | %-25s | %-7s |", "", currentCategory, "", "");
        }
        c_textcolor(15); // White for drink details
        c_gotoxy(35, y++);
        printf("| %-5d | %-15s | %-25s |%-6.2f DH|", drink.id, "", drink.name, drink.price);

        if (y > 30) { // Check Y limit (now 30)
            c_textcolor(9); // Navigation prompt
            c_gotoxy(50, 32);
            printf("Press any key to scroll down...");
            c_getch();
            c_clrscr();
            y = 13; // Reset position
            c_textcolor(14); // Reprint title
            c_gotoxy(40, 12);
            printf("============== DRINKS MENU ===============");
            c_textcolor(11); // Redraw header
            c_gotoxy(35, y++);
            printf("-----------------------------------------------------------------");
            c_gotoxy(35, y++);
            printf("| %-5s | %-15s | %-25s | %-7s |", "ID", "Category", "Drink Name", "Price");
            c_gotoxy(35, y++);
            printf("----------------------------------------------------------------");
        }
    }
    c_gotoxy(35, y++);
    c_textcolor(11); // Cyan for footer border
    printf("----------------------------------------------------------------");

    fclose(drinkFile);

    // Exit Message
    c_textcolor(10); // Green for navigation prompt
    c_gotoxy(50, y + 2);
    printf("Press any key to exit...");
    c_getch();
    c_textcolor(15); // Reset to default
}


void displayMenu2() {
    FILE *dishFile = fopen(dishFilePath, "rb");
    FILE *drinkFile = fopen(drinkFilePath, "rb");

    if (!dishFile || !drinkFile) {
        c_textcolor(4); // Red for errors
        c_gotoxy(50, 20);
        printf("Error: Unable to open menu files!");
        c_textcolor(15);
        return;
    }

    Dish dish;
    Drink drink;
    char currentCategory[50] = "";

    // Step 1: Display Dishes
    c_clrscr(); // Clear screen
    c_textcolor(14); // Yellow for title
    c_gotoxy(40, 12);
    printf("================= DISHES MENU =================");

    int y = 13;
    strcpy(currentCategory, "");

    // Draw table header
    c_textcolor(11); // Cyan for header
    c_gotoxy(35, y++);
    printf("---------------------------------------------------------");
    c_gotoxy(35, y++);
    printf("| %-15s | %-25s | %-7s |", "Category", "Dish Name", "Price");
    c_gotoxy(35, y++);
    printf("---------------------------------------------------------");

    // Start displaying dishes
    while (fread(&dish, sizeof(Dish), 1, dishFile)) {
        if (strcmp(currentCategory, dish.category) != 0) {
            // New category row
            strcpy(currentCategory, dish.category);
            c_textcolor(14); // Yellow for category
            c_gotoxy(35, y++);
            printf("| %-15s | %-25s | %-7s |", currentCategory, "", "");
        }
        c_textcolor(15); // White for dish details
        c_gotoxy(35, y++);
        printf("| %-15s | %-25s |%-6.2f DH|", "", dish.name, dish.price);

        if (y > 30) { // Check Y limit (now 30)
            c_textcolor(9); // Navigation prompt
            c_gotoxy(50, 32);
            printf("Press any key to scroll down...");
            c_getch();
            c_clrscr();
            y = 13; // Reset position
            c_textcolor(14); // Reprint title
            c_gotoxy(40, 12);
            printf("================== DISHES MENU =================");
            c_textcolor(11); // Redraw header
            c_gotoxy(35, y++);
            printf("---------------------------------------------------------");
            c_gotoxy(35, y++);
            printf("| %-15s | %-25s | %-7s |", "Category", "Dish Name", "Price");
            c_gotoxy(35, y++);
            printf("---------------------------------------------------------");
        }
    }
    c_gotoxy(35, y++);
    c_textcolor(11); // Cyan for footer border
    printf("---------------------------------------------------------");

    fclose(dishFile);

    // Wait for key press to move to Drinks
    c_textcolor(10); // Green for navigation prompt
    c_gotoxy(50, y + 1);
    printf("Press any key to view Drinks...");
    c_getch();
    c_clrscr();

    // Step 2: Display Drinks
    c_textcolor(14); // Yellow for title
    c_gotoxy(40, 12);
    printf("=============== DRINKS MENU ===============");

    y = 13;
    strcpy(currentCategory, "");

    // Draw table header for drinks
    c_textcolor(11); // Cyan for header
    c_gotoxy(35, y++);
    printf("---------------------------------------------------------");
    c_gotoxy(35, y++);
    printf("| %-15s | %-25s | %-7s |", "Category", "Drink Name", "Price");
    c_gotoxy(35, y++);
    printf("---------------------------------------------------------");

    // Start displaying drinks
    while (fread(&drink, sizeof(Drink), 1, drinkFile)) {
        if (strcmp(currentCategory, drink.category) != 0) {
            // New category row
            strcpy(currentCategory, drink.category);
            c_textcolor(14); // Yellow for category
            c_gotoxy(35, y++);
            printf("| %-15s | %-25s | %-7s |", currentCategory, "", "");
        }
        c_textcolor(15); // White for drink details
        c_gotoxy(35, y++);
        printf("| %-15s | %-25s |%-6.2f DH|", "", drink.name, drink.price);

        if (y > 30) { // Check Y limit (now 30)
            c_textcolor(9); // Navigation prompt
            c_gotoxy(50, 32);
            printf("Press any key to scroll down...");
            c_getch();
            c_clrscr();
            y = 13; // Reset position
            c_textcolor(14); // Reprint title
            c_gotoxy(40, 12);
            printf("============== DRINKS MENU ===============");
            c_textcolor(11); // Redraw header
            c_gotoxy(35, y++);
            printf("---------------------------------------------------------");
            c_gotoxy(35, y++);
            printf("| %-15s | %-25s | %-7s |", "Category", "Drink Name", "Price");
            c_gotoxy(35, y++);
            printf("---------------------------------------------------------");
        }
    }
    c_gotoxy(35, y++);
    c_textcolor(11); // Cyan for footer border
    printf("---------------------------------------------------------");

    fclose(drinkFile);

    // Exit Message
    c_textcolor(10); // Green for navigation prompt
    c_gotoxy(50, y + 2);
    printf("Press any key to exit...");
    c_getch();
    c_textcolor(15); // Reset to default
}

// Delete a dish
void deleteDish() {
    FILE *file = fopen(dishFilePath, "rb");
    FILE *tempFile = fopen("temp.bin", "wb");

    if (!file || !tempFile) {
        c_textcolor(4); // Red for error
        c_gotoxy(50, 20);
        printf("Error opening file!\n");
        c_textcolor(15); // Reset to default
        return;
    }

    int id;
    Dish dish;
    int found = 0;

    // Ask for the ID of the dish to delete
    
    c_textcolor(14); // Yellow for prompt
    c_gotoxy(50, 15);
    printf("Enter the ID of the dish to delete: ");
    c_textcolor(15); // White for input
    scanf("%d", &id);

    // Process deletion
    fseek(file, 0, SEEK_SET); // Reset file pointer to the start
    while (fread(&dish, sizeof(Dish), 1, file)) {
        if (dish.id == id) {
            found = 1;
            continue; // Skip this dish and do not write it to temp file
        }
        fwrite(&dish, sizeof(Dish), 1, tempFile); // Write remaining dishes
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the updated temp file
    remove(dishFilePath);
    rename("temp.bin", dishFilePath);

    if (found) {
        c_textcolor(10); // Green for success
        c_gotoxy(50, 17);
        printf("Dish deleted successfully!\n");
    } else {
        c_textcolor(4); // Red for error
        c_gotoxy(50, 17);
        printf("Dish with ID %d not found.\n", id);
    }

    c_textcolor(15); // Reset to default
    c_getch(); // Wait for key press before returning
}


// Delete a drink
void deleteDrink() {
    FILE *file = fopen(drinkFilePath, "rb");
    FILE *tempFile = fopen("temp.bin", "wb");

    if (!file || !tempFile) {
        c_textcolor(4); // Red for error
        c_gotoxy(50, 20);
        printf("Error opening file!\n");
        c_textcolor(15); // Reset to default
        return;
    }

    int id;
    Drink drink;
    int found = 0;

    // Ask for the ID of the drink to delete
    c_clrscr(); // Clear the screen for better UI
    c_textcolor(14); // Yellow for prompt
    c_gotoxy(50, 15);
    printf("Enter the ID of the drink to delete: ");
    c_textcolor(15); // White for input
    scanf("%d", &id);

    // Process deletion
    fseek(file, 0, SEEK_SET); // Reset file pointer to the start
    while (fread(&drink, sizeof(Drink), 1, file)) {
        if (drink.id == id) {
            found = 1;
            continue; // Skip this drink and do not write it to temp file
        }
        fwrite(&drink, sizeof(Drink), 1, tempFile); // Write remaining drinks
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the updated temp file
    remove(drinkFilePath);
    rename("temp.bin", drinkFilePath);

    if (found) {
        c_textcolor(10); // Green for success
        c_gotoxy(50, 17);
        printf("Drink deleted successfully!\n");
    } else {
        c_textcolor(4); // Red for error
        c_gotoxy(50, 17);
        printf("Drink with ID %d not found.\n", id);
    }

    c_textcolor(15); // Reset to default
    c_getch(); // Wait for key press before returning
}

#include <stdio.h>
#include <conio.h>
#include <string.h>

void afficherInfosRestaurant() {
    system("cls");

    // Unified background color (Light Gray) for all sections
    c_textcolor(15); // White text color

    // Display restaurant name
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Nom du restaurant: DragonWorrier        ");
    c_gotoxy(37, 15);
    printf("==============================================");
    c_getch();  // Wait for user to press a key before showing the next section

    // Address section
    system("cls");  // Clear screen
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Adresse: 123 Rue de la Paix, Paris      ");
    c_gotoxy(37, 15);
    printf("     France                                  ");
    c_gotoxy(37, 16);
    printf("==============================================");
    c_getch();  // Wait for user to press a key before showing the next section

    // Cuisine type and rating
    system("cls");
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Type de cuisine: Fusion asiatique       ");
    c_gotoxy(37, 15);
    printf("     Note: 4.3/5                             ");
    c_gotoxy(37, 16);
    printf("==============================================");
    c_getch();  // Wait for user to press a key before showing the next section

    // Specialties and payment options
    system("cls");
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Specialites: Sushi en la francaise       ");
    c_gotoxy(37, 15);
    printf("     Poulet au curry vert                    ");
    c_gotoxy(37, 16);
    printf("==============================================");
    c_gotoxy(37, 17);
    printf("     Options de paiement: Cartes bancaires    ");
    c_gotoxy(37, 18);
    printf("     Espèces, Paiement mobile                ");
    c_gotoxy(37, 19);
    printf("==============================================");
    c_getch();  // Wait for user to press a key before showing the next section

    // Contact info and social media
    system("cls");
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Contact: +33 1 23 45 67 89              ");
    c_gotoxy(37, 15);
    printf("     Facebook: DRAGON'S CHEFS                ");
    c_gotoxy(37, 16);
    printf("==============================================");
    c_gotoxy(37, 17);
    printf("     Instagram: ChefSOFDRAGON92              ");
    c_gotoxy(37, 18);
    printf("==============================================");
    c_getch();  // Wait for user to press a key before showing the next section

    // Footer message
    system("cls");
    c_textcolor(14); // Yellow text
    c_gotoxy(37, 13);
    printf("==============================================");
    c_gotoxy(37, 14);
    printf("     Appuyez sur une touche pour quitter...   ");
    c_gotoxy(37, 15);
    printf("==============================================");

    c_getch();  // Wait for user to press a key to exit
}


#endif