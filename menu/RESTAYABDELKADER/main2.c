#include "filehandling.h"   // Assume this includes employee management functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio.h"

// Function prototypes
void employeeMenu();
void reportMenu();
void normalizeFilePath(char *path);


int main() {
    int mainChoice;

    do {
        printf("=== Management System ===\n");
        printf("1. Employee Management\n");
        printf("2. Report Management\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &mainChoice) != 1) {
            // Clear invalid input from buffer
            while (getchar() != '\n');
            mainChoice = 0; // Reset to trigger invalid choice message
        }

        switch (mainChoice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                reportMenu();
                break;
            case 3:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("Press any key to continue...");
        c_getch();  // Pauses for user input

    } while (mainChoice != 3);

    return 0;
}

// Employee Management Menu
void employeeMenu() {
    int choice;

    do {
        c_textcolor(3);  // Set color (requires implementation if needed)
        printf("\n=== Employee Management System ===\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Delete Employee\n");
        printf("4. Return to Main Menu\n");

        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("Press any key to continue...");
        c_getch();  // Pauses for user input

    } while (choice != 4);
}

// Report Management Menu
void reportMenu() {
    int choice;
    char filePath[100];

    printf("Enter the file path for report storage: ");
    scanf("%s", filePath);
    normalizeFilePath(filePath);

    do {
        printf("\n=== Report Management System ===\n");
        printf("1. Add Daily Report Entry\n");
        printf("2. Display All Reports\n");
        printf("3. Return to Main Menu\n");

        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                addReportEntry(filePath);
                break;
            case 2:
                displayAllReports(filePath);
                break;
            case 3:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("Press any key to continue...");
        c_getch();  // Pauses for user input

    } while (choice != 3);
}
