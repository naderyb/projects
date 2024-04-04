#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

int main()
{
    int a,b;
    char key;
    do{
        system("cls");
        printf("--------------------Youb Nader------------------\n");
        printf("veillez entrer le premier nombre: ");
        scanf("%d",&a);
        printf("veillez entrer le deuxieme nombre: ");
        scanf("%d",&b);
    int min = a;
    int max = a;
        switch (b > a) {
        case 1:
            max = b;
            break;
        case 0:
            min = b;
            break;
    }
    printf("---------------------------------------------------\n");
    printf("Le minimum entre %d et %d est : %d\n", a, b, min);
    printf("\nLe maximum entre %d et %d est : %d\n", a, b, max);
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
