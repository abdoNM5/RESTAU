
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 200
typedef struct {
    int id;                // Unique ID for the employee
    char name[50];         // Name of the employee
    float salary;          // Salary of the employee
    char position[50];     // Position of the employee
} Employee;
void deltete_employee(){
    char filePath[200];
    printf("Enter the file path to delete an employee data: ");
    scanf("%s", filePath);
    normalizeFilePath(filePath);
    FILE *file=fopen(filePath,"a");
    if(file==NULL){
        perror("THERE IS ERROR ");
        return;
    }
    int deleteId;
    printf("enter the employee ID to delete");
    scanf("%d",&deleteId);
    Employee emp;
    int found =0;
    char buffer[1000];  // Buffer to hold new content
    char line[100];     // To store each line temporarily
    buffer[0] = '\0';   // Initialize buffer as an empty string
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%d",&emp.id);
        if(emp.id != deleteId){
            strcat(buffer,line);
        }
        else{
        found=1;
    }
    }
    fclose(file);
    if (!found){
        printf("EMPLOYEE WITH ID %d  not found .\n",deleteId);
        return;
    }
   
    // Overwrite the file with the contents of buffer
    file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fputs(buffer, file);
    fclose(file);

    printf("Employee with ID %d deleted successfully.\n", deleteId);
}

// Function to normalize the file path (remove quotes and replace backslashes with forward slashes)
void normalizeFilePath(char *path)
{
    int len = strlen(path);

    // Remove quotes at the beginning and end, if they exist
    if (path[0] == '"')
    {
        memmove(path, path + 1, len); // Shift the string left (remove first quote)
        len--;
    }
    if (path[len - 1] == '"')
    {
        path[len - 1] = '\0'; // Remove last quote
    }

    // Replace backslashes with forward slashes
    for (int i = 0; path[i] != '\0'; i++)
    {
        if (path[i] == '\\')
        {
            path[i] = '/'; // Replace backslash with forward slash
        }
    }
}

// Function to add an employee to a specified file
void addEmployee()
{
    char filePath[MAX_PATH_LENGTH];
    printf("Enter the file path to save the employee data (with quotes or slashes): ");
    scanf("%199s", filePath); // Read file path with a limit to avoid buffer overflow

    normalizeFilePath(filePath); // Normalize the file path

    // Open the file for appending
    FILE *file = fopen(filePath, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    Employee emp;

    // Get employee data from the user
    printf("Enter Employee ID: ");
    while (scanf("%d", &emp.id) != 1) {
        printf("Invalid input! Please enter a valid Employee ID: ");
        while(getchar() != '\n'); // Clear the input buffer
    }
    
    printf("Enter Name: ");
    scanf(" %[^\n]s", emp.name); // To read full name with spaces

    printf("Enter Position: ");
    scanf(" %[^\n]s", emp.position); // To read position with spaces

    printf("Enter Salary: ");
    while (scanf("%f", &emp.salary) != 1) {
        printf("Invalid input! Please enter a valid Salary: ");
        while(getchar() != '\n'); // Clear the input buffer
    }

    // Write employee data to the file
    fprintf(file, "%d %s %.2f %s\n", emp.id, emp.name, emp.salary, emp.position);
    fclose(file);

    printf("Employee added successfully to %s!\n", filePath);
}
// Function to display all employees from the file with proper formatting
void displayEmployees()
{
    char filePath[200];
    printf("Enter the file path to display the employee data: ");
    scanf("%s", filePath);

    normalizeFilePath(filePath); // Normalize the file path

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    Employee emp;

    // Print header with better spacing for alignment
    printf("%-10s%-30s%-10s%-20s\n", "ID", "Name", "Salary", "Position");
    printf("-------------------------------------------------------------\n");

    // Read employee data and display it with proper alignment
    while (fscanf(file, "%d %49s %f %49s", &emp.id, emp.name, &emp.salary, emp.position) != EOF)
    {
        // Adjust the widths of the columns using `%-10d`, `%-30s`, `%-10.2f`, and `%-20s`
        printf("%-10d%-30s%-10.2f%-20s\n", emp.id, emp.name, emp.salary, emp.position);
    }

    fclose(file);
}