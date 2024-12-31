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
#include "statistic.h"
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
        "STATICTIC",
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
        options.title = "= Al ATLAS USERS =";
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

        options.title = "== MANAGER WORKSPACE ==";
        options.ops = MANAGER;
        options.len = sizeof(MANAGER) / sizeof(MANAGER[0]);

        int option = select_menu(options);
        if (option == 0){
            emploi();
        }else if (option == 3){
            utilisation();
        }else if (option == 1){
            menu();
        }else if (option == 2){
            stat();
            c_clrscr();
            c_gotoxy(40,14);c_textcolor(10);
            printf("THE GRAPH GENERATED SUCSSESFULLY. :) >>");
            veuillez_patientez();
            c_clrscr();
            c_gotoxy(40,14);c_textcolor(6);
            printf("OPNING THE GRAPH >>...");
            veuillez_patientez();
            image("C:\\Users\\Pc\\Desktop\\newcproject\\RESTAU\\menu\\daily_totals.png");
            c_getch();
            gerant();
        }
        }
    void resp(){
        options.title = "== RECEPTIONIST WORKSPACE ==";
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
            c_getch();
            resp(); 
        }
    }
    void menu(){
        options.title = "== Restaurant Menu Management ==";
        options.ops = MENU;
        options.len = sizeof(MENU) / sizeof(MENU[0]);

        int option = select_menu(options);
         switch (option)
        {
        case 0:
            addDish();
            c_getch();
            menu();
            break;
        case 1:
            addDrink();
            c_getch();
            menu();
            break;
        case 2:
            displayMenu1();
            c_getch();
            menu();
            break;
        case 3:
            deleteDish();
            c_getch();
            menu();
            break;
        case 4:
            deleteDrink();
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
        options.title = "== GESTION DES COMMANDE ==";
        options.ops = COMMANDE;
        options.len = sizeof(COMMANDE) / sizeof(COMMANDE[0]);

        int option = select_menu(options);
           switch (option)
        {
        case 0:
            addCommande("Commandes.bin",dishFilePath,drinkFilePath);
            c_getch();
            commande();
            break;
        case 1:
            displayCommands("Commandes.bin");
            c_getch();
            commande();
            break;
        case 2:
            deleteCommand("Commandes.bin");
            c_getch();
            commande();
            break;
        case 3:
            resp();
            break;
             default:
            printf("\nInvalid choice! Please try again.\n");
        }
       
    }
    void reservation(){
        options.title = "== GESTION DES RESERVATIONS ==";
        options.ops = RESERV;
        options.len = sizeof(RESERV) / sizeof(RESERV[0]);

        int option = select_menu(options);
        load_reservations(FILE_PATH1);
        Reservation res;
           switch (option)
        {
        case 0:
            create_reservation(&res, FILE_PATH1);
            c_getch();
            reservation();
            break;
        case 1:
            display_reservations(FILE_PATH1);
            c_getch();
            reservation();
            break;
        case 2:
            int id;
            c_gotoxy(38,15);
            c_textcolor(6);
            printf("Enter the reservation ID to delete: ");
            drawEmptyBox(75, 14, 25);
            c_gotoxy(79,15);
            c_textcolor(15);
            scanf("%d", &id);
            getchar();
            delete_reservation(id, FILE_PATH1);
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
    c_gotoxy(40,14);
    c_textcolor(6);
    printf("Enter the Command ID to generate a facture: ");
    scanf("%d", &commande_id);
    creerFacture(commande_id);
    veuillez_patientez();
    c_gotoxy(40,18);
    c_textcolor(10);
    printf("PDF Facture generated: FACTEUR.pdf\n");
    c_gotoxy(40,19);
    printf("OPNING THE FACTURE ....");
    veuillez_patientez();
    const char *pdfPath = "C:\\Users\\Pc\\Desktop\\newcproject\\RESTAU\\menu\\FACTEUR.pdf"; 
    openPDFInEdge(pdfPath);

    }
    
    void emploi(){
        
        options.title = "== ESTION DES EMPLOYEES ==";
        options.ops = EMPLOYERS;
        options.len = sizeof(EMPLOYERS) / sizeof(EMPLOYERS[0]);

        int option = select_menu(options);
           switch (option)
        {
        case 0:
            addEmployee();
            c_getch();
            emploi();
            break;
        case 1:
            displayEmployees();
            c_getch();
            emploi();
            break;
        case 2:
            deleteEmployee();
            c_getch();
            emploi();
            break;
        case 3:
            updateEmployee();
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
        options.title = "== Welcome To AL ATLAS HOME ==";
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
            displayMenu2();
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
    chcp();
    utilisation();
}
    


