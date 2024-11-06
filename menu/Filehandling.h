
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;                // Unique ID for the employee
    char name[50];         // Name of the employee
    float salary;          // Salary of the employee
    char position[50];     // Position of the employee
} Employee;


// Function to normalize the file path (remove quotes and replace backslashes with forward slashes)
void normalizePathWithQuotes(char *path) {
    // Remove quotes at the beginning and end
    int len = strlen(path);
    if (path[0] == '"') {
        memmove(path, path + 1, len);  // Shift the string left (remove first quote)
        len--;
    }
    if (path[len - 1] == '"') {
        path[len - 1] = '\0';  // Remove last quote
    }

    // Replace backslashes with forward slashes
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '\\') {
            path[i] = '/';  // Replace backslash with forward slash
        }
    }
}

// Function to add an employee to a specified file
void addEmployee() {
    char filePath[200];
    printf("Enter the file path to save the employee data (with quotes or slashes): ");
    scanf("%s", filePath);

    normalizePathWithQuotes(filePath);  // Normalize the file path

    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", emp.name);  // To read full name with spaces
    printf("Enter Position: ");
    scanf(" %[^\n]s", emp.position);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fprintf(file, "%d %s %.2f %s\n", emp.id, emp.name, emp.salary, emp.position);
    fclose(file);
    printf("Employee added successfully to %s!\n", filePath);
}

// Function to display all employees from the file with proper formatting
void displayEmployees() {
    char filePath[200];
    printf("Enter the file path to display the employee data: ");
    scanf("%s", filePath);

    normalizePathWithQuotes(filePath);  // Normalize the file path

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Employee emp;

    // Print header with better spacing for alignment
    printf("%-10s%-30s%-10s%-20s\n", "ID", "Name", "Salary", "Position");
    printf("-------------------------------------------------------------\n");

    // Read employee data and display it with proper alignment
    while (fscanf(file, "%d %49s %f %49s", &emp.id, emp.name, &emp.salary, emp.position) != EOF) {
        // Adjust the widths of the columns using `%-10d`, `%-30s`, `%-10.2f`, and `%-20s`
        printf("%-10d%-30s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
    }

    fclose(file);
}
