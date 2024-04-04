#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main()
{
    int age;
    char key;
    do
    {
        system("cls");
        printf("-------------------YOUB NADER-------------------\n");
        printf("Veuillez donner l'age de la personne: ");
        scanf("%d", &age);
        switch (age)
        {
        default:
            if (age < 6)
                printf("Tres jeune.\n");
            else
                printf("Senior\n");
            break;
        case 6:
        case 7:
            printf("Poussin.\n");
            break;
        case 8:
        case 9:
            printf("Pupille.\n");
            break;
        case 10:
        case 11:
            printf("Minime.\n");
            break;
        case 12:
        case 13:
        case 14:
        case 15:
            printf("Cadet.\n");
            break;
        case 16:
        case 17:
        case 18:
            printf("Junior.\n");
            break;
        }
        key = getch();

        if (key == 13)
            continue;
        else if (key == 27)
            break;
    } while (1);
    printf("-----------------Merci-----------------");
    return 0;
}
