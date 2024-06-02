/*nom: youb nader
instagram: unnamed0._
class: 1y
programme: gestionnaire de transaction*/
//this version is in french
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
//------------------------------------------------------------------------
#define MAX_CLIENTS 100
#define MAX_TRANSACTIONS 100
//-----------------------------------------------------------------------
typedef struct {
    char TypeTransaction[50];
    float Montant;
    float SoldeApresTransaction;
} Transaction;
//------------------------------------------------------------------------
typedef struct {
    char nom[50];
    char prenom[50];
    char ID[50];
    char MDPS[50];
    float solde;
    int NumCompte;
    Transaction Transactions[MAX_TRANSACTIONS];
    int NbTransactions;
} Client;
//-------------------------------------------------------------------------------------------------
typedef Client TClient[MAX_CLIENTS];
//-------------------------------------------------------------------------------------------------
char* ReadPassword() {
    char Key;
    char* Password = malloc(50 * sizeof(char)); // Allocate memory for password
    if (Password == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    Password[0] = '\0'; // Initialize password as an empty string
    do {
        Key = getch(); // Read a key without echoing it to the console
        if (Key != '\r' && Key != '\b') { // If the key is not Enter or Backspace
            printf("*");
            strncat(Password, &Key, 1); // Concatenate the key to the password
        } else if (Key == '\b' && strlen(Password) > 0) { // If the key is Backspace and the password is not empty
            Password[strlen(Password) - 1] = '\0'; // Remove the last character from the password
            printf("\b \b"); // Erase the character from the console
        }
    } while (Key != '\r'); // Repeat until Enter is pressed
    printf("\n");
    return Password;
}
//-------------------------------------------------------------------------------------------------
void AddClient(TClient* clients, int* nbClient) {
    printf("AUTHENTIFICATION....\n");
    Client* newClient = &((*clients)[(*nbClient)++]);
    printf("Nom: ");
    scanf("%s", newClient->nom);
    printf("Prenom: ");
    scanf("%s", newClient->prenom);
    printf("Identifiant: ");
    scanf("%s", newClient->ID);
    printf("Mot de passe: ");
    strcpy(newClient->MDPS, ReadPassword()); 
    printf("Solde initial: ");
    scanf("%f", &newClient->solde);
    newClient->NbTransactions = 0;
}
//-------------------------------------------------------------------------------------------------
void AfficheINFO(TClient* clients, int nbClient) {
    Client* newClient = &((*clients)[nbClient - 1]);
    printf("Informations du nouveau client :\n");
    printf("|--------------------------------------------------------------------------------------------------------|\n");
    printf("|%-20s|%-20s|%-20s|%-20s|%-20s|\n", "Nom", "Prenom", "Identifiant", "Mot de passe", "Solde initial (DA)");
    printf("|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|%-20s|%-20s|%-20s|%-20s|%-20.2f|\n", newClient->nom, newClient->prenom, newClient->ID, newClient->MDPS, newClient->solde);
    printf("|--------------------------------------------------------------------------------------------------------|\n");
}
//-------------------------------------------------------------------------------------------------
void AjouterTransaction(TClient* clients, int clientIndex, char* TypeTransaction, float Montant) {
    int nbTransactions = (*clients)[clientIndex - 1].NbTransactions;
    (*clients)[clientIndex - 1].NbTransactions++;
    Transaction* transaction = &((*clients)[clientIndex - 1].Transactions[nbTransactions]);
    strcpy(transaction->TypeTransaction, TypeTransaction);
    transaction->Montant = Montant;
    transaction->SoldeApresTransaction = (*clients)[clientIndex - 1].solde + Montant;
    (*clients)[clientIndex - 1].solde += Montant;
}
//-------------------------------------------------------------------------------------------------
void Depot(TClient* clients, int clientIndex) {
    float Montant;
    printf("Veuillez preciser le montant a deposer : ");
    scanf("%f", &Montant);
    printf("Veuillez patienter...\n");
    usleep(4000000); // Sleep for 4000 milliseconds (4000 * 1000)
    Client* client = &((*clients)[clientIndex - 1]);
    int nbTransactions = client->NbTransactions;
    client->NbTransactions++;
    strcpy(client->Transactions[nbTransactions].TypeTransaction, "Depot");
    client->Transactions[nbTransactions].Montant = Montant;
    client->Transactions[nbTransactions].SoldeApresTransaction = client->solde + Montant;
    client->solde += Montant;
    system("cls");
    printf("--------------------------*Youb Nader*--------------------------\n");
    printf(" --> Depot effectue avec succes\n");
    printf("----------------------------------------------\n");
    printf(">Compte: %s %s\n", client->nom, client->prenom);
    printf(">Type de transaction: depot d'argent\n");
    printf(">Montant depose: %.2f DA\n", Montant);
    printf(">Nouveau solde: %.2f DA\n", client->solde);
    printf("----------------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------
void AfficheHistorique(TClient* clients, int clientI) {
    printf(" --> Historique de transactions\n");
    printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
    printf("|%-15s|%-25s|%-25s|%-15s|%-20s|\n", "Transaction", "Compte", "Type de transaction", "Montant", "Solde apres transaction");
    printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
    Client* client = &((*clients)[clientI - 1]);
    if (client->NbTransactions > 0) {
        for (int i = 0; i < client->NbTransactions; i++) {
            // Construire une chaîne de compte avec nom et prénom sans modifier les données originales
            char compte[100];
            snprintf(compte, sizeof(compte), "%s %s", client->nom, client->prenom);
            printf("|%-15d|%-25s|%-25s|%-15.2f|%-20.2f    |\n", i + 1, compte, client->Transactions[i].TypeTransaction, client->Transactions[i].Montant, client->Transactions[i].SoldeApresTransaction);
            printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
        }
    } else {
        printf(" --> Pas de transactions à afficher.\n");
        printf("-------------------------------------------------------------------------------------------------\n");
    }
}
//-------------------------------------------------------------------------------------------------
void ConsultationSolde(TClient* clients, int clientI) {
    printf("Compte: %s %s\n", (*clients)[clientI - 1].nom, (*clients)[clientI - 1].prenom);
    printf("Solde actuel: %.2f DA\n", (*clients)[clientI - 1].solde);
}
//-------------------------------------------------------------------------------------------------
void menu(TClient* clients, int nbClient) {
    int ch, cch;
    float montant;
    do {
        printf("---------------MENU---------------\n");
        printf("1: Transaction\n");
        printf("2: Historique de transaction\n");
        printf("3: Consultation de solde\n");
        printf("4: Quitter\n");
        printf("Veuillez entrer votre choix: ");
        scanf("%d", &ch);
    } while (ch < 1 || ch > 4);
    switch (ch) {
        case 1:
            do {
                system("cls");
                printf("--------------------------*Youb Nader*--------------------------\n");
                printf("TRANSACTION....\n");
                printf("----------------------------------------------------------\n");
                printf("1: Retrait d'argent\n");
                printf("2: Depot d'argent\n");
                printf("Veuillez definir le type de transaction: ");
                scanf("%d", &cch);
            } while (cch < 1 || cch > 2);
            switch (cch) {
                case 1:
                    printf("----------------------------------------------------------\n");
                    printf("Retrait....\n");
                    printf("--------------------------\n");
                    printf("Veuillez preciser le montant a retirer: ");
                    scanf("%f", &montant);
                    printf("Veuillez patienter...\n");
                    usleep(4000000);
                    printf("Nous verifions votre solde....\n");
                    usleep(3000000);
                    if (montant > (*clients)[nbClient - 1].solde) {
                        system("cls");
                        printf("--------------------------*Youb Nader*--------------------------\n");
                        printf("Solde insuffisant.\n");
                        printf("----------------------------------------------------------------\n");
                    } else {
                        (*clients)[nbClient - 1].solde -= montant;
                        int nbTransactions = (*clients)[nbClient - 1].NbTransactions;
                        (*clients)[nbClient - 1].NbTransactions++;
                        strcpy((*clients)[nbClient - 1].Transactions[nbTransactions].TypeTransaction, "Retrait");
                        (*clients)[nbClient - 1].Transactions[nbTransactions].Montant = montant;
                        (*clients)[nbClient - 1].Transactions[nbTransactions].SoldeApresTransaction = (*clients)[nbClient - 1].solde;
                        system("cls");                       
                        printf("--------------------------*Youb Nader*--------------------------\n");
                        printf(" --> Retrait effectue avec succes.\n");
                        printf("----------------------------------------------------------------\n");
                        printf(">Compte: %s %s\n", (*clients)[nbClient - 1].nom, (*clients)[nbClient - 1].prenom);
                        printf(">Type de transaction: retrait\n");
                        printf(">Montant retire: %.2f DA\n", montant);
                        printf(">Nouveau solde: %.2f DA\n", (*clients)[nbClient - 1].solde);
                        printf("------------------------------------------------------------\n");
                    }
                    break;
                case 2:
                    system("cls");
                    printf("--------------------------*Youb Nader*--------------------------\n");
                    printf("Depot....\n");
                    printf("--------------------------\n");
                    Depot(clients, nbClient);
                    break;
            }
            break;
        case 2:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Historique de transaction....\n");
            printf("-------------------------------------------------------------\n");
            system("cls");
            printf("-------------------------------------------------------------\n");
            AfficheHistorique(clients, nbClient);
            break;
        case 3:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Consultation du solde....\n");
            printf("---------------------------------\n");
            printf("Veuillez patienter...\n");
            usleep(2000000);
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Consultation du solde....\n");
            ConsultationSolde(clients, nbClient);
            printf("-------------------------------------------------------------\n");
            break;
        case 4:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Merci de nous avoir fait confiance.\n");
            printf("-----------------------*Bonne journee*-----------------------\n");
            exit(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
int main() {
    TClient clients;
    int nbClient = 0;
    system("cls");
    printf("--------------------------*Youb Nader*--------------------------\n");
    AddClient(&clients, &nbClient);
    printf("Authentification en cours....\n");
    usleep(5000000); // Sleep for 5000 milliseconds (5000 * 1000)
    system("cls");
    printf("--------------------------*Youb Nader*--------------------------\n");
    printf("Authentification effectuee avec succes.\n");
    AfficheINFO(&clients, nbClient);
    printf("-------------------------------------------------------------\n");
    char key;
    do {
        menu(&clients, nbClient);
        scanf("%c", &key);
    } while (key != 27); // 27 is the ASCII code for the Escape key
    return 0;
}