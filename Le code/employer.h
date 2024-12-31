#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h" // Include for console styling functions
#include "identif.h"
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
    c_gotoxy(52,11);
    c_textcolor(4);
    printf("==== Add Employee ====");
    while (attempts < 4) {
        isUnique = 1;
        c_gotoxy(32, 15);
        c_textcolor(14);
        printf("Enter Employee ID: ");
        drawEmptyBox(51,14,25);
        c_gotoxy(52, 15);
        while (scanf("%d", &emp.id) != 1) {
            c_gotoxy(52,29);
            printf("Invalid input! Please enter a valid ID: ");
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
                c_gotoxy(52,29);
                printf("Error: Employee ID already exists.");
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
            c_gotoxy(52,30);
            sprintf(msg, "Try again. (%d attempts left)", 4 - attempts);
            c_gotoxy(52,30);
            printf(msg);
        }
    }

    if (!isUnique) {
        printCentered("Maximum attempts reached. Operation canceled.", 20, 12);
        return;
    }
    c_gotoxy(32, 18);
    printf("Enter Name: ");
    drawEmptyBox(51,17,25);
    c_gotoxy(52, 18); 
    scanf(" %[^\n]", emp.name); 
    c_gotoxy(32, 21);
    printf("Enter Position: ");
    drawEmptyBox(51,20,25);
    c_gotoxy(52,21);
    scanf(" %[^\n]", emp.position);
    c_gotoxy(32, 24);
    printf("Enter Salary: ");
    drawEmptyBox(51,23,25);
    c_gotoxy(52,24);
    while (scanf("%f", &emp.salary) != 1) {
        printCentered("Invalid input! Please enter a valid Salary: ", 24, 12);
        while (getchar() != '\n'); // Clear input buffer
    }
    
    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);
    c_gotoxy(52,28);
    c_textcolor(1);
    printf("Employee added successfully!");
}

// Display Employees Function
void displayEmployees() {
    FILE *file = fopen("employer.dat", "rb");
    if (!file) {
        printCentered("Error opening file for display.", 15, 12);
        return;
    }

    Employee emp;
    c_textcolor(14);
    c_gotoxy(36,12);
    printf("===================== Employee Records ========================");
    c_gotoxy(36, 14);
    c_textcolor(11); // Cyan
    printf("%-10s%-20s%-15s%-20s\n", "ID", "Name", "Salary(DH)", "Position");
    c_gotoxy(36, 15);
    printf("===============================================================");

    int y = 16;
    c_textcolor(15); // White
    while (fread(&emp, sizeof(Employee), 1, file)) {
        c_gotoxy(36, y++);
        printf("%-10d%-20s%-15.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
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
    c_gotoxy(32, 15);
    c_textcolor(3);
    printf("Enter the ID to update salary: ");
    drawEmptyBox(62,14,22);
    c_gotoxy(63, 15);
    scanf("%d", &id);
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            c_gotoxy(32, 18);
            c_textcolor(3);
            printf("Enter new salary: ");
            drawEmptyBox(62,17,22);
            c_gotoxy(63, 18);
            while (scanf("%f", &emp.salary) != 1) {
                printCentered("Invalid input! Please enter a valid Salary: ", 19, 12);
                while (getchar() != '\n'); 
            }
        }
        fwrite(&emp, sizeof(Employee), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("employer.dat");
        rename("temp_employer.dat", "employer.dat");
        c_gotoxy(32,20);
        c_textcolor(10);
        printf("Employee salary updated successfully.");
    } else {
        c_gotoxy(32,20);
        c_textcolor(4);
        printf("Employee not found.");
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
    c_gotoxy(32, 15);
    c_textcolor(3);
    printf("Enter the ID to delete: ");
    drawEmptyBox(55,14,22);
    c_gotoxy(56, 15);
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
        c_gotoxy(52,25);
        c_textcolor(10);
        printf("Employee deleted successfully.");
    } else {
        c_gotoxy(52,25);
        c_textcolor(4);
        printf("Employee not found.");
    }
}

#endif
