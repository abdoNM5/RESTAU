#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h" // Single include for conio library
#define MAX_PATH_LENGTH 256
#define CONSOLE_WIDTH 80

int background_color = 0;

// Define Employee struct
typedef struct {
    int id;
    char name[50];
    float salary;
    char position[50];
} Employee;

// Helper function to center text
void printCentered(const char *text, int y) {
    int x = (CONSOLE_WIDTH - strlen(text)) / 2;
    c_gotoxy(x, y);
    printf("%s", text);
}

// Function to normalize file paths
void normalizeFilePath(char *path) {
    int len = strlen(path);

    // Remove surrounding quotes if they exist
    if (path[0] == '"') {
        memmove(path, path + 1, len);
        len--;
    }
    if (path[len - 1] == '"') {
        path[len - 1] = '\0';
    }

    // Replace backslashes with forward slashes
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
}

// Function to add an employee to a file
void addEmployee() {
    char filePath[MAX_PATH_LENGTH];
    printCentered("Enter the file path to save the employee data:", 6);
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        printCentered("Error opening file", 8);
        perror("");
        return;
    }

    Employee emp;
    printCentered("Enter Employee ID: ", 7);
    
    // Validate Employee ID input
    while (scanf("%d", &emp.id) != 1) {
        printCentered("Invalid input! Please enter a valid Employee ID: ", 8);
        while(getchar() != '\n'); // Clear input buffer
    }

    printCentered("Enter Name: ", 9);
    scanf(" %[^\n]s", emp.name);

    printCentered("Enter Position: ", 10);
    scanf(" %[^\n]s", emp.position);

    printCentered("Enter Salary: ", 11);
    while (scanf("%f", &emp.salary) != 1) {
        printCentered("Invalid input! Please enter a valid Salary: ", 12);
        while(getchar() != '\n'); // Clear input buffer
    }

    fprintf(file, "%d|%s|%.2f|%s\n", emp.id, emp.name, emp.salary, emp.position);
    fclose(file);
    printCentered("Employee added successfully!", 13);
}

// Function to display all employees from a file
void displayEmployees() {
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(6);
    printCentered("Enter the file path to display the employee data: ", 7);
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printCentered("Error opening file", 8);
        perror("");
        return;
    }

    Employee emp;
    c_textbackground(3);
    c_textcolor(0);
    printCentered("ID        Name                       Salary(DH)  Position", 9);
    printCentered("=========================================================", 10);
    c_textbackground(0);
    c_textcolor(15);
    int y = 11;
    while (fscanf(file, "%d|%49[^|]|%f|%49[^\n]", &emp.id, emp.name, &emp.salary, emp.position) == 4) {
        c_gotoxy((CONSOLE_WIDTH - 58) / 2, y++);
        printf("%-10d%-30s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
    }

    fclose(file);
}

// Function to delete an employee from a file
void deleteEmployee() {
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(6);
    printCentered("Enter the file path to delete an employee data: ", 7);
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);
        printCentered("Error opening file", 8);
        perror("");
        return;
    }

    int deleteId;
    printCentered("Enter the employee ID to delete: ", 9);
    scanf("%d", &deleteId);

    Employee emp;
    int found = 0;
    char buffer[1000] = ""; // Clear the buffer initially
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d", &emp.id);
        if (emp.id != deleteId) {
            strcat(buffer, line); // Append the line to the buffer
        } else {
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printCentered("Employee not found.", 10);
        return;
    }

    file = fopen(filePath, "w");
    if (file == NULL) {
        printCentered("Error opening file for writing", 11);
        perror("");
        return;
    }

    fputs(buffer, file);
    fclose(file);

    printCentered("Employee deleted successfully!", 12);
}
