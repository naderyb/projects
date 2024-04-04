#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

// Fonction pour compter le nombre de chiffres dans un nombre
int nbCH(int n)
{
    int cmp = 0;
    while (n != 0)
    {
        n /= 10;
        ++cmp;
    }
    return cmp;
}

// Fonction pour compter le nombre de chiffres pairs et impairs
void chPairImpair(int n)
{
    int pair = 0, impair = 0, ch;
    while (n != 0)
    {
        ch = n % 10;
        if (ch % 2 == 0)
            ++pair;
        else
            ++impair;
        n /= 10;
    }
    printf("\nChiffres pairs : %d\n", pair);
    printf("\nChiffres impairs: %d\n", impair);
}

// Fonction pour calculer la somme des chiffres d'un nombre
int sommeCH(int n)
{
    int somme = 0, CH;
    while (n != 0)
    {
        CH= n % 10;
        somme = somme + CH;
        n /= 10;
    }
    return somme;
}

// Fonction pour inverser un nombre
int invNB(int n)
{
    int inv = 0;
    while (n != 0)
    {
        inv = inv * 10 + n % 10;
        n /= 10;
    }
    return inv;
}

int main()
{
    int n;
    char key;
    do
    {
        system("cls");
        printf("-------------------YOUB NADER-------------------\n");
        printf("Entrez un nombre : ");
        scanf("%d", &n);
        printf("\nLe chiffre %d contient %d chiffres.\n", n, nbCH(n));
        chPairImpair(n);
        printf("\nLa somme des chiffres de %d est : %d\n",n, sommeCH(n));
        printf("\nL'inverse du nombre %d est : %d\n",n, invNB(n));
        key = getch();

        if (key == 13)
            continue;
        else if (key == 27)
            break;
    }
    while (1);
    printf("-----------------Merci-----------------");
    return 0;
}
