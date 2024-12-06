#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char date[20];
    char order_type[5];
    int num_items;
    char dishes[10][30];
    int quantities[10];
    float prices[10];
    float total_price;
} Command;

// Function to clear the input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

// Function to get the current date as a string
void getCurrentDate(char *date_str, size_t size) {
    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    strftime(date_str, size, "%Y-%m-%d %H:%M:%S", time_info);
}

// Function to add a command
void addCommand(const char *filename) {
    Command command;
    FILE *file = fopen(filename, "ab+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Determine the next ID
    int next_id = 1;
    rewind(file);
    while (fread(&command, sizeof(Command), 1, file)) {
        if (command.id >= next_id) {
            next_id = command.id + 1;
        }
    }
    command.id = next_id;

    // Get the current date
    getCurrentDate(command.date, sizeof(command.date));

    // Input order type
    do {
        printf("Enter order type (in/out): ");
        scanf("%s", command.order_type);
        clearBuffer();
        if (strcmp(command.order_type, "in") != 0 && strcmp(command.order_type, "out") != 0) {
            printf("Invalid type! Please enter 'in' or 'out'.\n");
        }
    } while (strcmp(command.order_type, "in") != 0 && strcmp(command.order_type, "out") != 0);

    // Input number of dishes
    printf("Enter the number of dishes in the order: ");
    while (scanf("%d", &command.num_items) != 1 || command.num_items <= 0 || command.num_items > 10) {
        printf("Invalid input! Please enter a number between 1 and 10: ");
        clearBuffer();
    }

    // Input details for each dish
    command.total_price = 0;
    for (int i = 0; i < command.num_items; i++) {
        printf("Enter the name of dish %d: ", i + 1);
        clearBuffer();
        fgets(command.dishes[i], sizeof(command.dishes[i]), stdin);
        command.dishes[i][strcspn(command.dishes[i], "\n")] = '\0';

        printf("Enter the quantity for %s: ", command.dishes[i]);
        while (scanf("%d", &command.quantities[i]) != 1 || command.quantities[i] <= 0) {
            printf("Invalid input! Please enter a valid quantity: ");
            clearBuffer();
        }

        printf("Enter the unit price for %s: ", command.dishes[i]);
        while (scanf("%f", &command.prices[i]) != 1 || command.prices[i] <= 0) {
            printf("Invalid input! Please enter a valid price: ");
            clearBuffer();
        }

        command.total_price += command.quantities[i] * command.prices[i];
    }

    // Save the command to the file
    fwrite(&command, sizeof(Command), 1, file);
    fclose(file);
    printf("Command added successfully!\n");
}

// Function to display all commands
void displayCommands(const char *filename) {
    Command command;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\n=== List of Commands ===\n");
    while (fread(&command, sizeof(Command), 1, file)) {
        printf("ID: %d\n", command.id);
        printf("Date: %s\n", command.date);
        printf("Order Type: %s\n", command.order_type);
        printf("Order Details:\n");
        for (int i = 0; i < command.num_items; i++) {
            printf("- %d x %s at %.2f each\n", command.quantities[i], command.dishes[i], command.prices[i]);
        }
        printf("Total Price: %.2f\n", command.total_price);
        printf("--------------------------\n");
    }

    fclose(file);
}

// Function to delete a command
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

    printf("Enter the ID of the command to delete: ");
    while (scanf("%d", &id_to_delete) != 1) {
        printf("Invalid input! Please enter an integer: ");
        clearBuffer();
    }

    while (fread(&command, sizeof(Command), 1, file)) {
        if (command.id == id_to_delete) {
            command_found = 1;
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
        printf("No command with ID %d found.\n", id_to_delete);
        remove("temp.bin");
    }
}

#endif
