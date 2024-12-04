#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h" // Include for console styling functions

#define MAX_NAME_LENGTH 50
#define CONSOLE_WIDTH 80

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
    char position[MAX_NAME_LENGTH];
} Employee;

// Function Prototypes
void addEmployee();
void displayEmployees();
void updateEmployee();
void deleteEmployee();
void printCentered(const char *text, int y, int color);

// Function to print centered text with color
void printCentered(const char *text, int y, int color) {
    int x = 20;
    c_gotoxy(x, y);
    c_textcolor(color);
    printf("%s", text);
    c_textcolor(15); // Reset to white
}

// Add Employee Function
void addEmployee() {
    FILE *file = fopen("employer.dat", "ab");
    if (!file) {
        printCentered("Error opening file for adding.", 15, 12);
        return;
    }

    Employee emp;
    int isUnique, attempts = 0;

    printCentered("==== Add Employee ====", 14, 14);

    while (attempts < 4) {
        isUnique = 1;

        printCentered("Enter Employee ID: ", 16, 10);
        while (scanf("%d", &emp.id) != 1) {
            printCentered("Invalid input! Please enter a valid ID: ", 17, 12);
            while (getchar() != '\n'); // Clear input buffer
        }

        // Check for unique ID
        FILE *checkFile = fopen("employer.dat", "rb");
        if (!checkFile) {
            printCentered("Error opening file for checking ID.", 18, 12);
            fclose(file);
            return;
        }

        Employee temp;
        while (fread(&temp, sizeof(Employee), 1, checkFile)) {
            if (temp.id == emp.id) {
                printCentered("Error: Employee ID already exists.", 18, 12);
                isUnique = 0;
                break;
            }
        }
        fclose(checkFile);

        if (isUnique) {
            break;
        }

        attempts++;
        if (attempts < 4) {
            char msg[50];
            sprintf(msg, "Try again. (%d attempts left)", 4 - attempts);
            printCentered(msg, 19, 14);
        }
    }

    if (!isUnique) {
        printCentered("Maximum attempts reached. Operation canceled.", 20, 12);
        return;
    }

    printCentered("Enter Name: ", 21, 10);
    scanf(" %[^\n]", emp.name);

    printCentered("Enter Position: ", 22, 10);
    scanf(" %[^\n]", emp.position);

    printCentered("Enter Salary: ", 23, 10);
    while (scanf("%f", &emp.salary) != 1) {
        printCentered("Invalid input! Please enter a valid Salary: ", 24, 12);
        while (getchar() != '\n'); // Clear input buffer
    }

    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);

    printCentered("Employee added successfully!", 25, 1);
}

// Display Employees Function
void displayEmployees() {
    FILE *file = fopen("employer.dat", "rb");
    if (!file) {
        printCentered("Error opening file for display.", 15, 12);
        return;
    }

    Employee emp;

    c_textbackground(0); // Blue background
    c_clrscr();          // Clear screen

    printCentered("================= Employee Records =================", 10, 14);
    c_gotoxy(21, 12);
    c_textcolor(11); // Cyan
    printf("%-10s%-20s%-10s%-20s\n", "ID", "Name", "Salary(DH)", "Position");
    c_gotoxy(21, 13);
    printf("===================================================");

    int y = 14;
    c_textcolor(15); // White
    while (fread(&emp, sizeof(Employee), 1, file)) {
        c_gotoxy(21, y++);
        printf("%-10d%-20s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
    }

    fclose(file);
    c_textcolor(15); // Reset color
}

// Update Employee Salary Function
void updateEmployee() {
    FILE *file = fopen("employer.dat", "rb");
    if (!file) {
        printCentered("Error opening file for update.", 15, 12);
        return;
    }

    FILE *tempFile = fopen("temp_employer.dat", "wb");
    if (!tempFile) {
        printCentered("Error creating temporary file.", 16, 12);
        fclose(file);
        return;
    }

    Employee emp;
    int id, found = 0;

    printCentered("Enter the ID to update salary: ", 17, 10);
    scanf("%d", &id);

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            printCentered("Enter new salary: ", 18, 10);
            while (scanf("%f", &emp.salary) != 1) {
                printCentered("Invalid input! Please enter a valid Salary: ", 19, 12);
                while (getchar() != '\n'); // Clear input buffer
            }
        }
        fwrite(&emp, sizeof(Employee), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("employer.dat");
        rename("temp_employer.dat", "employer.dat");
        printCentered("Employee salary updated successfully.", 20, 10);
    } else {
        printCentered("Employee not found.", 20, 12);
    }
}

// Delete Employee Function
void deleteEmployee() {
    FILE *file = fopen("employer.dat", "rb");
    if (!file) {
        printCentered("Error opening file for deletion.", 15, 12);
        return;
    }

    FILE *tempFile = fopen("temp_employer.dat", "wb");
    if (!tempFile) {
        printCentered("Error creating temporary file.", 16, 12);
        fclose(file);
        return;
    }

    Employee emp;
    int id, found = 0;

    printCentered("Enter the ID to delete: ", 17, 10);
    scanf("%d", &id);

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("employer.dat");
        rename("temp_employer.dat", "employer.dat");
        printCentered("Employee deleted successfully.", 18, 10);
    } else {
        printCentered("Employee not found.", 18, 12);
    }
}

#endif