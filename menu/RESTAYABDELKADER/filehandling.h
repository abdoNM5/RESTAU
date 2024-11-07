#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h" // Single include for conio library
#define MAX_PATH_LENGTH 256 // Define the maximum length for file paths

int background_color = 0;

// Define Employee struct
typedef struct {
    int id;
    char name[50];
    float salary;
    char position[50];
} Employee;

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
    c_textcolor(2);
    c_gotoxy(40, 6);
    printf("Enter the file path to save the employee data: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    // Open the file for reading to check for existing IDs
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);
        c_gotoxy(40,6);
        perror("Error opening file");
        return;
    }

    Employee emp;
    c_textcolor(2);
    c_gotoxy(40,6);
    printf("Enter Employee ID: ");
    
    // Validate Employee ID input and check for uniqueness
    while (scanf("%d", &emp.id) != 1) {
        c_textcolor(4);
        printf("Invalid input! Please enter a valid Employee ID: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Check if the ID is already taken
    int idExists = 0;
    while (fscanf(file, "%d|%49[^|]|%f|%49[^\n]", &emp.id, emp.name, &emp.salary, emp.position) == 4) {
        if (emp.id == emp.id) {
            idExists = 1;
            break;
        }
    }

    fclose(file);  // Close the file after checking

    // If the ID is already taken, ask for a new one
    if (idExists) {
        c_textcolor(4);
        c_gotoxy(40,6);
        printf("ID already taken! Please enter a different Employee ID: ");
        return;
    }

    // Open the file for appending
    file = fopen(filePath, "a");
    if (file == NULL) {
        c_textcolor(4);
        c_gotoxy(40, 6);
        perror("Error opening file");
        return;
    }

    c_textcolor(1);
    c_gotoxy(40, 6);
    printf("Enter Name: ");
    scanf(" %[^\n]s", emp.name);

    printf("Enter Position: ");
    scanf(" %[^\n]s", emp.position);

    c_textcolor(2);
    printf("Enter Salary: ");
    
    // Validate Salary input
    while (scanf("%f", &emp.salary) != 1) {
        c_textcolor(4);
        c_gotoxy(40, 6);
        printf("Invalid input! Please enter a valid Salary: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Write employee data to the file using a delimiter
    fprintf(file, "%d|%s|%.2f|%s\n", emp.id, emp.name, emp.salary, emp.position);
    fclose(file);
    
    c_textcolor(2);
    c_gotoxy(40, 6);
    printf("Employee added successfully to %s!\n", filePath);
}

// Function to display all employees from a file
void displayEmployees() {
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);
     c_gotoxy(40, 6);
    printf("Enter the file path to display the employee data: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);
        perror("Error opening file");
        return;
    }

    Employee emp;
    c_textcolor(2);
    c_gotoxy(40, 6);
    printf("%-10s%-30s%-10s%-20s\n", "ID", "Name", "Salary", "Position");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%d|%49[^|]|%f|%49[^\n]", &emp.id, emp.name, &emp.salary, emp.position) == 4) {
        c_textcolor(2);

        printf("%-10d%-30s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
    }

    fclose(file);
}

// Function to delete an employee from a file
void deleteEmployee() {
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);
    c_gotoxy(40, 6);
    printf("Enter the file path to delete an employee data: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);
        perror("Error opening file");
        return;
    }

    int deleteId;
    c_textcolor(2);
    c_gotoxy(40, 6);
    printf("Enter the employee ID to delete: ");
    scanf("%d", &deleteId);

    Employee emp;
    int found = 0;
    char buffer[1000] = ""; // Clear the buffer initially
    char line[200]; // Increase line buffer size

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
        c_textcolor(4);
        printf("Employee with ID %d not found.\n", deleteId);
        return;
    }

    // Open the file for writing and overwrite it
    file = fopen(filePath, "w");
    if (file == NULL) {
        c_textcolor(4);
        perror("Error opening file for writing");
        return;
    }

    fputs(buffer, file); // Write the new content
    fclose(file);

    c_textcolor(2);
    printf("Employee with ID %d deleted successfully.\n", deleteId);
}
