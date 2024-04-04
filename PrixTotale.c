#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

int main()
{
    float ht, ttc, tva;
    int na;
    char key;
    do
    {
        system("cls");
        printf("-------------------Youb Nader-------------------\n");
        printf("Donnez le montant HT : ");
        scanf("%f", &ht);
        printf("Entrez le nombre d'articles : ");
        scanf("%d", &na);
        printf("Entrez le taux de TVA : ");
        scanf("%f", &tva);
        ttc = ht * na * (1 + (tva / 100));
        printf("-----------------------------------------------\n");
        printf("Le prix TTC des articles est : %.2f \n", &ttc);
        printf("-----------------------------------------------\n");
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
