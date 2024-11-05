#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;
typedef struct {
    int id;                // Identifiant unique de l'employé
    char name[50];         // Nom de l'employé
    float salary;          // Salaire de l'employé
    char position[50];     // Poste de l'employé
} Employee;
// Structure représentant un aliment
typedef struct {
    char name[50];     // Nom de l'aliment
    float price;       // Prix de l'aliment
} Food;

// Structure représentant une table
typedef struct {
    int id;            // Identifiant unique de la table
    int capacity;      // Capacité d'accueil de la table
    int isOccupied;    // État de la table (1 si occupée, 0 si libre)
} Table;
User users[2] = {
    {"manager", "admin123"},   // Manager credentials
    {"reception", "admin123"} // Receptionist credentials
};
// Structure représentant une réservation
typedef struct {
    char customerName[50]; // Nom du client
    int tableId;           // Identifiant de la table réservée
    Food order[10];        // Commande des aliments
    int orderCount;        // Nombre d'aliments commandés
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
// Fonction pour ajouter un employé à la liste
void addEmployee(Employee **employees, int *count) {
    *employees = (Employee *)realloc(*employees, (*count + 1) * sizeof(Employee));
    if (*employees == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    printf("Entrez l'ID de l'employé: ");
    scanf("%d", &(*employees)[*count].id);
    printf("Entrez le nom de l'employé: ");
    scanf("%s", (*employees)[*count].name);
    printf("Entrez le salaire de l'employé: ");
    scanf("%f", &(*employees)[*count].salary);
    printf("Entrez le poste de l'employé: ");
    scanf("%s", (*employees)[*count].position);  // Nouvelle entrée pour le poste

    (*count)++;
    printf("Employé ajouté avec succès !\n");
}
void deleteEmployee(Employee **employees, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if ((*employees)[i].id == id) {
            // Déplacer les éléments suivants vers la gauche
            for (int j = i; j < *count - 1; j++) {
                (*employees)[j] = (*employees)[j + 1];
            }
            (*employees) = (Employee *)realloc(*employees, (*count - 1) * sizeof(Employee));
            if (*employees == NULL && *count - 1 > 0) {
                printf("Erreur d'allocation mémoire\n");
                exit(1);
            }
            (*count)--;
            printf("Employé supprimé avec succès !\n");
            return;
        }
    }
    printf("Aucun employé trouvé avec l'ID %d.\n", id);
}
// Fonction pour afficher tous les employés
void displayEmployees(Employee *employees, int count) {
    if (count == 0) {
        printf("Aucun employé à afficher.\n");
        return;
    }
    printf("--- Liste des employés ---\n");
    for (int i = 0; i < count; i++) {
        displayEmployee(employees[i]);
    }
}
void searchEmployee(Employee *employees, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("ID: %d, Nom: %s, Salaire: %.2f, Poste: %s\n", employees[i].id, employees[i].name, employees[i].salary, employees[i].position);
            return; // L'employé a été trouvé, sortie de la fonction
        }
    }
    printf("Aucun employé trouvé avec l'ID %d.\n", id); // Aucun employé trouvé
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

