#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME_LEN 50  // Define a maximum length for username
#define PASSWORD_LEN 50  // Define a maximum length for password

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;
typedef struct {
    int id;                // Identifiant unique de l'employ
    char name[50];         // Nom de l'employ�
    float salary;          // Salaire de l'employ�
    char position[50];     // Poste de l'employ�
} Employee;
// Structure repr�sentant un aliment
typedef struct {
    char name[50];     // Nom de l'aliment
    float price;       // Prix de l'aliment
} Food;

// Structure repr�sentant une table
typedef struct {
    int id;            // Identifiant unique de la table
    int capacity;      // Capacit� d'accueil de la table
    int isOccupied;    // �tat de la table (1 si occup�e, 0 si libre)
} Table;
User users[2] = {
    {"manager", "admin123"},   // Manager credentials
    {"reception", "admin123"} // Receptionist credentials
};
// Structure repr�sentant une r�servation
typedef struct {
    char customerName[50]; // Nom du client
    int tableId;           // Identifiant de la table r�serv�e
    Food order[10];        // Commande des aliments
    int orderCount;        // Nombre d'aliments command�s
} Reservation;

// Function to authenticate user
int authenticate(char *username, char *password) {
    int usernameValid = 0; // Flag for username validation
    int passwordValid = 0; // Flag for password validation

    for (int i = 0; i < 2; i++) {
        if (strcmp(users[i].username, username) == 0) {
            usernameValid = 1; // Username is valid
        }
        if (strcmp(users[i].password, password) == 0) {
            passwordValid = 1; // Password is valid
        }
    }

    // Return 1 if either the username or password is valid
    return usernameValid || passwordValid;
}

void displayEmployee(Employee emp) {
    printf("ID: %d, Nom: %s, Salaire: %.2f, Poste: %s\n", emp.id, emp.name, emp.salary, emp.position);
}
// Fonction pour ajouter un employ� � la liste
void addEmployee(Employee **employees, int *count) {
    *employees = (Employee *)realloc(*employees, (*count + 1) * sizeof(Employee));
    if (*employees == NULL) {
        printf("Erreur d'allocation m�moire\n");
        exit(1);
    }

    printf("Entrez l'ID de l'employ�: ");
    scanf("%d", &(*employees)[*count].id);
    printf("Entrez le nom de l'employ�: ");
    scanf("%s", (*employees)[*count].name);
    printf("Entrez le salaire de l'employ�: ");
    scanf("%f", &(*employees)[*count].salary);
    printf("Entrez le poste de l'employ�: ");
    scanf("%s", (*employees)[*count].position);  // Nouvelle entre pour le poste

    (*count)++;
    printf("Employ� ajout� avec succ�s !\n");
}
void deleteEmployee(Employee **employees, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if ((*employees)[i].id == id) {
            // D�placer les �l�ments suivants vers la gauche
            for (int j = i; j < *count - 1; j++) {
                (*employees)[j] = (*employees)[j + 1];
            }
            (*employees) = (Employee *)realloc(*employees, (*count - 1) * sizeof(Employee));
            if (*employees == NULL && *count - 1 > 0) {
                printf("Erreur d'allocation m�moire\n");
                exit(1);
            }
            (*count)--;
            printf("Employ� supprim� avec succ�s !\n");
            return;
        }
    }
    printf("Aucun employ� trouv� avec l'ID %d.\n", id);
}
// Fonction pour afficher tous les employ�s
void displayEmployees(Employee *employees, int count) {
    if (count == 0) {
        printf("Aucun employ� � afficher.\n");
        return;
    }
    printf("--- Liste des employ�s ---\n");
    for (int i = 0; i < count; i++) {
        displayEmployee(employees[i]);
    }
}
void searchEmployee(Employee *employees, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("ID: %d, Nom: %s, Salaire: %.2f, Poste: %s\n", employees[i].id, employees[i].name, employees[i].salary, employees[i].position);
            return; // L'employ� a �t� trouv�, sortie de la fonction
        }
    }
    printf("Aucun employ� trouv� avec l'ID %d.\n", id); // Aucun employ� trouv�
}

// Fonction pour afficher la facture
void displayInvoice(Reservation reservation) {
    printf("\n--- Facture pour %s ---\n", reservation.customerName);
    printf("Table ID: %d\n", reservation.tableId);
    float total = 0;
    for (int i = 0; i < reservation.orderCount; i++) {
        printf("%s - %.2f\n", reservation.order[i].name, reservation.order[i].price);
        total += reservation.order[i].price;
    }
    printf("Total: %.2f\n", total);
}

// Fonction pour cr�er une r�servation
void createReservation(Table tables[], int tableCount) {
    Reservation reservation;
    printf("Entrez le nom du client: ");
    scanf("%s", reservation.customerName);

    // Choisir une table
    printf("Choisissez une table (ID entre 1 et %d): ", tableCount);
    scanf("%d", &reservation.tableId);

    // V�rifier si la table est libre
    if (tables[reservation.tableId - 1].isOccupied) {
        printf("D�sol�, cette table est d�j� occup�e.\n");
        return;
    }

    // Marquer la table comme occup�e
    tables[reservation.tableId - 1].isOccupied = 1;

    // Ajouter des aliments � la commande
    reservation.orderCount = 0;
    char choice;
    do {
        printf("Entrez le nom de l'aliment: ");
        scanf("%s", reservation.order[reservation.orderCount].name);
        printf("Entrez le prix de l'aliment: ");
        scanf("%f", &reservation.order[reservation.orderCount].price);
        reservation.orderCount++;

        printf("Voulez-vous ajouter un autre aliment? (o/n): ");
        scanf(" %c", &choice); // L'espace avant %c est pour ignorer les espaces
    } while (choice == 'o' && reservation.orderCount < 10);

    // Afficher la facture
    displayInvoice(reservation);
}(reservation);
// Fonction pour obtenir le nombre d'employ�s
int getEmployeeCount(int employeeCount) {
    return employeeCount; // Retourne simplement le compteur actuel
}

