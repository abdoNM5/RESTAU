#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filehandling.h"
#define MAX_NAME_LENGTH 100
#define MAX_RESERVATIONS 100

// Structure for Reservation
typedef struct
{
    int id;                                 // Unique ID for each reservation
    char client_name[MAX_NAME_LENGTH];      // Name of the client
    char reservation_type[MAX_NAME_LENGTH]; // Type of reservation (phone/instant)
    char reservation_date[MAX_NAME_LENGTH]; // Date of reservation
    char reservation_time[MAX_NAME_LENGTH]; // Time of reservation (HH:MM)
    int table_number;                       // Table number assigned for reservation
} Reservation;

// Structure to store all reservations
Reservation reservations[MAX_RESERVATIONS];
int reservation_count = 0;   // Keep track of how many reservations exist
int last_reservation_id = 0; // Track the last assigned reservation ID

// Function to create a new reservation
int create_reservation(Reservation *res,const char *file_path)
{
    printf("Enter client's name: ");
    fgets(res->client_name, MAX_NAME_LENGTH, stdin);
    res->client_name[strcspn(res->client_name, "\n")] = '\0'; // Remove the newline character

    printf("Enter reservation type (phone/instant): ");
    fgets(res->reservation_type, MAX_NAME_LENGTH, stdin);
    res->reservation_type[strcspn(res->reservation_type, "\n")] = '\0';

    printf("Enter reservation date (YYYY-MM-DD): ");
    fgets(res->reservation_date, MAX_NAME_LENGTH, stdin);
    res->reservation_date[strcspn(res->reservation_date, "\n")] = '\0';

    printf("Enter reservation time (HH:MM): ");
    fgets(res->reservation_time, MAX_NAME_LENGTH, stdin);
    res->reservation_time[strcspn(res->reservation_time, "\n")] = '\0';

    // Start a loop that keeps asking for a table number if it's already reserved
    int table_available = 0;
    while (!table_available)
    {
        printf("Enter table number for reservation: ");
        scanf("%d", &res->table_number);
        getchar(); // To consume the newline character

        // Check if the table is available at the given time and date
        table_available = 1; // Assume table is available unless we find otherwise
        for (int i = 0; i < reservation_count; i++)
        {
            // Check if the same table is already reserved for the same date and time
            if (reservations[i].table_number == res->table_number &&
                strcmp(reservations[i].reservation_date, res->reservation_date) == 0 &&
                strcmp(reservations[i].reservation_time, res->reservation_time) == 0)
            {
                printf("Error: Table %d is already reserved for %s at %s on %s.\n",
                       res->table_number, reservations[i].client_name, reservations[i].reservation_time, res->reservation_date);
                table_available = 0; // Table is not available, continue asking
                break;               // Exit the loop and re-prompt for a table number
            }
        }

        if (!table_available)
        {
            printf("Please choose a different table number.\n");
        }
    }

    // Assign a unique reservation ID
    res->id = ++last_reservation_id;

    // Store the reservation
    reservations[reservation_count++] = *res;
    printf("Reservation for %s at table %d on %s at %s successfully created with ID: %d\n",
           res->client_name, res->table_number, res->reservation_date, res->reservation_time, res->id);
    return 1; // Reservation successful
}

// Function to store the reservation in a file
void store_reservation(Reservation *res, const char *file_path)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "Reservation ID: %d\n", res->id);
    fprintf(file, "Client Name: %s\n", res->client_name);
    fprintf(file, "Reservation Type: %s\n", res->reservation_type);
    fprintf(file, "Reservation Date: %s\n", res->reservation_date);
    fprintf(file, "Reservation Time: %s\n", res->reservation_time);
    fprintf(file, "Table Number: %d\n", res->table_number);
    fprintf(file, "----------------------------------------\n");
    fclose(file);
}

// Function to display all reservations with ID
void display_reservations(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Print table headers
    printf("\n------------------------------------------ Reservation List ------------------------------------\n");
    printf("|  %-10s |  %-20s |  %-15s |  %-15s |  %-8s |  %-12s |\n",
           "ID", "Client Name", "Reservation Type", "Reservation Date", "Time", "Table Number");
    printf("------------------------------------------------------------------------------------------------------\n");

    char line[256];
    int line_count = 0;

    // Read file line by line and print reservations in a vertical structure
    int id, table_number;
    char client_name[MAX_NAME_LENGTH], reservation_type[MAX_NAME_LENGTH], reservation_date[MAX_NAME_LENGTH], reservation_time[MAX_NAME_LENGTH];

    while (fgets(line, sizeof(line), file))
    {
        // Remove the newline character from the line
        line[strcspn(line, "\n")] = '\0';

        if (strstr(line, "Reservation ID:") != NULL)
        {
            sscanf(line, "Reservation ID: %d", &id);
        }
        else if (strstr(line, "Client Name:") != NULL)
        {
            sscanf(line, "Client Name: %[^\n]", client_name);
        }
        else if (strstr(line, "Reservation Type:") != NULL)
        {
            sscanf(line, "Reservation Type: %[^\n]", reservation_type);
        }
        else if (strstr(line, "Reservation Date:") != NULL)
        {
            sscanf(line, "Reservation Date: %[^\n]", reservation_date);
        }
        else if (strstr(line, "Reservation Time:") != NULL)
        {
            sscanf(line, "Reservation Time: %[^\n]", reservation_time);
        }
        else if (strstr(line, "Table Number:") != NULL)
        {
            sscanf(line, "Table Number: %d", &table_number);

            // Print the reservation in a line-by-line format
            printf("|  %-10d |  %-20s |  %-15s |  %-15s |  %-8s |  %-12d |\n",
                   id, client_name, reservation_type, reservation_date, reservation_time, table_number);
        }
    }

    printf("--------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

// Function to delete a reservation by ID
void delete_reservation(int id, const char *file_path)
{
    int found = 0; // Flag to check if reservation with given ID is found
    FILE *file = fopen(file_path, "r");
    FILE *temp_file = fopen("temp_reservations.txt", "w");

    if (file == NULL || temp_file == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    char line[256];
    int temp_id = -1;
    int skip_block = 0; // Flag to indicate whether we should skip a block of lines

    // Process each line in the original file
    while (fgets(line, sizeof(line), file))
    {
        // Check if line contains "Reservation ID:" and extract the ID
        if (strstr(line, "Reservation ID:") != NULL)
        {
            sscanf(line, "Reservation ID: %d", &temp_id);

            // If this is the reservation ID to delete, set skip_block flag
            if (temp_id == id)
            {
                found = 1;
                skip_block = 1; // Start skipping this reservation block
                continue;       // Skip the current line without writing to temp file
            }
        }

        // Reset skip_block at the end of a reservation block
        if (strstr(line, "----------------------------------------") != NULL)
        {
            skip_block = 0; // End skipping once the block ends
        }

        // Write to temp file if we are not in the skip block
        if (!skip_block)
        {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace original file with the updated file if reservation was found
    if (found)
    {
        remove(file_path);                          // Delete the old file
        rename("temp_reservations.txt", file_path); // Rename temp file to original
        printf("Reservation with ID %d successfully deleted from file and display.\n", id);
    }
    else
    {
        printf("No reservation found with ID %d.\n", id);
        remove("temp_reservations.txt"); // Clean up temp file if no reservation was deleted
    }
}
