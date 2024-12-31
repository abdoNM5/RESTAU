#ifndef RESERVATION_H
#define RESERVATION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conio.h"
#include <conio.h>
#define MAX_NAME_LENGTH1 100
#define MAX_RESERVATIONS 100

// Structure for Reservation
typedef struct
{
    int id;                                 // Unique ID for each reservation
    char client_name[MAX_NAME_LENGTH1];      // Name of the client
    char reservation_type[MAX_NAME_LENGTH1]; // Type of reservation (phone/instant)
    char reservation_date[MAX_NAME_LENGTH1]; // Date of reservation
    char reservation_time[MAX_NAME_LENGTH1]; // Time of reservation (HH:MM)
    int table_number;                       // Table number assigned for reservation
} Reservation;

// Structure to store all reservations
Reservation reservations[MAX_RESERVATIONS];
int reservation_count = 0;   // Keep track of how many reservations exist
int last_reservation_id = 0; // Track the last assigned reservation ID

// Function to load reservations from the binary file
void load_reservations(const char *file_path)
{
    FILE *file = fopen(file_path, "rb"); // Open the binary file for reading
    if (file == NULL)
    {
        printf("No existing reservations found.\n");
        return;
    }

    Reservation res;
    size_t size = sizeof(Reservation);
    while (fread(&res, size, 1, file) == 1)
    {
        reservations[reservation_count++] = res;
        last_reservation_id = res.id > last_reservation_id ? res.id : last_reservation_id;
    }

    fclose(file);
}

