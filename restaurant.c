#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//----------------------------------------------------------------------------------------------------
#define MAX_TABLES 10
//-----------------------------------------------------------------------------------------------------
typedef struct {
    int numTable;
    char nom[50];
    int nbPersonnes;
    char typePates[50];
    char typeSauce[50];
    double prixTotal;
} Client;
//-------------------------------------------------------------------------------------------------------
typedef struct {
    int numTable;
    int client_numTable;
} Table;
typedef struct {
    char nom[50];
    double prix;
} Pates;
typedef struct {
    char nom[50];
    double prix;
} Sauce;
//--------------------------------------------------------------------------------------------------------
Client* ajouterClient(Client *clients, int *nbClients, int *tailleMax, const char *nom, int nbPersonnes) {
   if (*nbClients >= *tailleMax) {
       *tailleMax *= 2;
        clients = realloc(clients, *tailleMax * sizeof(Client));
        if (!clients) {
            perror("Erreur de reallocation memoire");
            exit(EXIT_FAILURE);
        }
    }
    clients[*nbClients].numTable = *nbClients;
    strcpy(clients[*nbClients].nom, nom);
    clients[*nbClients].nbPersonnes = nbPersonnes;
    strcpy(clients[*nbClients].typePates, "");
    strcpy(clients[*nbClients].typeSauce, "");
    clients[*nbClients].prixTotal = 0.0;
    (*nbClients)++;
    return clients;
}
//-----------------------------------------------------------------------------------------------------
void initialiserTables(Table *tables, int nbTables) {
    for (int i = 0; i < nbTables; i++) {
        tables[i].numTable = i;
        tables[i].client_numTable = -1; 
    }
}
//------------------------------------------------------------------------------------------------------
void choisirMenu(Client *client) {
    Pates patesOptions[4] = {
        {"Spaghetti", 300.0},
        {"Penne", 250.0},
        {"Fusilli", 270.0},
        {"Macaroni", 280.0}
    };
    Sauce sauceOptions[4] = {
        {"Tomate", 100.0},
        {"Pesto", 150.0},
        {"Alfredo", 200.0},
        {"Carbonara", 220.0}
    };
    int choixPates, choixSauce;
    printf("---------------------Choix des pates-----------------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s (%.2f DZD)\n", i+1, patesOptions[i].nom, patesOptions[i].prix);
    }
    printf("Choisissez le type de pates: ");
    scanf("%d", &choixPates);
    if (choixPates < 1 || choixPates > 4) {
        printf("Choix invalide. Veuillez reessayer.\n");
        return;
    }
    printf("---------------------Choix des sauces----------------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s (%.2f DZD)\n", i+1, sauceOptions[i].nom, sauceOptions[i].prix);
    }
    printf("Choisissez le type de sauce: ");
    scanf("%d", &choixSauce);
    if (choixSauce < 1 || choixSauce > 4) {
        printf("Choix invalide. Veuillez reessayer.\n");
        return;
    }
    strcpy(client->typePates, patesOptions[choixPates-1].nom);
    strcpy(client->typeSauce, sauceOptions[choixSauce-1].nom);
    client->prixTotal = patesOptions[choixPates-1].prix + sauceOptions[choixSauce-1].prix;
    printf("----------------------------------------------\n");
    printf(" --> Vous avez choisi %s avec %s.\n", client->typePates, client->typeSauce);
    printf("----------------------------------------------\n");
}
//----------------------------------------------------------------------------------------------------------
void reserverTable(Table *tables, int nbTables, Client *clients, int *nbClients, int *tailleMaxClients) {
    char nom[50];
    int nbPersonnes;
    system("cls");
    printf("---------------------Restaurant La Fourchette--------------------\n");
    printf("--------------------------------------------\n");
    printf(" --> Reservation:\n");
    printf("---------------------------------------------\n");
    printf("-Entrer le nom du client: ");
    scanf("%s", nom);
    printf("-Entrer le nombre de personnes: ");
    scanf("%d", &nbPersonnes);
    clients = ajouterClient(clients, nbClients, tailleMaxClients, nom, nbPersonnes);
    for (int i = 1; i < nbTables; i++) {
        if (tables[i].client_numTable == -1) {
            tables[i].client_numTable = clients[*nbClients - 1].numTable;
            printf("---------------------------------------------\n");
            printf("| Table | Client                           |\n");
            printf("---------------------------------------------\n");
            printf("| %-5d | %-32s |\n", tables[i].numTable, nom);
            printf("---------------------------------------------\n");
            choisirMenu(&clients[*nbClients - 1]);
            return;
        }
    }
    printf("-Aucune table disponible pour le client %s.\n", nom);
}
//-----------------------------------------------------------------------------------------------
void annulerReservation(Table *tables, int nbTables, Client *clients, int nbClients) {
    char nom[50];
    system("cls");
    printf("---------------------Restaurant La Fourchette--------------------\n");
    printf("--------------------------------------------\n");
    printf(" --> Annulation de la reservation:\n");
    printf("---------------------------------------------\n");
    printf("-Entrer le nom du client pour annuler la reservation: ");
    scanf("%s", nom);
    for (int i = 0; i < nbClients; i++) {
        if (strcmp(clients[i].nom, nom) == 0) {
            for (int j = 0; j < nbTables; j++) {
                if (tables[j].client_numTable == clients[i].numTable) {
                    tables[j].client_numTable = -1;
                    printf("\n-Reservation de la table %d au nom de %s: annulee.\n", tables[j].numTable, nom);
                    return;
                }
            }
        }
    }
    printf("-Aucune reservation au nom de %s trouvee.\n", nom);
}
//-----------------------------------------------------------------------------------------------
void VerifDispoTables(Table *tables, Client *clients, int nbTables) {
    system("cls");
    printf("---------------------Restaurant La Fourchette--------------------\n");
    printf("--------------------------------------------\n");
    printf(" --> Verification des tables disponibles:\n");
    printf("---------------------------------------------\n");
    printf("| Table | Disponibilite                     |\n");
    printf("---------------------------------------------\n");
    for (int i = 1; i < nbTables; i++) {
        if (tables[i].client_numTable == -1) {
            printf("| %-5d | Libre                              |\n", tables[i].numTable);
        } else {
            printf("| %-5d | Reservee par %-20s |\n", tables[i].numTable, clients[tables[i].client_numTable].nom);
        }
    }
    printf("---------------------------------------------\n");
}
//-----------------------------------------------------------------------------------------------
void afficherFacture(Client *clients, int nbClients) {
    char nom[50];
    system("cls");
    printf("---------------------Restaurant La Fourchette--------------------\n");
    printf("--------------------------------------------\n");
    printf(" --> Afficher Facture:\n");
    printf("---------------------------------------------\n");
    printf("-Entrer le nom du client pour afficher la facture: ");
    scanf("%s", nom);
    for (int i = 0; i < nbClients; i++) {
        if (strcmp(clients[i].nom, nom) == 0) {
            printf("------------------------------------------------------------------------\n");
            printf("| %-15s | %-10s | %-10s | %-10s | %-10s |\n", "Client", "Pates", "Sauce", "Prix Pates", "Prix Sauce");
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-15s | %-10s | %-10s | %-10.2f | %-10.2f |\n", clients[i].nom, clients[i].typePates, clients[i].typeSauce, clients[i].prixTotal - 200, 200.0);
            printf("------------------------------------------------------------------------\n");
            printf("| %-54s | %-10.2f |\n", "Total TTC:", clients[i].prixTotal);
            printf("------------------------------------------------------------------------\n");
            return;
        }
    }
    printf("-Aucune reservation trouvee pour le client %s.\n", nom);
}
//----------------------------------------------------------------------------------------

