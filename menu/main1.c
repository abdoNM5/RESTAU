#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "identif.h"
#include <windows.h>
#include "home.h"
#include "dashboard.h"
#include "manager.h"

Options options;
    
    char *MAIN_OPTIONS[] = {
        "Client",
        "Receptionist",
        "Manager",
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
    "exit"
        };
    char *HOME[] = {
        "Info Restau",
        "Categories",
        "Produits",
        "exit"
    };

        void dashboard();
        void emploi();
        void utilisation();
        void gerant();
 
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
    
    void emploi() {
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
            printf("\n\nPress any key to prove...");
            c_getch();
            gerant();
            break;
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

            break;
        case 2:

            break;
        case 3:
            utilisation();
            break;
        default:

            break;
        }
    }
void main(){
    utilisation();
}
    


