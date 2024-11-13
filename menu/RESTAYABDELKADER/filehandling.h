#ifndef FILEHANDLING_H  // Garder l'inclusion unique
#define FILEHANDLING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h" // Single include for conio library
#include <ctype.h>

#define MAX_PATH_LENGTH 256 // Define the maximum length for file paths

extern int background_color;

struct Report {
    int id;
    char date[11]; // Format: YYYY-MM-DD
    float loss;
    float earnings;
    float profit;
};

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

void addEmployee() {
    c_clrscr();  // Clear the screen
    c_gotoxy(40, 6);  // Move the cursor to (40, 6)
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);
    printf("Enter the file path to save the employee data: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    Employee emp;
    int enteredId;
    FILE *file;
    int idExists = 0;

    // Open the file for reading to check for existing IDs
    file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);
        c_gotoxy(40, 6);
        perror("Error opening file for reading, creating a new file...");
        file = fopen(filePath, "w"); // Create the file if it doesn't exist
        if (file == NULL) {
            perror("Error creating file");
            return;
        }
    }

    c_textcolor(2);
    c_gotoxy(40, 8);  // Move the cursor down
    printf("Enter Employee ID: ");
    
    // Validate Employee ID input
    while (scanf("%d", &enteredId) != 1) {
        c_textcolor(4);
        printf("Invalid input! Please enter a valid Employee ID: ");
        while(getchar() != '\n'); // Clear input buffer
    }

    // Check if the ID is already taken
    while (fscanf(file, "%d|%49[^|]|%f|%49[^\n]", &emp.id, emp.name, &emp.salary, emp.position) == 4) {
        if (emp.id == enteredId) {  // Compare the entered ID with IDs in the file
            idExists = 1;
            break;
        }
    }

    fclose(file);  // Close the file after checking

    // If the ID is already taken, ask for a new one
    if (idExists) {
        c_textcolor(4);
        c_gotoxy(40, 10);
        printf("Error: ID %d already taken! Please enter a different Employee ID.\n", enteredId);
        c_getch();  // Wait for user input
        return;  // Exit the function to allow the user to re-enter a unique ID
    }

    // Open the file for appending
    file = fopen(filePath, "a");
    if (file == NULL) {
        c_textcolor(4);
        c_gotoxy(40, 10);
        perror("Error opening file for writing");
        return;
    }

    // If ID is unique, proceed with adding the employee
    emp.id = enteredId;
    c_textcolor(1);
    c_gotoxy(40, 12);
    printf("Enter Name: ");
    scanf(" %[^\n]s", emp.name);

    c_gotoxy(40, 14);
    printf("Enter Position: ");
    scanf(" %[^\n]s", emp.position);

    c_gotoxy(40, 16);
    c_textcolor(2);
    printf("Enter Salary: ");
    
    // Validate Salary input
    while (scanf("%f", &emp.salary) != 1) {
        c_textcolor(4);
        c_gotoxy(40, 18);
        printf("Invalid input! Please enter a valid Salary: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Write employee data to the file using a delimiter
    fprintf(file, "%d|%s|%.2f|%s\n", emp.id, emp.name, emp.salary, emp.position);
    fclose(file);

    c_textcolor(2);
    c_gotoxy(40, 20);  // Move the cursor down to a new line
    printf("Employee added successfully to %s!\n", filePath);
    c_getch();  // Wait for user to press a key
}

void displayEmployees() {
    c_clrscr();  // Clear the screen
    c_textcolor(15);  // Set text color to white for the title
    c_gotoxy(40, 6);  // Move the cursor to (40, 6)
    printf("=== Employee Data Display ===\n");

    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);  // Set text color to green for the prompt
    c_gotoxy(40, 8);
    printf("Enter the file path to display the employee data: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);  // Set text color to red for error messages
        c_gotoxy(40, 10);
        perror("Error opening file");
        c_getch();  // Wait for user to press a key
        return;
    }

    Employee emp;
    c_textcolor(15);  // Set text color to white for the headings
    c_gotoxy(40, 10);
    printf("%-10s%-30s%-10s%-20s\n", "ID", "Name", "Salary", "Position");
    printf("----------------------------------------------------------------------------------------------------\n");

    int line = 12;  // Start printing employees from line 12
    while (fscanf(file, "%d|%49[^|]|%f|%49[^\n]", &emp.id, emp.name, &emp.salary, emp.position) == 4) {
        c_gotoxy(40, line);
        c_textcolor(2);  // Set text color to green for employee data
        printf("%-10d%-30s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
        line++;
    }

    fclose(file);
    c_textcolor(15);  // Reset text color to white
    c_gotoxy(40, line);
    printf("Press any key to continue...");
    c_getch();  // Wait for user to press a key
}

// Function to delete an employee from a file
void deleteEmployee() {
    c_clrscr();  // Clear the screen
    c_gotoxy(40, 6);  // Move the cursor to (40, 6)
    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);
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
    c_gotoxy(40, 8);
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
        c_getch();  // Wait for user to press a key
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
    c_gotoxy(40, 10);
    printf("Employee with ID %d deleted successfully.\n", deleteId);
    c_getch();  // Wait for user to press a key
}

