#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

// fonction qui verifie si le nombre est premier
int isPrime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// fonction qui donne la liste des diviseurs d'un nombre
void listDivisors(int n)
{
    printf("La liste des diviseurs de %d est: ", n);
    for (int i = 1; i <= abs(n); i++)
    {
        if (abs(n) % i == 0)
        {
            printf("%d, ", i);
            if (i != abs(n) / 2)
            {
                printf("%d, ", -i);
            }
        }
    }
}
int main()
{
    int choice;
    int n;
    int a, b;

    do
    {
        do
        {
            printf("\n--------------------Youb Nader--------------------\n");
            printf("-----------------------MENU-----------------------\n");
            printf("1- teste nombre premier\n");
            printf("2- liste des diviseurs du nombre\n");
            printf("3- quitter\n");
            printf("-----------------------------------------------\n");
            printf("entrez votre choix : ");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 3);

        switch (choice)
        {
        case 1:
            system("cls");
            printf("--------------------Youb Nader--------------------\n");
            printf("\nTESTE NOMBRE PREMIER\n");
            printf("--------------------\n");
            printf("Entrez un nombre n positif : ");
            scanf("%d", &n);
            if (isPrime(n))
                printf("%d est un nombre premier.\n", n);
            else
                printf("%d n'est pas un nombre premier.\n", n);
            break;
        case 2:
            system("cls");
            printf("--------------------Youb Nader--------------------\n");
            printf("\nLA LISTE DES DIVISEURS\n");
            printf("---------------------\n");
            printf("Entrez un nombre n : ");
            scanf("%d", &n);
            listDivisors(n);
            break;
        case 3:
            printf("----------------------------------------");
            printf("\na bientot.\n");
            break;
        }
    } while (choice != 3);
    return 0;
}
