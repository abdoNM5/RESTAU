#ifndef MAIN_H // Guard to prevent multiple inclusions
#define MAIN_H

#include <stdio.h>        // Standard I/O functions
#include <stdlib.h>       // Standard library functions (e.g., malloc, free)
#include <string.h>       // String manipulation functions (e.g., strcpy, strcat)
#include <ctype.h>        // Character handling functions (e.g., isdigit, isalpha)
#include "conio.h"        // Console I/O functions (only if needed for your environment)
#include "filehandling.h" // Your custom header for file handling
#include "reservation.h"

// Function prototypes
void employeeMenu();
void reportMenu();
void receptionistMenu();

int main()
{
    int mainChoice;

    do
    {
        c_clrscr();
        c_textcolor(4);
        c_gotoxy(30, 6);
        printf("=== System Access ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Manager\n");
        c_gotoxy(30, 9);
        printf("2. Receptionist\n");
        c_gotoxy(30, 10);
        printf("3. Exit\n");
        c_gotoxy(30, 12);
        c_textcolor(15);
        printf("Choose an access level: ");

        if (scanf("%d", &mainChoice) != 1)
        {
            while (getchar() != '\n')
                ;
            mainChoice = 0;
        }

        switch (mainChoice)
        {
        case 1:
            c_clrscr();
            employeeMenu();
            break;
        case 2:
            c_clrscr();
            receptionistMenu();
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

// Menu for Manager
void employeeMenu()
{
    int choice;

    do
    {
        c_clrscr();
        c_textcolor(2);
        c_gotoxy(30, 6);
        printf("=== Manager: Employee Management ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Add Employee\n");
        c_gotoxy(30, 9);
        printf("2. Display Employees\n");
        c_gotoxy(30, 10);
        printf("3. Delete Employee\n");
        c_gotoxy(30, 11);
        printf("4. Report Management\n");
        c_gotoxy(30, 12);
        printf("5. Return to Main Menu\n");
        c_textcolor(15);
        c_gotoxy(30, 14);
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
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
            reportMenu();
            break;
        case 5:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }

        c_gotoxy(30, 16);
        printf("Press any key to continue...");
        c_getch();

    } while (choice != 5);
}
void receptionistMenu()
{
    int choice;
    Reservation res;
    int reservationID;
    char file_path[100];

    do
    {
        c_clrscr();
        c_textcolor(2);
        c_gotoxy(30, 6);
        printf("=== Receptionist: Reservation System ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Create Reservation\n");
        c_gotoxy(30, 9);
        printf("2. Display Reservations\n");
        c_gotoxy(30, 10);
        printf("3. Delete Reservation\n");
        c_gotoxy(30, 11);
        printf("4. Return to Main Menu\n");
        c_textcolor(15);
        c_gotoxy(30, 13);
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            // Prompt user for the file path before creating a reservation
            printf("Enter file path to save reservation: ");
            getchar(); // Clear newline left by scanf
            fgets(file_path, sizeof(file_path), stdin);
            file_path[strcspn(file_path, "\n")] = '\0'; // Remove newline character
            normalizeFilePath(file_path);

            if (create_reservation(&res, file_path))
            {
                printf("Reservation created successfully!\n");
            }
            else
            {
                printf("Failed to create reservation.\n");
            }
            break;

        case 2:
            // Prompt user for the file path before displaying reservations
            printf("Enter file path to display reservations: ");
            getchar();
            fgets(file_path, sizeof(file_path), stdin);
            file_path[strcspn(file_path, "\n")] = '\0';
            normalizeFilePath(file_path);

            display_reservations(file_path);
            break;

        case 3:
            // Prompt user for the file path before deleting a reservation
            printf("Enter file path to delete reservation from: ");
            getchar();
            fgets(file_path, sizeof(file_path), stdin);
            file_path[strcspn(file_path, "\n")] = '\0';
            normalizeFilePath(file_path);

            printf("Enter Reservation ID to delete: ");
            if (scanf("%d", &reservationID) == 1)
            {
                delete_reservation(reservationID, file_path);
            }
            else
            {
                printf("Invalid ID input.\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
            }
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

// Report Menu for Manager
void reportMenu()
{
    int choice;
    char filePath[100];

    c_clrscr();
    c_textcolor(3);
    c_gotoxy(30, 6);
    printf("Enter the file path for report storage: ");
    scanf("%s", filePath);
    normalizeFilePath(filePath);

    do
    {
        c_clrscr();
        c_textcolor(2);
        c_gotoxy(30, 6);
        printf("=== Manager: Report Management ===\n");
        c_textcolor(14);
        c_gotoxy(30, 8);
        printf("1. Add Daily Report Entry\n");
        c_gotoxy(30, 9);
        printf("2. Display All Reports\n");
        c_gotoxy(30, 10);
        printf("3. Return to Employee Menu\n");
        c_textcolor(15);
        c_gotoxy(30, 12);
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            addReportEntry(filePath);
            break;
        case 2:
            displayReports(filePath);
            break;
        case 3:
            printf("Returning to employee menu...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }

        c_gotoxy(30, 14);
        printf("Press any key to continue...");
        c_getch();

    } while (choice != 3);
}
#endif // MAIN_H