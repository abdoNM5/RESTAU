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
    if (year < 1900 || year > 2100)
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
    // Clear the screen for a clean interface
    c_clrscr();

    // Clear the screen after input
    c_clrscr();
    c_textcolor(14);
    c_gotoxy(20, 5);
    printf("Enter client's name: ");
    c_textcolor(15);
    fgets(res->client_name, MAX_NAME_LENGTH1, stdin);
    res->client_name[strcspn(res->client_name, "\n")] = '\0'; // Remove the newline character

    // Clear the screen after input
    c_clrscr();

    // Validate and input the reservation type (p/i for phone/instant)
    int valid_type = 0;
    while (!valid_type)
    {
        c_textcolor(14);
        c_gotoxy(20, 5);
        printf("Enter reservation type (p for phone, i for instant): ");
        c_textcolor(15);
        fgets(res->reservation_type, MAX_NAME_LENGTH1, stdin);
        res->reservation_type[strcspn(res->reservation_type, "\n")] = '\0'; // Remove newline character

        // Validate the input (only accept 'p' or 'i')
        if (strcmp(res->reservation_type, "p") == 0)
        {
            strcpy(res->reservation_type, "phone"); // Convert 'p' to 'phone'
            valid_type = 1;                         // Valid input for phone
        }
        else if (strcmp(res->reservation_type, "i") == 0)
        {
            strcpy(res->reservation_type, "instant"); // Convert 'i' to 'instant'
            valid_type = 1;                           // Valid input for instant
        }
        else
        {
            // Invalid input, ask the user to re-enter
            c_textcolor(4);
            c_gotoxy(20, 7);
            printf("Error: Invalid reservation type. Please enter 'p' for phone or 'i' for instant.\n");
        }
    }

    // Clear the screen after input
    c_clrscr();

    int valid_date = 0;
    while (!valid_date)
    {
        c_clrscr(); // Clear screen for each new attempt
        c_textcolor(14);
        c_gotoxy(20, 5);
        printf("Enter reservation date (YYYY-MM-DD): ");
        c_textcolor(15);
        fgets(res->reservation_date, MAX_NAME_LENGTH1, stdin);
        res->reservation_date[strcspn(res->reservation_date, "\n")] = '\0'; // Remove newline character

        if (validate_date(res->reservation_date))
        {
            valid_date = 1; // Proceed if valid
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(20, 7);
            printf("Error: Invalid date format. Please enter in the format YYYY-MM-DD.\n");
        }
    }

    // Inside the reservation time input section
    int valid_time = 0;
    while (!valid_time)
    {
        c_clrscr(); // Clear screen for each new attempt
        c_textcolor(14);
        c_gotoxy(20, 5);
        printf("Enter reservation time (HH:MM): ");
        c_textcolor(15);
        fgets(res->reservation_time, MAX_NAME_LENGTH1, stdin);
        res->reservation_time[strcspn(res->reservation_time, "\n")] = '\0'; // Remove newline character

        if (validate_time(res->reservation_time))
        {
            valid_time = 1; // Proceed if valid
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(10, 7);
            printf("Error: Invalid time format. Please enter in the format HH:MM (24-hour format).\n");
        }
    }
    int table_available = 0;
    while (!table_available)
    {
        c_textcolor(14);
        c_gotoxy(20, 5);
        printf("Enter table number for reservation: ");
        c_textcolor(15);
        scanf("%d", &res->table_number);
        getchar(); // To consume the newline character

        table_available = 1; // Assume table is available unless we find otherwise
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
                    c_gotoxy(20, 7);
                    printf("Error: Table %d is already reserved for %s from %s to %d:%d on %s.\n",
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
            c_gotoxy(20, 9);
            printf("Please choose a different table number or time slot.\n");
        }
    }

    // Assign a unique reservation ID
    res->id = ++last_reservation_id;

    // Store the reservation in the binary file
    store_reservation(res, file_path);

    // Add to the in-memory reservation list
    reservations[reservation_count++] = *res;

    c_clrscr();
    c_textcolor(2);
    c_gotoxy(20, 5);
    printf("Reservation for %s at table %d on %s at %s successfully created with ID: %d\n",
           res->client_name, res->table_number, res->reservation_date, res->reservation_time, res->id);
           c_textcolor(15);
    return 1; // Reservation successful
}
// Function to display all reservations from a binary file
void display_reservations(const char *file_path)
{
    c_clrscr();
    FILE *file = fopen(file_path, "rb"); // Open the binary file for reading
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Print table headers
    c_textcolor(14);
    printf("\n----------------------------------------------- Reservation List ------------------------------------------------\n");
    c_textcolor(1);
    printf("|  %-10s |  %-20s |  %-15s |  %-15s |  %-8s |  %-12s |\n",
           "ID", "Client Name", "Reservation Type", "Reservation Date", "Time", "Table Number");
    c_textcolor(14);
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    Reservation res;
    size_t size = sizeof(Reservation);

    // Read reservations from the binary file and print them
    while (fread(&res, size, 1, file) == 1)
    {
        c_textcolor(3);
        // Print the reservation details
        printf("|  %-10d |  %-20s |  %-15s  |  %-15s  |  %-8s |  %-12d |\n",
               res.id, res.client_name, res.reservation_type, res.reservation_date, res.reservation_time, res.table_number);
    }
    c_textcolor(14);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
    c_textcolor(15);
}

// Function to delete a reservation by ID in binary files
void delete_reservation(int id, const char *file_path)
{
    c_clrscr();
    int found = 0;                                          // Flag to check if reservation with the given ID is found
    FILE *file = fopen(file_path, "rb");                    // Open the binary file for reading
    FILE *temp_file = fopen("temp_reservations.bin", "wb"); // Open a temporary binary file for writing

    if (file == NULL || temp_file == NULL)
    {
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
            c_gotoxy(20, 7);
            printf("Reservation with ID %d successfully deleted.\n", id);
        }
        else
        {
            c_textcolor(4);
            c_gotoxy(20, 7);
            printf("Error deleting the reservation file.\n");
        }
    }
    else
    {
        c_textcolor(4);
        c_gotoxy(20, 7);
        printf("No reservation found with ID %d.\n", id);
        remove("temp_reservations.bin"); // Clean up the temporary file if no reservation was deleted
        c_textcolor(15);
    }
}
#endif