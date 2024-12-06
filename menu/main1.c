#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"
#include "identif.h"
#include <windows.h>
#include "home.h"
#include "dashboard.h"
#include "employer.h"
#include "commande.h"
#include "reservation.h"
#include "facture.h"
#define FILE_PATH1 "reservations.bin"
Options options;

   
    char *MAIN_OPTIONS[] = {
        "Client",
        "Receptionist",
        "Manager",
        "exit"
    };
    char *RESEPS[] = {
        "COMMANDE",
        "RESERVATION",
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
        "GESTION MENU",
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
        "INFO RESTOU",
        "OUR MENU",
        "exit"
        };
    char *RESERV[] = {
        "Add Reservation",
        "Display Reservations",
        "Delete Reservation",
        "exit"
        };
    char *MENU[] = {
        "Add Dish",
        "Add Drink",
        "Display Menu",
        "Delete Dish",
        "Delete Drink",
        "exit"
        };

        void dashboard();
        void emploi();
        void utilisation();
        void gerant();
        void resp();
        void commande();
        void reservation();
        void facture();
        void menu();
 
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

        options.title = "==== MANAGER WORKSPACE ====";
        options.ops = MANAGER;
        options.len = sizeof(MANAGER) / sizeof(MANAGER[0]);

        int option = select_menu(options);
        if (option == 0){
            emploi();
        }else if (option == 4){
            utilisation();
        }else if (option == 1){
            menu();
        }
        }
    void resp(){
        options.title = "=== RESEP WORKSPACE ===";
        options.ops = RESEPS;
        options.len = sizeof(RESEPS) / sizeof(RESEPS[0]);

        int option = select_menu(options);
        if (option == 0){
            commande();
        }else if (option == 3){
            utilisation();
        }else if (option == 1){
            reservation();
        }else if (option == 2){
            facture();
        }
    }
    void menu(){
        options.title = "========== Restaurant Menu Management ==========";
        options.ops = MENU;
        options.len = sizeof(MENU) / sizeof(MENU[0]);

        int option = select_menu(options);
         switch (option)
        {
        case 0:
            addDish();
            printf("\n\nPress any key to prove...");
            c_getch();
            menu();
            break;
        case 1:
            addDrink();
            printf("\n\nPress any key to prove...");
            c_getch();
            menu();
            break;
        case 2:
            displayMenu();
            printf("\n\nPress any key to prove...");
            c_getch();
            menu();
            break;
        case 3:
            deleteDish();
            printf("\n\nPress any key to prove...");
            c_getch();
            menu();
            break;
        case 4:
            deleteDrink();
            printf("\nInvalid choice! Please try again.\n");
            c_getch();
            menu();
            break;
        case 5:
            gerant();
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
            addCommand("Commandes.bin");
            printf("\nPress any key to prove...");
            c_getch();
            commande();
            break;
        case 1:
            displayCommands("Commandes.bin");
            printf("\n\nPress any key to prove...");
            c_getch();
            commande();
            break;
        case 2:
            deleteCommand("Commandes.bin");
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
        options.title = "=== GESTION DES RESERVATIONS ===";
        options.ops = RESERV;
        options.len = sizeof(RESERV) / sizeof(RESERV[0]);

        int option = select_menu(options);
        load_reservations(FILE_PATH1);
        Reservation res;
           switch (option)
        {
        case 0:
            create_reservation(&res, FILE_PATH1);
            c_textcolor(6);
            printf("\nPress any key to prove...");
            c_getch();
            reservation();
            break;
        case 1:
            display_reservations(FILE_PATH1);
            c_textcolor(6);
            printf("\n\nPress any key to prove...");
            c_getch();
            reservation();
            break;
        case 2:
            int id;
            c_gotoxy(3,10);
            c_textcolor(6);
            printf("Enter the reservation ID to delete: ");
            c_textcolor(15);
            scanf("%d", &id);
            getchar();
            delete_reservation(id, FILE_PATH1);
            printf("\n\n\nPress any key to prove...");
            c_getch();
            reservation();
            break;
        case 3:
            resp();
            break;
             default:
            printf("\nInvalid choice! Please try again.\n");
        }
       
    }
    void facture(){
        
    int commande_id;

    printf("Enter the Command ID to generate a facture: ");
    scanf("%d", &commande_id);
    c_clrscr();
    creerFacture(commande_id);
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
            displayMenu();
            printf("\n\nPress any key to prove...");
            c_getch();
            dashboard(); 
            break;
        case 2:
            utilisation();
            break;
        default:
            printf("\nInvalid choice! Please try again.\n");
            break;
        }
    }
void main(){
    utilisation();
}
    