// Functions to display sub-menu for each category
void setTextColor(short color) {
    if (color >= 0 && color < 8) {
        printf("\033[1;%dm", 30 + color); // Couleurs de 30 � 37
    }
}
void setCursorPosition(int x, int y) {
    printf("\033[%d;%df", y, x); // D�place le curseur � la position (y, x)
}

void resetColor() {
    printf("\033[0m"); // R�initialiser les couleurs par d�faut
}
void displayBoissons() {
    setTextColor(4);
    printf("\n--- Boissons ---\n");
    resetColor(); // Reset color after the title

    setTextColor(2); // Set color for the drinks
    // Do not move the cursor to (0, 0) after printing the title
    printf("1. Caf� - Ingr�dients: Eau, Caf� moulu\n");
    printf("2. Th� - Ingr�dients: Eau, Th� vert\n");
    printf("3. Eau min�rale - \n");
    printf("4. Retour au menu principal\n");
    printf("5. Jus d'orange - \n");
    printf("6. Jus de carotte - \n");
    printf("7. Jus de citron - \n");
    printf("8. Jus de banane - \n");
    printf("9. Jus panach� - \n");

    resetColor(); // Reset color at the end
}

void displayPetitDejeuner() {
     setTextColor(4);
    printf("\n--- Petit D�jeuner ---\n");
    resetColor();
    setTextColor(2);
    printf("1.\n--- Ftour Beldi ---\n");
    printf("Ingr�dients: Msemen, Beghrir, Zitoune (olives), Fromage, Th� � la menthe\n");
    printf("2.\n--- Ftour Chamali ---\n");
    printf("Ingr�dients: Krachel, Batbout, Amlou, Oeufs au cumin, Zaatar, Th� au thym\n");
   printf("3.\n--- Ftour Bidawi ---\n");
    printf("Ingr�dients: Harcha, Meloui, Beurre, Miel, Jben (fromage frais), Th� � la menthe\n");
     printf("4.\n--- Ftour Fessi ---\n");
    printf("Ingr�dients: Khlii (viande s�ch�e), Oeufs, Msemen, Zitoune, Pain de semoule, Th� � la menthe\n");
    printf("5.\n--- Ftour Espagnol ---\n");
    printf("Ingr�dients: Tortilla espagnole, Churros, Pain � la tomate, Caf� au lait\n");
    printf("6.\n--- Ftour Hollandais ---\n");
    printf("Ingr�dients: Pannenkoeken (cr�pes hollandaises), Fromage gouda, Jus d'orange, Caf�\n");
    printf("7.\n--- Ftour Merrakchi ---\n");
    printf("Ingr�dients: Bissara (pur�e de f�ves), Khobz marqa (pain traditionnel), Rghaif, Zitoune, Th� � la menthe\n");
     printf("8.\n--- Ftour Norvegien ---\n");
    printf("Ingr�dients: Saumon fum�, Oeufs brouill�s, Pain complet, Fromage � la cr�me, Jus d'orange\n");
    printf("9.\n--- Ftour Sportif ---\n");
    printf("Ingr�dients: Flocons d'avoine, Banane, Yaourt grec, Amandes, Jus de fruits\n");
    printf("10.\n--- Ftour Express ---\n");
    printf("Ingr�dients: Croissant, Jus d'orange, Caf�\n");
}

void displayDejeuner() {
     setTextColor(4);
      printf("\n--- Menu D�jeuner ---\n");
      resetColor();
    setTextColor(2);
        printf("1.\n--- Couscous Royal ---\n");
        printf("Ingr�dients: Semoule, Viande d'agneau, L�gumes (carottes, courgettes, pois chiches), Ras el hanout\n");
        printf("2.\n--- Tajine de Poulet aux Citrons Confits et Olives ---\n");
        printf("Ingr�dients: Poulet, Citrons confits, Olives vertes, Safran, Gingembre\n");
        printf("3.\n--- Pastilla au Poulet ---\n");
        printf("Ingr�dients: Feuilles de brick, Poulet, Amandes, Cannelle, Sucre glace\n");
        printf("4.\n--- Brochettes de Viande ---\n");
        printf("Ingr�dients: Boeuf ou agneau, �pices marocaines, Ail, Persil\n");
        printf("5.\n--- Salade Marocaine ---\n");
        printf("Ingr�dients: Tomates, Concombres, Poivrons, Oignons, Coriandre\n");
        printf("6. Retour au menu principal\n");
}

void displayDiner() {
     setTextColor(4);
      printf("\n--- Menu D�ner ---\n");
      resetColor();
    setTextColor(2);
        printf("1.\n--- Harira ---\n");
        printf("Ingr�dients: Tomates, Lentilles, Pois chiches, Viande d'agneau, C�leri, Coriandre\n");
        printf("2.\n--- Tajine de Kefta aux Oeufs ---\n");
        printf("Ingr�dients: Viande hach�e, Sauce tomate, Oeufs, �pices marocaines, Persil\n");
        printf("3.\n--- M�choui ---\n");
        printf("Ingr�dients: Agneau r�ti, Beurre, Cumin, Sel\n");
        printf("4.\n--- Poisson Chermoula ---\n");
        printf("Ingr�dients: Poisson (daurade ou sardine), Coriandre, Persil, Ail, Paprika, Cumin\n");
        printf("5.\n--- Briouates ---\n");
        printf("Ingr�dients: Feuilles de brick, Farce (poulet ou l�gumes), Fromage, Cannelle\n");
        printf("6. Retour au menu principal\n");
}