void attendreEntree() {
    printf("\nAppuyez sur Entree pour continuer...");
    getchar(); 
    getchar(); 
}
//-----------------------------------------------------------------------------------------

int main() {
    int nbClients = 0;
    int tailleMaxClients = 10;
    int nbTables = 10;
    Client *clients = malloc(tailleMaxClients * sizeof(Client));
    Table tables[MAX_TABLES];
    if (!clients) {
        perror("Erreur d'allocation memoire");
        return EXIT_FAILURE;
    }
    // Initialiser les tables
    initialiserTables(tables, nbTables);
    int choix;
    do {
        system("cls");
        printf("---------------------Restaurant La Fourchette--------------------\n");
        printf("-----------------------------------------------------------------\n");
        printf("1. Reserver une table\n");
        printf("2. Annuler une reservation\n");
        printf("3. Verifier la disponibilite des tables\n");
        printf("4. Afficher Facture\n");
        printf("5. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                reserverTable(tables, nbTables, clients, &nbClients, &tailleMaxClients);
                attendreEntree();
                break;
            case 2:
                annulerReservation(tables, nbTables, clients, nbClients);
                attendreEntree();
                break;
            case 3:
                VerifDispoTables(tables, clients, nbTables);
                attendreEntree();
                break;
            case 4:
                afficherFacture(clients, nbClients);
                attendreEntree();
                break;
            case 5:
                printf("Bonne journee.\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
                attendreEntree();
                break;
        }
    } while (choix != 5);
    free(clients);
    return 0;
}