// Function to store the reservation in a binary file
void store_reservation(Reservation *res, const char *file_path)
{
    FILE *file = fopen(file_path, "ab"); // Open the file in binary append mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Write the reservation structure to the file in binary format
    size_t size = sizeof(Reservation);
    size_t written = fwrite(res, size, 1, file);

    if (written != 1)
    {
        c_textcolor(4);
        c_gotoxy(20, 7);
        printf("Error writing reservation to the file.\n");
    }
    fclose(file);
}
int validate_time(const char *time)
{
    // Check the format: length must be 5 (HH:MM)
    if (strlen(time) != 5 || time[2] != ':')
    {
        return 0; // Invalid format
    }

    // Extract hours and minutes as integers
    int hours = atoi(time);
    int minutes = atoi(&time[3]);

    // Validate hours and minutes
    if (hours < 0 || hours > 23)
    {
        return 0; // Invalid hours
    }
    if (minutes < 0 || minutes > 59)
    {
        return 0; // Invalid minutes
    }

    return 1; // Valid time
}
int validate_date(const char *date)
{
    // Check the format: length must be 10 (YYYY-MM-DD)
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-')
    {
        return 0; // Invalid format
    }

    // Extract year, month, and day as integers
    int year = atoi(date);
    int month = atoi(&date[5]);
    int day = atoi(&date[8]);

    // Validate year
    if (year < 2024 || year > 2100)
    {
        return 0; // Invalid year
    }

    // Validate month
    if (month < 1 || month > 12)
    {
        return 0; // Invalid month
    }

    // Validate day based on the month
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap years
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        days_in_month[1] = 29; // February has 29 days in a leap year
    }

    if (day < 1 || day > days_in_month[month - 1])
    {
        return 0; // Invalid day
    }

    return 1; // Valid date
}
// Function to create a new reservation
int create_reservation(Reservation *res, const char *file_path)
{
    int line = 12; // Starting y-coordinate for prompts and messages
    int spacing = 2; // Spacing between lines

    // Input client's name
    c_textcolor(14);
    c_gotoxy(32, line);
    printf("Enter client's name: ");
    c_textcolor(15);
    c_gotoxy(32, line + 1);
    fgets(res->client_name, MAX_NAME_LENGTH1, stdin);
    res->client_name[strcspn(res->client_name, "\n")] = '\0'; // Remove newline
    line += spacing + 1; // Move down

    // Input reservation type
    int valid_type = 0;
    while (!valid_type)
    {
        c_textcolor(14);
        c_gotoxy(32, line);
        printf("Enter reservation type (p for phone, i for instant): ");
        c_textcolor(15);
        c_gotoxy(32, line + 1);
        fgets(res->reservation_type, MAX_NAME_LENGTH1, stdin);
        res->reservation_type[strcspn(res->reservation_type, "\n")] = '\0'; // Remove newline

        if (strcmp(res->reservation_type, "p") == 0)
        {
            strcpy(res->reservation_type, "phone");
            valid_type = 1;
        }
        else if (strcmp(res->reservation_type, "i") == 0)
        {
            strcpy(res->reservation_type, "instant");
            valid_type = 1;
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(32, line + 2);
            printf("Error: Invalid type. Enter 'p' for phone or 'i' for instant.");
            line += spacing + 2; // Adjust for error message
        }
    }
    line += spacing; // Move down after successful input

    // Input reservation date
    int valid_date = 0;
    while (!valid_date)
    {
        c_textcolor(14);
        c_gotoxy(32, line);
        printf("Enter reservation date (YYYY-MM-DD): ");
        c_textcolor(15);
        c_gotoxy(32, line + 1);
        fgets(res->reservation_date, MAX_NAME_LENGTH1, stdin);
        res->reservation_date[strcspn(res->reservation_date, "\n")] = '\0'; // Remove newline

        if (validate_date(res->reservation_date))
        {
            valid_date = 1;
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(32, line + 2);
            printf("Error: Invalid date format. Use YYYY-MM-DD.");
            line += spacing + 2; // Adjust for error message
        }
    }
    line += spacing; // Move down after successful input

    // Input reservation time
    int valid_time = 0;
    while (!valid_time)
    {
        c_textcolor(14);
        c_gotoxy(32, line);
        printf("Enter reservation time (HH:MM): ");
        c_textcolor(15);
        c_gotoxy(32, line + 1);
        fgets(res->reservation_time, MAX_NAME_LENGTH1, stdin);
        res->reservation_time[strcspn(res->reservation_time, "\n")] = '\0'; // Remove newline

        if (validate_time(res->reservation_time))
        {
            valid_time = 1;
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(32, line + 2);
            printf("Error: Invalid time. Use HH:MM (24-hour format).");
            line += spacing + 2; // Adjust for error message
        }
    }
    line += spacing; // Move down after successful input

    // Input table number and check availability
    int table_available = 0;
    while (!table_available)
    {
        c_textcolor(14);
        c_gotoxy(32, line);
        printf("Enter table number for reservation: ");
        c_textcolor(15);
        c_gotoxy(32, line + 1);
        scanf("%d", &res->table_number);
        getchar(); // Consume newline

        table_available = 1; // Assume availability initially
        for (int i = 0; i < reservation_count; i++)
        {
            if (reservations[i].table_number == res->table_number &&
                strcmp(reservations[i].reservation_date, res->reservation_date) == 0)
            {
                int start_hour, start_minute, end_hour, end_minute;
                int existing_start_hour, existing_start_minute, existing_end_hour, existing_end_minute;

                sscanf(res->reservation_time, "%d:%d", &start_hour, &start_minute);
                end_hour = start_hour + 2;
                end_minute = start_minute;

                sscanf(reservations[i].reservation_time, "%d:%d", &existing_start_hour, &existing_start_minute);
                existing_end_hour = existing_start_hour + 2;
                existing_end_minute = existing_start_minute;

                if ((start_hour < existing_end_hour || (start_hour == existing_end_hour && start_minute < existing_end_minute)) &&
                    (end_hour > existing_start_hour || (end_hour == existing_start_hour && end_minute > existing_start_minute)))
                {
                    c_textcolor(4);
                    c_gotoxy(32, line + 2);
                    printf("Error: Table %d is already reserved by %s from %s to %d:%d on %s.",
                           res->table_number, reservations[i].client_name, reservations[i].reservation_time,
                           existing_end_hour, existing_end_minute, res->reservation_date);
                    table_available = 0;
                    break;
                }
            }
        }

        if (!table_available)
        {
            c_textcolor(2);
            c_gotoxy(32, line + 3);
            printf("Choose a different table number or time slot.");
            line += spacing + 3; // Adjust for error message
        }
    }

    // Assign a unique ID and store the reservation
    res->id = ++last_reservation_id;
    store_reservation(res, file_path);
    reservations[reservation_count++] = *res;

    c_textcolor(2);
    c_gotoxy(32, line + 2);
    printf("Reservation created successfully!");
    c_gotoxy(32, line + 3);
    printf("Client: %s, Table: %d, Date: %s, Time: %s, ID: %d",
           res->client_name, res->table_number, res->reservation_date, res->reservation_time, res->id);
    c_textcolor(15); // Reset text color

    return 1; // Success
}


