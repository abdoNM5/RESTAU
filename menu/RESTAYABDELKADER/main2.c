#include "filehandling.h"
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"

int main()
{
    int choice;

    do
    {
        c_textcolor(3);
        printf("=== Employee Management System ===\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Delete Employee\n");
        printf("4. Exit\n");
        c_textcolor(2);
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer in case of invalid input

            while (getchar() != '\n');
            choice = 0; // Reset choice to trigger invalid choice
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
            c_textcolor(2);
            printf("Exiting the program...\n");
            break;
        default:
            c_textcolor(4);
            printf("Invalid choice! Please try again.\n");
        }
        printf("Press any key to continue...");
        c_getch();

    } while (choice != 4);

    return 0;
}
