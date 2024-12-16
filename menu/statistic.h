#ifndef STAT_H
#define STAT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commande.h"
#include "conio.h"

// Function to extract data from the binary file and generate a summarized data file for gnuplot
void generateDataFileFromBinary(const char *binaryFile, const char *outputDataFile)
{
    FILE *file = fopen(binaryFile, "rb");
    if (file == NULL)
    {
        perror("Error opening binary file");
        return;
    }

    FILE *outputFile = fopen(outputDataFile, "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(file);
        return;
    }

    // Data structure to store totals by date
    typedef struct
    {
        char date[11]; // Format "YYYY-MM-DD"
        float total_price;
    } DateTotal;

    DateTotal totals[1000]; // Adjust size if needed
    int totals_count = 0;

    Command command;
    while (fread(&command, sizeof(Command), 1, file) == 1)
    {
        // Extract the date portion (YYYY-MM-DD) from the timestamp
        char date_only[11];
        strncpy(date_only, command.date, 10);
        date_only[10] = '\0'; // Null-terminate the string

        // Search for the date in the totals array
        int found = 0;
        for (int i = 0; i < totals_count; i++)
        {
            if (strcmp(totals[i].date, date_only) == 0)
            {
                // Date exists, add to total price
                totals[i].total_price += command.total_price;
                found = 1;
                break;
            }
        }

        // If the date was not found, add a new entry
        if (!found)
        {
            strcpy(totals[totals_count].date, date_only);
            totals[totals_count].total_price = command.total_price;
            totals_count++;
        }
    }

    // Write the accumulated totals to the output file
    for (int i = 0; i < totals_count; i++)
    {
        fprintf(outputFile, "%s %.2f\n", totals[i].date, totals[i].total_price);
    }

    fclose(file);
    fclose(outputFile);
    printf("Data file '%s' generated successfully from binary file '%s'!\n", outputDataFile,binaryFile);
}

// Function to execute the gnuplot script
void runGnuplot(const char *scriptFile)
{
    char command[256];
    snprintf(command, sizeof(command), "gnuplot \"%s\"", scriptFile);
    int result = system(command);
    if (result == 0)
    {   
        c_gotoxy(40, 18);
        c_textcolor(6);
        printf("Graph generated successfully!\n");
    }
    else
    {   
        c_gotoxy(40, 18);
        c_textcolor(4);
        printf("Error executing gnuplot script.\n");
    }
}

void stat()
{
    const char *binaryFile = "Commandes.bin";         // Your binary file
    const char *dataFile = "daily_totals.dat";        // Output data file for gnuplot
    const char *scriptFile = "C:\\Users\\Pc\\Desktop\\newcproject\\RESTAU\\menu\\plot_daily_totals.gp";  // Existing gnuplot script file
    const char *outputImageFile = "daily_totals.png"; // Output image file

    // Generate the data file for gnuplot from the binary file
    generateDataFileFromBinary(binaryFile, dataFile);

    // Check if the data file was created
    FILE *testDataFile = fopen(dataFile, "r");
    if (!testDataFile)
    {  
        c_gotoxy(40, 16);
        c_textcolor(4);
        printf("Failed to generate data file '%s'. Exiting.\n", dataFile);
        exit(1);
    }
    fclose(testDataFile);

    // Run the existing gnuplot script
    runGnuplot(scriptFile);

    // Verify if the PNG image was generated
    FILE *testImageFile = fopen(outputImageFile, "r");
    if (testImageFile)
    {   
        c_gotoxy(40, 20);
        c_textcolor(10);
        printf("Graph image '%s' generated successfully!\n", outputImageFile);
        fclose(testImageFile);
    }
    else
    {
        c_gotoxy(40, 20);
        c_textcolor(4);
        printf("Failed to generate graph image '%s'. Please check gnuplot setup.\n", outputImageFile);
    }
}

#endif
