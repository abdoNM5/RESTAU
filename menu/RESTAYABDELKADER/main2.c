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
        c_clrscr();  
        c_textcolor(4);
        c_gotoxy(30, 6);  
        printf("=== Management System ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8); 
        printf("1. Employee Management\n");
        c_gotoxy(30, 9); 
        printf("2. Report Management\n");
        c_gotoxy(30, 10); 
        printf("3. Exit\n");
        c_gotoxy(30, 12); 
        c_textcolor(15); 
        printf("Choose an option: ");
        
        if (scanf("%d", &mainChoice) != 1) {
            while (getchar() != '\n');
            mainChoice = 0;
        }

        switch (mainChoice) {
            case 1:
                c_clrscr();  // Clear screen after choice
                employeeMenu();
                break;
            case 2:
                c_clrscr();  // Clear screen after choice
                reportMenu();
                break;
            case 3:
                c_textcolor(4);
                printf("Exiting the program...\n");
                break;
            default:
                c_textcolor(4);
                printf("Invalid choice! Please try again.\n");
        }
        c_textcolor(2);
        printf("Press any key to continue...");
        c_getch();  

    } while (mainChoice != 3);

    return 0;
}

void employeeMenu() {
    int choice;

    do {
        c_clrscr();  // Clear screen each time a menu is displayed
        c_textcolor(2);
        c_gotoxy(30, 6);
        printf("=== Employee Management System ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Add Employee\n");
        c_gotoxy(30, 9);
        printf("2. Display Employees\n");
        c_gotoxy(30, 10);
        printf("3. Delete Employee\n");
        c_gotoxy(30, 11);
        printf("4. Return to Main Menu\n");
        c_textcolor(15);
        c_gotoxy(30, 13);
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

        c_gotoxy(30, 15);
        printf("Press any key to continue...");
        c_getch();

    } while (choice != 4);
}

void reportMenu() {
    int choice;
    char filePath[100];

    c_clrscr();  // Clear screen before asking for file path
    c_textcolor(3);
    c_gotoxy(30, 6);
    printf("Enter the file path for report storage: ");
    scanf("%s", filePath);
    normalizeFilePath(filePath);

    do {
        c_clrscr();  // Clear screen each time a menu is displayed
        c_textcolor(2);
        c_gotoxy(30, 6);
        printf("=== Report Management System ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Add Daily Report Entry\n");
        c_gotoxy(30, 9);
        printf("2. Display All Reports\n");
        c_gotoxy(30, 10);
        printf("3. Return to Main Menu\n");
        c_textcolor(15);
        c_gotoxy(30, 12);
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

        c_gotoxy(30, 14);
        printf("Press any key to continue...");
        c_getch();

    } while (choice != 3);
}
