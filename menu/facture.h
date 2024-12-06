#ifndef facture_h
#define facture_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "commande.h"
char pdf_header[] = 
    "%%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 330 >>\n"
    "stream\n"
    "BT\n"
    "/F1 12 Tf\n"
    "72 750 Td\n";

char pdf_footer[] = 
    "ET\n"
    "endstream\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
    "endobj\n"
    "xref\n"
    "0 6\n"
    "0000000000 65535 f\n"
    "0000000010 00000 n\n"
    "0000000079 00000 n\n"
    "0000000178 00000 n\n"
    "0000000307 00000 n\n"
    "0000000403 00000 n\n"
    "trailer\n"
    "<< /Root 1 0 R /Size 6 >>\n"
    "startxref\n"
    "482\n"
    "%%EOF\n";

void creerFacture(int commande_id) {
    char s[]="commandes.bin";
    FILE *file = fopen(s, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n",s );
        return;
    }

    Command commande;
    int found = 0;

    // Search for the command by ID
    while (fread(&commande, sizeof(Command), 1, file)) {
        if (commande.id == commande_id) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Error: Command with ID %d not found in %s\n", commande_id, s);
        return;
    }

    // Open the PDF file for writing
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Error: Unable to create FACTEUR.pdf file!\n");
        return;
    }

    // Write the PDF header
    fprintf(FACT, pdf_header);

    // Add command details to the PDF
    fprintf(FACT, "(================== FACTURE ==================) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Command ID: %d ) Tj\n0 -20 Td\n", commande.id);
    fprintf(FACT, "(Type: %s ) Tj\n0 -20 Td\n", commande.order_type);

    // Get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(FACT, "(Date: %02d-%02d-%d ) Tj\n0 -30 Td\n", 
            localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);

    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(| Product         | Quantity   | Unit Price | Total Price |) Tj\n0 -20 Td\n");
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");

    // Add each product in the command to the PDF
    for (int i = 0; i < commande.num_items; i++) {
        float total_price = commande.quantities[i] * commande.prices[i];
        fprintf(FACT, "(| %-15s | %-10d | %-10.2f DH | %-10.2f DH |) Tj\n0 -20 Td\n", 
                commande.dishes[i], commande.quantities[i], commande.prices[i], total_price);
    }

    // Write the grand total
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Grand Total: %.2f DH ) Tj\n0 -20 Td\n", commande.total_price);
    fprintf(FACT, "(=============================================) Tj\n");

    // Write the PDF footer and close the file
    fprintf(FACT, pdf_footer);
    fclose(FACT);

    printf("PDF Facture generated: FACTEUR.pdf\n");
}
#endif