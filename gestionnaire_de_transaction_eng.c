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
    printf("AUTHENTICATION....\n");
    Client* newClient = &((*clients)[(*nbClient)++]);
    printf("First name: ");
    scanf("%s", newClient->nom);
    printf("Last name: ");
    scanf("%s", newClient->prenom);
    printf("ID: ");
    scanf("%s", newClient->ID);
    printf("Password: ");
    strcpy(newClient->MDPS, ReadPassword()); 
    printf("Initial Balance: ");
    scanf("%f", &newClient->solde);
    newClient->NbTransactions = 0;
}
//-------------------------------------------------------------------------------------------------
void AfficheINFO(TClient* clients, int nbClient) {
    Client* newClient = &((*clients)[nbClient - 1]);
    printf("New customer information:\n");
    printf("|--------------------------------------------------------------------------------------------------------|\n");
    printf("|%-20s|%-20s|%-20s|%-20s|%-20s|\n", " first name", "last name", "ID", "Password", "Initial balance (DZD)");
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
    printf("Please specify the deposit amount: ");
    scanf("%f", &Montant);
    printf("Please wait while your transaction is processing...\n");
    usleep(4000000); // Sleep for 4000 milliseconds (4000 * 1000)
    Client* client = &((*clients)[clientIndex - 1]);
    int nbTransactions = client->NbTransactions;
    client->NbTransactions++;
    strcpy(client->Transactions[nbTransactions].TypeTransaction, "Deposit");
    client->Transactions[nbTransactions].Montant = Montant;
    client->Transactions[nbTransactions].SoldeApresTransaction = client->solde + Montant;
    client->solde += Montant;
    system("cls");
    printf("--------------------------*Youb Nader*--------------------------\n");
    printf(" --> Deposit successfully completed. \n");
    printf("----------------------------------------------\n");
    printf(">Account: %s %s\n", client->nom, client->prenom);
    printf(">Type of transaction: Money deposit\n");
    printf(">Amount deposited: %.2f DZD\n", Montant);
    printf(">New balance: %.2f DZD\n", client->solde);
    printf("-----------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------
void AfficheHistorique(TClient* clients, int clientI) {
    printf(" --> Transaction history\n");
    printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
    printf("|%-15s|%-25s|%-25s|%-15s|%-20s|\n", "Transaction", "Account", "Type of transaction", "amount", "New balance");
    printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
    Client* client = &((*clients)[clientI - 1]);
    if (client->NbTransactions > 0) {
        for (int i = 0; i < client->NbTransactions; i++) {
            //construire une chaine de compte avec nom et prenom sans modifier les donnees originales
            char compte[100];
            snprintf(compte, sizeof(compte), "%s %s", client->nom, client->prenom);
            printf("|%-15d|%-25s|%-25s|%-15.2f|%-20.2f    |\n", i + 1, compte, client->Transactions[i].TypeTransaction, client->Transactions[i].Montant, client->Transactions[i].SoldeApresTransaction);
            printf("|---------------|-------------------------|-------------------------|---------------|------------------------|\n");
        }
    } else {
        printf(" --> No transactions to display.\n");
        printf("-------------------------------------------------------------------------------------------------\n");
    }
}
//-------------------------------------------------------------------------------------------------
void ConsultationSolde(TClient* clients, int clientI) {
    printf(">Account: %s %s\n", (*clients)[clientI - 1].nom, (*clients)[clientI - 1].prenom);
    printf(">Balance: %.2f DZD\n", (*clients)[clientI - 1].solde);
}
//-------------------------------------------------------------------------------------------------
void menu(TClient* clients, int nbClient) {
    int ch, cch;
    float montant;
    do {
        printf("---------------MENU---------------\n");
        printf("1: Transaction\n");
        printf("2: Transaction history\n");
        printf("3: Balance inquiry\n");
        printf("4: Exit\n");
        printf("Please enter your selection: ");
        scanf("%d", &ch);
    } while (ch < 1 || ch > 4);
    switch (ch) {
        case 1:
            do {
                system("cls");
                printf("--------------------------*Youb Nader*--------------------------\n");
                printf("TRANSACTION....\n");
                printf("----------------------------------------------------------\n");
                printf("1: Withdrawal of funds\n");
                printf("2: Depost of funds\n");
                printf("Please specify the type of transaction: ");
                scanf("%d", &cch);
            } while (cch < 1 || cch > 2);
            switch (cch) {
                case 1:
                    printf("----------------------------------------------------------\n");
                    printf("Withdrawal....\n");
                    printf("--------------------------\n");
                    printf("Please specify the amount to withdraw: ");
                    scanf("%f", &montant);
                    printf("Please wait while your transaction is processing...\n");
                    usleep(4000000);
                    printf("We are checking your balance....\n");
                    usleep(3000000);
                    if (montant > (*clients)[nbClient - 1].solde) {
                        system("cls");
                        printf("--------------------------*Youb Nader*--------------------------\n");
                        printf("Insufficient funds.\n");
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
                        printf(" --> Withdrawal successfully completed\n");
                        printf("----------------------------------------------------------------\n");
                        printf(">Account: %s %s\n", (*clients)[nbClient - 1].nom, (*clients)[nbClient - 1].prenom);
                        printf(">Type of transaction: Money withdrawal\n");
                        printf(">Amount withdrawn: %.2f DZD\n", montant);
                        printf(">New balance: %.2f DZD\n", (*clients)[nbClient - 1].solde);
                        printf("------------------------------------------------------------\n");
                    }
                    break;
                case 2:
                    system("cls");
                    printf("--------------------------*Youb Nader*--------------------------\n");
                    printf("Deposit....\n");
                    printf("--------------------------\n");
                    Depot(clients, nbClient);
                    break;
            }
            break;
        case 2:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Transaction history....\n");
            printf("-------------------------------------------------------------\n");
            system("cls");
            printf("-------------------------------------------------------------\n");
            AfficheHistorique(clients, nbClient);
            break;
        case 3:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Balance inquiry....\n");
            printf("---------------------------------\n");
            printf("Please wait while your request is processing...\n");
            usleep(2000000);
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Balance inquiry....\n");
            printf("---------------------------------\n");
            ConsultationSolde(clients, nbClient);
            printf("-------------------------------------------------------------\n");
            break;
        case 4:
            system("cls");
            printf("--------------------------*Youb Nader*--------------------------\n");
            printf("Thank you for choosing our services.\n");
            printf("-----------------------*Have a good day*-----------------------\n");
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
    printf("Authentication process started....\n");
    usleep(5000000); // Sleep for 5000 milliseconds (5000 * 1000)
    printf("Authentication process ended...");
    usleep(3000000);
    system("cls");
    printf("--------------------------*Youb Nader*--------------------------\n");
    AfficheINFO(&clients, nbClient);
    printf("-------------------------------------------------------------\n");
    char key;
    do {
        menu(&clients, nbClient);
        scanf("%c", &key);
    } while (key != 27); // 27 is the ASCII code for the Escape key
    return 0;
}