// Function to display all reservations from a binary file
void display_reservations(const char *file_path)
{
    FILE *file = fopen(file_path, "rb"); // Open the binary file for reading
    if (file == NULL)
    {
        c_textcolor(12); // Set red text for error
        c_gotoxy(32, 14);
        printf("Error opening file.\n");
        return;
    }

    // Print table headers within the bounds
    c_textcolor(14); // Yellow for headers
    c_gotoxy(31, 12);
    printf("---------------------------------------------------------------------------");
    c_gotoxy(31, 13);
    printf("|  %-5s | %-15s |  %-10s |  %-11s | %-6s |%-5s|",
           "ID", "Client Name", "Reserv_Type", "Reserv_Date", "Time", "Tabl_NB");
    c_gotoxy(31, 14);
    printf("---------------------------------------------------------------------------");

    Reservation res;
    size_t size = sizeof(Reservation);
    int y = 15; // Start at y = 15 for the first data row

    // Read reservations from the binary file and print them
    while (fread(&res, size, 1, file) == 1)
    {
        // Stop printing if we exceed the maximum y-coordinate
        if (y > 39)
        {
            c_textcolor(12); // Red for warning
            c_gotoxy(31, 40);
            printf("Reached maximum displayable rows. Additional entries not shown.\n");
            break;
        }

        c_textcolor(3); // Cyan for data rows
        c_gotoxy(31, y++);
        printf("|  %-5d | %-15s |  %-10s  |  %-11s | %-6s | %-5d |",
               res.id, res.client_name, res.reservation_type, res.reservation_date, res.reservation_time, res.table_number);
    }

    // Print bottom border and close file
    c_textcolor(14); // Yellow for footer
    if (y <= 39) // Ensure footer stays in bounds
    {
        c_gotoxy(31, y);
        printf("---------------------------------------------------------------------------");
    }

    fclose(file);
    c_textcolor(15); // Reset to default color
}


// Function to delete a reservation by ID in binary files
void delete_reservation(int id, const char *file_path)
{
    int found = 0;                                          // Flag to check if reservation with the given ID is found
    FILE *file = fopen(file_path, "rb");                    // Open the binary file for reading
    FILE *temp_file = fopen("temp_reservations.bin", "wb"); // Open a temporary binary file for writing

    if (file == NULL || temp_file == NULL)
    {   c_gotoxy(40,14);
        c_textcolor(4);
        printf("Error opening files.\n");
        return;
    }

    Reservation res;
    size_t size = sizeof(Reservation);

    // Process each reservation in the binary file
    while (fread(&res, size, 1, file) == 1)
    {
        // If the reservation ID matches, don't write it to the temp file (skip this reservation)
        if (res.id == id)
        {
            found = 1;
            continue; // Skip writing this reservation to the temp file
        }

        // Write the reservation to the temp file if it's not the one to be deleted
        fwrite(&res, size, 1, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    // Replace the original file with the temp file if the reservation was found
    if (found)
    {
        if (remove(file_path) == 0 && rename("temp_reservations.bin", file_path) == 0)
        {
            c_textcolor(2);
            c_gotoxy(38, 18);
            printf("Reservation with ID %d successfully deleted.\n", id);
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(40, 15);
            printf("Error deleting the reservation file.\n");
        }
    }
    else
    {
        c_textcolor(4);
        c_gotoxy(39, 18);
        printf("No reservation found with ID %d.\n", id);
        remove("temp_reservations.bin"); // Clean up the temporary file if no reservation was deleted
        c_textcolor(15);
    }
}
#endif