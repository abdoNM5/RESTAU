#ifndef commandes
#define commandes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char type_commande[5];
    int num_dom;
    char plat[10][30];
    int quantite[10];
    float prix[10];
    float prix_total;
} Commande;

void ajouterCommande(const char *nomFichier) {
    Commande commande;
    FILE *fichier = fopen(nomFichier, "ab+");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int id_exist;
    int local_id;

 
    do {
        rewind(fichier); 
        id_exist = 0;

        printf("Entrez l'ID de la commande : ");
        while (scanf("%d", &local_id) != 1) {
            printf("Entree invalide ! Veuillez entrer un entier : ");
            while (getchar() != '\n'); 
        }

       
        while (fread(&commande, sizeof(Commande), 1, fichier)) {
            if (commande.id == local_id) {
                id_exist = 1;
                printf("Erreur : l'ID %d existe deja ! Veuillez entrer un autre ID.\n", local_id);
                break;
            }
        }
    } while (id_exist); 

    commande.id = local_id;

    printf("Entrez le type de commande (in/out) : ");
    scanf("%s", commande.type_commande);

    printf("Entrez le nombre de plats dans la commande : ");
    while (scanf("%d", &commande.num_dom) != 1 || commande.num_dom <= 0 || commande.num_dom > 10) {
        printf("Entree invalide ! Veuillez entrer un nombre entre 1 et 10 : ");
        while (getchar() != '\n'); 

    
    commande.prix_total = 0;
    for (int i = 0; i < commande.num_dom; i++) {
        printf("Entrez le nom du plat %d : ", i + 1);
        while (getchar() != '\n'); 
        fgets(commande.plat[i], sizeof(commande.plat[i]), stdin);
        commande.plat[i][strcspn(commande.plat[i], "\n")] = '\0'; 

        printf("Entrez la quantite pour %s : ", commande.plat[i]);
        while (scanf("%d", &commande.quantite[i]) != 1 || commande.quantite[i] <= 0) {
            printf("Entree invalide ! Veuillez entrer une quantite valide : ");
            while (getchar() != '\n');
        }

        printf("Entrez le prix unitaire pour %s : ", commande.plat[i]);
        while (scanf("%f", &commande.prix[i]) != 1 || commande.prix[i] <= 0) {
            printf("Entree invalide ! Veuillez entrer un prix valide : ");
            while (getchar() != '\n');
        }

        commande.prix_total += commande.quantite[i] * commande.prix[i];
    }

    fwrite(&commande, sizeof(Commande), 1, fichier);
    fclose(fichier);
    printf("Commande ajoutee avec succes !\n");
}
}

void afficherCommandes(const char *nomFichier) {
    Commande commande;
    FILE *fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    printf("\n=== Liste des commandes ===\n");
    while (fread(&commande, sizeof(Commande), 1, fichier)) {
        printf("ID : %d\n", commande.id);
        printf("Type de commande : %s\n", commande.type_commande);
        printf("Details de la commande :\n");
        for (int i = 0; i < commande.num_dom; i++) {
            printf("- %d x %s par %.2f DH\n", commande.quantite[i], commande.plat[i], commande.prix[i]);
        }
        printf("Prix total : %.2f DH\n", commande.prix_total);
        printf("--------------------------\n");
    }

    fclose(fichier);
}

void supprimerCommande(const char *nomFichier) {
    int id_supprimer;
    int commande_trouvee = 0;
    Commande commande;

    
    FILE *fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    FILE *tempFichier = fopen("temp.bin", "wb");
    if (tempFichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        fclose(fichier);
        return;
    }

    
    printf("Entrez l'ID de la commande à supprimer : ");
    while (scanf("%d", &id_supprimer) != 1) {
        printf("Entrée invalide ! Veuillez entrer un entier : ");
        while (getchar() != '\n'); 
    }

    
    while (fread(&commande, sizeof(Commande), 1, fichier)) {
        if (commande.id == id_supprimer) {
            commande_trouvee = 1;
            printf("Commande avec ID %d supprimée.\n", id_supprimer);
        } else {
            fwrite(&commande, sizeof(Commande), 1, tempFichier);
        }
    }

    fclose(fichier);
    fclose(tempFichier);

    if (commande_trouvee) {
        
        remove(nomFichier);
        rename("temp.bin", nomFichier);
    } else {
        printf("Aucune commande avec ID %d n'a été trouvée.\n", id_supprimer);
        remove("temp.bin"); 
    }
}


// int main() {
//     const char *nomFichier = "commandes.bin";
//     int choix;

//     do {
//         printf("\n=== Gestion des Commandes ===\n");
//         printf("1. Ajouter une commande\n");
//         printf("2. Afficher les commandes\n");
//         printf("3. Suprimer une commande\n");
//         printf("4. Quitter\n");
//         printf("Entrez votre choix : ");
//         scanf("%d", &choix);

//         switch (choix) {
//             case 1:
//                 ajouterCommande(nomFichier);
//                 break;
//             case 2:
//                 afficherCommandes(nomFichier);
//                 break;
//             case 3:
//                  supprimerCommande(nomFichier);
//                 break;
//             case 4:
//                 printf("Au revoir !\n");
//                 break;
//             default:
//                 printf("Choix invalide. Veuillez réessayer.\n");
//         }
//     } while (choix != 4);

//     return 0;
// }
#endif