// Fonction pour créer une réservation
void createReservation(Table tables[], int tableCount) {
    Reservation reservation;
    printf("Entrez le nom du client: ");
    scanf("%s", reservation.customerName);

    // Choisir une table
    printf("Choisissez une table (ID entre 1 et %d): ", tableCount);
    scanf("%d", &reservation.tableId);

    // Vérifier si la table est libre
    if (tables[reservation.tableId - 1].isOccupied) {
        printf("Désolé, cette table est déjà occupée.\n");
        return;
    }

    // Marquer la table comme occupée
    tables[reservation.tableId - 1].isOccupied = 1;

    // Ajouter des aliments à la commande
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
// Fonction pour obtenir le nombre d'employés
int getEmployeeCount(int employeeCount) {
    return employeeCount; // Retourne simplement le compteur actuel
}

// Functions to display sub-menu for each category
void setTextColor(short color) {
    if (color >= 0 && color < 8) {
        printf("\033[1;%dm", 30 + color); // Couleurs de 30 à 37
    }
}
void setCursorPosition(int x, int y) {
    printf("\033[%d;%df", y, x); // Déplace le curseur à la position (y, x)
}

void resetColor() {
    printf("\033[0m"); // Réinitialiser les couleurs par défaut
}
void displayBoissons() {
    setTextColor(4);
    printf("\n--- Boissons ---\n");
    resetColor(); // Reset color after the title

    setTextColor(2); // Set color for the drinks
    // Do not move the cursor to (0, 0) after printing the title
    printf("1. Café - Ingrédients: Eau, Café moulu\n");
    printf("2. Thé - Ingrédients: Eau, Thé vert\n");
    printf("3. Eau minérale - \n");
    printf("4. Retour au menu principal\n");
    printf("5. Jus d'orange - \n");
    printf("6. Jus de carotte - \n");
    printf("7. Jus de citron - \n");
    printf("8. Jus de banane - \n");
    printf("9. Jus panaché - \n");

    resetColor(); // Reset color at the end
}

void displayPetitDejeuner() {
     setTextColor(4);
    printf("\n--- Petit Déjeuner ---\n");
    resetColor();
    setTextColor(2);
    printf("1.\n--- Ftour Beldi ---\n");
    printf("Ingrédients: Msemen, Beghrir, Zitoune (olives), Fromage, Thé à la menthe\n");
    printf("2.\n--- Ftour Chamali ---\n");
    printf("Ingrédients: Krachel, Batbout, Amlou, Oeufs au cumin, Zaatar, Thé au thym\n");
   printf("3.\n--- Ftour Bidawi ---\n");
    printf("Ingrédients: Harcha, Meloui, Beurre, Miel, Jben (fromage frais), Thé à la menthe\n");
     printf("4.\n--- Ftour Fessi ---\n");
    printf("Ingrédients: Khlii (viande séchée), Oeufs, Msemen, Zitoune, Pain de semoule, Thé à la menthe\n");
    printf("5.\n--- Ftour Espagnol ---\n");
    printf("Ingrédients: Tortilla espagnole, Churros, Pain à la tomate, Café au lait\n");
    printf("6.\n--- Ftour Hollandais ---\n");
    printf("Ingrédients: Pannenkoeken (crêpes hollandaises), Fromage gouda, Jus d'orange, Café\n");
    printf("7.\n--- Ftour Merrakchi ---\n");
    printf("Ingrédients: Bissara (purée de fèves), Khobz marqa (pain traditionnel), Rghaif, Zitoune, Thé à la menthe\n");
     printf("8.\n--- Ftour Norvegien ---\n");
    printf("Ingrédients: Saumon fumé, Oeufs brouillés, Pain complet, Fromage à la crème, Jus d'orange\n");
    printf("9.\n--- Ftour Sportif ---\n");
    printf("Ingrédients: Flocons d'avoine, Banane, Yaourt grec, Amandes, Jus de fruits\n");
    printf("10.\n--- Ftour Express ---\n");
    printf("Ingrédients: Croissant, Jus d'orange, Café\n");
}

void displayDejeuner() {
     setTextColor(4);
      printf("\n--- Menu Déjeuner ---\n");
      resetColor();
    setTextColor(2);
        printf("1.\n--- Couscous Royal ---\n");
        printf("Ingrédients: Semoule, Viande d'agneau, Légumes (carottes, courgettes, pois chiches), Ras el hanout\n");
        printf("2.\n--- Tajine de Poulet aux Citrons Confits et Olives ---\n");
        printf("Ingrédients: Poulet, Citrons confits, Olives vertes, Safran, Gingembre\n");
        printf("3.\n--- Pastilla au Poulet ---\n");
        printf("Ingrédients: Feuilles de brick, Poulet, Amandes, Cannelle, Sucre glace\n");
        printf("4.\n--- Brochettes de Viande ---\n");
        printf("Ingrédients: Boeuf ou agneau, Épices marocaines, Ail, Persil\n");
        printf("5.\n--- Salade Marocaine ---\n");
        printf("Ingrédients: Tomates, Concombres, Poivrons, Oignons, Coriandre\n");
        printf("6. Retour au menu principal\n");
}

void displayDiner() {
     setTextColor(4);
      printf("\n--- Menu Dîner ---\n");
      resetColor();
    setTextColor(2);
        printf("1.\n--- Harira ---\n");
        printf("Ingrédients: Tomates, Lentilles, Pois chiches, Viande d'agneau, Céleri, Coriandre\n");
        printf("2.\n--- Tajine de Kefta aux Oeufs ---\n");
        printf("Ingrédients: Viande hachée, Sauce tomate, Oeufs, Épices marocaines, Persil\n");
        printf("3.\n--- Méchoui ---\n");
        printf("Ingrédients: Agneau rôti, Beurre, Cumin, Sel\n");
        printf("4.\n--- Poisson Chermoula ---\n");
        printf("Ingrédients: Poisson (daurade ou sardine), Coriandre, Persil, Ail, Paprika, Cumin\n");
        printf("5.\n--- Briouates ---\n");
        printf("Ingrédients: Feuilles de brick, Farce (poulet ou légumes), Fromage, Cannelle\n");
        printf("6. Retour au menu principal\n");
}