int isValidDateFormat(const char *date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else if (!isdigit(date[i])) {
            return 0;
        }
    }
    return 1;
}

void displayReports() {
    c_clrscr();  // Clear the screen
    c_textcolor(15);  // Set text color to white for the title
    c_gotoxy(40, 6);  // Move the cursor to (40, 6)
    printf("=== Report Display ===\n");

    char filePath[MAX_PATH_LENGTH];
    c_textcolor(2);  // Set text color to green for the prompt
    c_gotoxy(40, 8);
    printf("Enter the file path to display the reports: ");
    scanf("%255s", filePath);

    normalizeFilePath(filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        c_textcolor(4);  // Set text color to red for error messages
        c_gotoxy(40, 10);
        perror("Error opening file");
        c_getch();  // Wait for user to press a key
        return;
    }

    struct Report rep;
    c_textcolor(15);  // Set text color to white for the headings
    c_gotoxy(40, 10);
    printf("%-10s%-12s%-12s%-12s\n", "ID", "Date", "Loss", "Earnings");
    printf("-----------------------------------------------------------\n");

    int line = 12;
    while (fscanf(file, "%d|%10[^|]|%f|%f", &rep.id, rep.date, &rep.loss, &rep.earnings) == 4) {
        rep.profit = rep.earnings - rep.loss;
        c_gotoxy(40, line);
        c_textcolor(2);  // Set text color to green for report data
        printf("%-10d%-12s%-12.2f%-12.2f\n", rep.id, rep.date, rep.loss, rep.earnings);
        line++;
    }

    fclose(file);
    c_textcolor(15);  // Reset text color to white
    c_gotoxy(40, line);
    printf("Press any key to continue...");
    c_getch();  // Wait for user to press a key
}

// Function to check if ID is unique in the specified file
int isUniqueID(const char *filePath, int id) {
    struct Report report;
    FILE *file = fopen(filePath, "r");

    if (file == NULL) return 1; // If file does not exist, ID is unique by default

    while (fscanf(file, "%d\t%10s\t%f\t%f\t%f\n", &report.id, report.date, &report.earnings, &report.loss, &report.profit) != EOF) {
        if (report.id == id) {
            fclose(file);
            return 0; // ID already exists
        }
    }
    fclose(file);
    return 1; // ID is unique
}

// Function to add a new report entry to the specified file
void addReportEntry(const char *filePath) {
    struct Report report;
    normalizeFilePath((char*)filePath);

    FILE *file = fopen(filePath, "a"); // Open file in append mode
    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        return;
    }

    // Get report ID with unique ID check
    do {
        printf("Enter Report ID: ");
        scanf("%d", &report.id);
        if (!isUniqueID(filePath, report.id)) {
            printf("Error: ID already exists. Please enter a unique ID.\n");
        }
    } while (!isUniqueID(filePath, report.id));

    // Get date with format validation
    do {
        printf("Enter Date (YYYY-MM-DD): ");
        scanf("%s", report.date);
        if (!isValidDateFormat(report.date)) {
            printf("Error: Invalid date format. Please enter in YYYY-MM-DD format.\n");
        }
    } while (!isValidDateFormat(report.date));

    // Get daily earnings and loss
    printf("Enter Daily Earnings (Won): ");
    scanf("%f", &report.earnings);

    printf("Enter Daily Loss: ");
    scanf("%f", &report.loss);

    // Calculate profit
    report.profit = report.earnings - report.loss;

    // Write the report entry to the file in a tabular format
    fprintf(file, "%d\t%s\t%.2f\t%.2f\t%.2f\n", report.id, report.date, report.earnings, report.loss, report.profit);
    fclose(file);

    printf("Report entry added successfully to %s!\n", filePath);
}

#endif // FILEHANDLING_H