#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "identif.h"
#include <windows.h>
#include "home.h"
#include "dashboard.h"
#include "employer.h"
#include "commande.h"
#include "facture.h"

Options options;


    
    char *MAIN_OPTIONS[] = {
        "Client",
        "Receptionist",
        "Manager",
        "exit"
    };
    char *RESEPS[] = {
        "Commande",
        "Reservation",
        "Facture",
        "exit"
    };
    char *COMMANDE[] = {
        "Add Commande",
        "Display Commandes",
        "Delete Commande",
        "exit"
    };
    char *MANAGER[] = {
        "EMPLOYEES",
        "STOKE",
        "RAPORT",
        "exit"
        };
    char *EMPLOYERS[] = {
        "Add Employee",
        "Display Employees",
        "Delete Employee",
        "Update Employee",
        "exit"
        };
    char *HOME[] = {
        "Info Restau",
        "Our Menu",
        "exit"
    };

        void dashboard();
        void emploi();
        void utilisation();
        void gerant();
        void resp();
        void commande();
        void reservation();
    void utilisation(){
        options.title = "=== DragonWorrier Restaurant USERS ===";
        options.ops = MAIN_OPTIONS;
        options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

        int option = select_menu(options);
            switch (option)
        {
        case 0:
            dashboard();
            break;
        case 1:
             login(2);
            system("cls");
            resp();
            break;
        case 2:
             login(1);
            system("cls");
            gerant();
            break;
        case 3:
            printf("Exiting program.\n");
            exit(1);
            break;
             default:
            printf("\nInvalid choice! Please try again.\n");
        }
    }
    void gerant(){   

        options.title = "=== MANAGER WORKSPACE ===";
        options.ops = MANAGER;
        options.len = sizeof(MANAGER) / sizeof(MANAGER[0]);

        int option = select_menu(options);
        if (option == 0){
            emploi();
        }else if (option == 3){
            utilisation();
        }
        }
void resp() {
    options.title = "=== RESEP WORKSPACE ===";
    options.ops = RESEPS;
    options.len = sizeof(RESEPS) / sizeof(RESEPS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0: 
            commande();
            break;
        case 1: 
            reservation();
            break;
        case 2: { 
            int id;
            printf("Entrez l'ID de la commande pour générer une facture : ");
            while (scanf("%d", &id) != 1) {
                printf("Entrée invalide ! Veuillez entrer un entier : ");
                clearBuffer();
            }
            creerFacture(id);
            printf("\nPress any key to return to RESEP workspace...");
            c_getch();
            resp();
            break;
        }
        case 3: 
            utilisation();
            break;
        default:
            printf("\nInvalid choice! Please try again.\n");
    }
}
    void commande(){
         options.title = "=== GESTION DES COMMANDE ===";
        options.ops = COMMANDE;
        options.len = sizeof(COMMANDE) / sizeof(COMMANDE[0]);

        int option = select_menu(options);
           switch (option)
        {
        case 0:
            ajouterCommande("Commandes.bin");
            printf("\nPress any key to prove...");
            c_getch();
            commande();
            break;
        case 1:
            afficherCommandes("Commandes.bin");
            printf("\n\nPress any key to prove...");
            c_getch();
            commande();
            break;
        case 2:
            supprimerCommande("Commandes.bin");
            printf("\n\nPress any key to prove...");
            c_getch();
            commande();
            break;
        case 3:
            printf("\n\nPress any key to prove...");
            c_getch();
            resp();
            break;
             default:
            printf("\nInvalid choice! Please try again.\n");
        }
       
    }
    void reservation(){
        
    }
    void emploi(){
        
        options.title = "=== GESTION DES EMPLOYEES ===";
        options.ops = EMPLOYERS;
        options.len = sizeof(EMPLOYERS) / sizeof(EMPLOYERS[0]);

        int option = select_menu(options);
           switch (option)
        {
        case 0:
            addEmployee();
            printf("\nPress any key to prove...");
            c_getch();
            emploi();
            break;
        case 1:
            displayEmployees();
            printf("\n\nPress any key to prove...");
            c_getch();
            emploi();
            break;
        case 2:
            deleteEmployee();
            printf("\n\nPress any key to prove...");
            c_getch();
            emploi();
            break;
        case 3:
            updateEmployee();
            printf("\n\nPress any key to prove...");
            c_getch();
            emploi();
            break;
        case 4:
            gerant();

             default:
            printf("\nInvalid choice! Please try again.\n");
        }
       }
    void dashboard(){
        options.title = "=== Welcome To DragonWorrier Restaurant HOME ===";
        options.ops = HOME;
        options.len = sizeof(HOME) / sizeof(HOME[0]);

        int option = select_menu(options);
        switch (option)
        {
        case 0:
            afficherInfosRestaurant();
            dashboard();
            break;
        case 1:
            displayMenuTable();
            dashboard(); 
            break;
        case 2:
            utilisation();
            break;
        default:

            break;
        }
    }
void main(){
    utilisation();
}
    


