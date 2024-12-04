#ifndef commande_h
#define commande_h
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

void clearBuffer() {
    while (getchar() != '\n');
}

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
            printf("Entrée invalide ! Veuillez entrer un entier : ");
            clearBuffer();
        }

        while (fread(&commande, sizeof(Commande), 1, fichier)) {
            if (commande.id == local_id) {
                id_exist = 1;
                printf("Erreur : l'ID %d existe déjà ! Veuillez entrer un autre ID.\n", local_id);
                break;
            }
        }
    } while (id_exist);

    commande.id = local_id;

    do {
        printf("Entrez le type de commande (in/out) : ");
        scanf("%s", commande.type_commande);
        clearBuffer();
        if (strcmp(commande.type_commande, "in") != 0 && strcmp(commande.type_commande, "out") != 0) {
            printf("Type invalide ! Veuillez entrer 'in' ou 'out'.\n");
        }
    } while (strcmp(commande.type_commande, "in") != 0 && strcmp(commande.type_commande, "out") != 0);

    printf("Entrez le nombre de plats dans la commande : ");
    while (scanf("%d", &commande.num_dom) != 1 || commande.num_dom <= 0 || commande.num_dom > 10) {
        printf("Entrée invalide ! Veuillez entrer un nombre entre 1 et 10 : ");
        clearBuffer();
    }

    commande.prix_total = 0;
    for (int i = 0; i < commande.num_dom; i++) {
        printf("Entrez le nom du plat %d : ", i + 1);
        clearBuffer();
        fgets(commande.plat[i], sizeof(commande.plat[i]), stdin);
        commande.plat[i][strcspn(commande.plat[i], "\n")] = '\0';

        printf("Entrez la quantité pour %s : ", commande.plat[i]);
        while (scanf("%d", &commande.quantite[i]) != 1 || commande.quantite[i] <= 0) {
            printf("Entrée invalide ! Veuillez entrer une quantité valide : ");
            clearBuffer();
        }

        printf("Entrez le prix unitaire pour %s : ", commande.plat[i]);
        while (scanf("%f", &commande.prix[i]) != 1 || commande.prix[i] <= 0) {
            printf("Entrée invalide ! Veuillez entrer un prix valide : ");
            clearBuffer();
        }

        commande.prix_total += commande.quantite[i] * commande.prix[i];
    }

    fwrite(&commande, sizeof(Commande), 1, fichier);
    fclose(fichier);
    printf("Commande ajoutée avec succès !\n");
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
        printf("Détails de la commande :\n");
        for (int i = 0; i < commande.num_dom; i++) {
            printf("- %d x %s à %.2f DH\n", commande.quantite[i], commande.plat[i], commande.prix[i]);
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
        clearBuffer();
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
        if (rename("temp.bin", nomFichier) != 0) {
            perror("Erreur lors du renommage du fichier temporaire");
        }
    } else {
        printf("Aucune commande avec ID %d n'a été trouvée.\n", id_supprimer);
        remove("temp.bin");
    }
}
#endif