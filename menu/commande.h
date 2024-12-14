#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dashboard.h"


typedef struct {
    int id;                            
    char date[20];                     
    char order_type[15];               
    int table_number;                
    char dishes[9][50];
    int quantities[9];
    float prices[9];               
    int num_items;                     
    float total_price;                 
} Command;

void clearBuffer() {
    while (getchar() != '\n');
}
void printAtXY(int x, int y, const char *text) {
    COORD coord;
    coord.X = x - 1; 
    coord.Y = y - 1;  
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    
    SetConsoleCursorPosition(hConsole, coord);
    
   
    printf("%s", text);
}

void getCurrentDate(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, size, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void addCommande(const char *filename, const char *dishFilePath, const char *drinkFilePath) {
    Command command;
    FILE *file = fopen(filename, "ab+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    
    int next_id = 1;
    rewind(file);
    while (fread(&command, sizeof(Command), 1, file)) {
        if (command.id >= next_id) {
            next_id = command.id + 1;
        }
    }
    command.id = next_id;

    getCurrentDate(command.date, sizeof(command.date));

    
    do {
        c_gotoxy(36, 13);
        c_textcolor(14); 
        printf("Enter order type (dine-in/take-away): ");
        scanf("%s", command.order_type);
        clearBuffer();
        if (strcmp(command.order_type, "dine-in") != 0 && strcmp(command.order_type, "take-away") != 0) {
            c_gotoxy(36, 14);
            c_textcolor(12);
            printf("Invalid type! Please enter 'dine-in' or 'take-away'.\n");
        }
    } while (strcmp(command.order_type, "dine-in") != 0 && strcmp(command.order_type, "take-away") != 0);

    
    if (strcmp(command.order_type, "dine-in") == 0) {
        c_gotoxy(36, 15);
        c_textcolor(10); 
        printf("Enter table number: ");
        scanf("%d", &command.table_number);
    } else {
        command.table_number = -1; 
    }

    
    FILE *dishFile = fopen(dishFilePath, "rb");
    if (!dishFile) {
        c_gotoxy(36, 16);
        printf("Error: Unable to open dish menu file!\n");
        fclose(file);
        return;
    }

   
    command.num_items = 0;
    command.total_price = 0;

    Dish dish;
    char add_more;
    int dish_id, quantity;
           do {
              c_textcolor(6); 
              printAtXY(36, 17, "Enter the ID of the dish you want to add: "); 
              scanf("%d", &dish_id);  
              rewind(dishFile);  

    int found = 0;
    while (fread(&dish, sizeof(Dish), 1, dishFile)) {
        if (dish.id == dish_id) {
            found = 1;
            c_gotoxy(36, 18);  
            c_textcolor(11);   
            printf("Enter the quantity for '%s':       ", dish.name);  
            scanf("%d", &quantity);  
            strcpy(command.dishes[command.num_items], dish.name);  
            command.quantities[command.num_items] = quantity;  
            command.prices[command.num_items] = dish.price;
            command.total_price += quantity * dish.price;  
            command.num_items++;  
            break;  
        }
    }

    if (!found) {
        c_gotoxy(36, 19);  
        c_textcolor(12);  
        printf("Invalid dish ID! Please try again.\n");  
    }

    c_gotoxy(36, 20);  
    printf("Do you want to add another dish? (y/n): ");
    scanf(" %c", &add_more); 
} while (add_more == 'y' && command.num_items < 10);

fclose(dishFile); 

   
    char add_drink;
    c_textcolor(6);  
    printAtXY(36, 23, "Do you want to add a drink? (y/n): ");
    scanf(" %c", &add_drink);

    if (add_drink == 'y' || add_drink == 'Y') {
        
        Drink drink;
         FILE *drinkFile = fopen(drinkFilePath, "rb");
            if (!drinkFile) {
                c_gotoxy(36, 22);
                printf("Error: Unable to open drink menu file!\n");
                fclose(file);
                return;
            }
            
        do {
            c_textcolor(6);  
            printAtXY(36, 25, "Enter the ID of the drink you want to add: ");
            scanf("%d", &dish_id); 
            rewind(drinkFile); 

            int found = 0;
            while (fread(&drink, sizeof(Drink), 1, drinkFile)) {
                if (drink.id == dish_id) {
                    found = 1;
                    c_gotoxy(36, 26);  
                    c_textcolor(11); 
                    printf("Enter the quantity for '%s':     ", drink.name);
                    scanf("%d", &quantity);
                    strcpy(command.dishes[command.num_items], drink.name);
                    command.quantities[command.num_items] = quantity;
                    command.prices[command.num_items] = drink.price;
                    command.total_price += quantity * drink.price;
                    command.num_items++;
                    break;
                }
            }

            if (!found) {
                c_textcolor(12); 
                c_gotoxy(36, 26); 
                printf("Invalid drink ID! Try again.\n");
            }

            printAtXY(36,29,"Do you want to add another drink? (y/n): ");
            scanf(" %c", &add_more);
        } while (add_more == 'y' && command.num_items < 10);
    }


    
    fwrite(&command, sizeof(Command), 1, file);
    fclose(file);
    
c_gotoxy(36, 30); 
c_textcolor(10); 
printf("Command added successfully! Total price: %.2f DH", command.total_price); 
}

void displayCommand(const Command *command) {
    int y_position = 13;

    c_gotoxy(36, y_position++);
    c_textcolor(14);  
    printf("============= Command ID: %d ==============", command->id);
    
    c_gotoxy(36, y_position++);
    c_textcolor(11); 
    printf("Date           : %s", command->date);
    
    c_gotoxy(36, y_position++);
    printf("Order Type     : %s", command->order_type);

    if (strcmp(command->order_type, "dine-in") == 0) {
        c_gotoxy(36, y_position++);
        printf("Table Number   : %d", command->table_number);
    }

    c_gotoxy(36, y_position++);
    printf("Order Details  :                               ");
    c_gotoxy(36, y_position++);
    printf("                                               ");

    for (int i = 0; i < command->num_items; i++) {
        c_gotoxy(36, y_position++);
        printf("- %d x %-18s   at %6.2f  DH", command->quantities[i], command->dishes[i], command->prices[i]);
    }
    
    c_gotoxy(36,y_position++);
    printf("                                                                ");
    c_gotoxy(36, y_position++);
    printf("Total Price:  %.2f DH                  ", command->total_price);

    c_gotoxy(36, y_position++);
    printf("                                   ");
    c_gotoxy(36, y_position++);
    printf("                                   ");
    c_gotoxy(36, y_position++);
    printf("                                   ");
    c_gotoxy(36, y_position++); 
    printf("                                   ");
    c_gotoxy(36, y_position++);
    printf("                                   ");
}


void displayCommands(const char *filename) {
    Command command;
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int commandCount = 0;
    fseek(file, 0, SEEK_END);  
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);  

    
    while (fread(&command, sizeof(Command), 1, file)) {
        commandCount++;
    }

    fseek(file, 0, SEEK_SET);  

    int currentIndex = 0;  

    char input;
    int searchId = -1;  
    while (1) {
       
        if (searchId == -1) {
            fseek(file, currentIndex * sizeof(Command), SEEK_SET);
            fread(&command, sizeof(Command), 1, file);
        } else {
            
            int found = 0;
            while (fread(&command, sizeof(Command), 1, file)) {
                if (command.id == searchId) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                c_textcolor(12); 
                c_gotoxy(36, 28);
                printf("Command with ID %d not found.", searchId);
                searchId = -1;  
                continue;
            }
        }

        
        displayCommand(&command);

        
        c_textcolor(13);  
        c_gotoxy(36, 30);
        printf("N : Next, | P : Previous, | Q: Quit, | S: Search by ID ");
        

        input = getch(); 
        if (input == 'n' || input == 'N') {
            if (currentIndex < commandCount - 1) {
                currentIndex++;  
            }
        } else if (input == 'p' || input == 'P') {
            if (currentIndex > 0) {
                currentIndex--;  
            }
        } else if (input == 'q' || input == 'Q') {
            break; 
        } else if (input == 's' || input == 'S') {
        
            c_gotoxy(36, 32);
            c_textcolor(6);
            printf("Enter the Command ID to search: ");
            scanf("%d", &searchId);
            fseek(file, 0, SEEK_SET);  // Reset file pointer for next search
        }
    }

    fclose(file);
}


void deleteCommand(const char *filename) {
    int id_to_delete;
    int command_found = 0;
    Command command;

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    c_textcolor(6); 
    c_gotoxy(36, 15); 
    printf("Enter the ID of the command to delete: ");

    while (scanf("%d", &id_to_delete) != 1) {
        c_gotoxy(36, 16); 
        printf("Invalid input! Please enter an integer: ");
        clearBuffer();
    }

    while (fread(&command, sizeof(Command), 1, file)) {
        if (command.id == id_to_delete) {
            command_found = 1;
            c_gotoxy(36, 18);  
            c_textcolor(10);   
            printf("Command with ID %d deleted.\n", id_to_delete);
        } else {
            fwrite(&command, sizeof(Command), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (command_found) {
        remove(filename);
        if (rename("temp.bin", filename) != 0) {
            perror("Error renaming temporary file");
        }
    } else {
        c_gotoxy(36, 19);  
        c_textcolor(12);    
        printf("No command with ID %d found.\n", id_to_delete);
        remove("temp.bin");
    } 
}


#endif
