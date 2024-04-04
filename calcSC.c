#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define PI 3.1415

int main()
{
    char op, key;
    double a, b, res;
    double angledeg, anglerad, cosres, sinres, tanres;

    do
    {
        system("cls");
        printf("------------------------Youb Nader----------------------\n");
        printf("addiction (+)\n");
        printf("soustraction (-)\n");
        printf("multiplication (*)\n");
        printf("division (/)\n");
        printf("reste de la division entiere (%%)\n");
        printf("racine carree (q)\n");
        printf("cosinus (c)\n");
        printf("sinus (s)\n");
        printf("tangente (t)\n");
        printf("puissance (^)\n");
        printf("factorielle (!)\n");
        printf("exponontielle (e)\n");
        printf("logarithme neperien (l)\n");
        printf("PGCD (g)\n");
        printf("PPCM (p)\n");
        printf("--------------------------------------------------------\n");
        printf("Entrez votre choix: ");
        scanf(" %c", &op);

        switch (op)
        {
        case '+':
            printf("----------------------------------\n");
            printf("ADDITION...\n");
            printf("-------------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            res = a + b;
            printf("%.2f + %.2f = %.2f\n", a, b, res);
            break;
        case '-':
            printf("----------------------------------\n");
            printf("SOUSTRACTION...\n");
            printf("-------------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            res = a - b;
            printf("%.2f - %.2f = %.2f\n", a, b, res);
            break;
        case '*':
            printf("----------------------------------\n");
            printf("MULTIPLICATION...\n");
            printf("-------------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            res = a * b;
            printf("%.2f * %.2f = %.2f\n", a, b, res);
            break;
        case '/':
            printf("----------------------------------\n");
            printf("DIVISION...\n");
            printf("-------------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            if (b != 0)
            {
                res = a / b;
                printf("%.2f / %.2f = %.2f\n", a, b, res);
            }
            else
            {
                printf("Division par zero impossible.\n");
            }
            break;
        case '%':
            printf("----------------------------------\n");
            printf("RESTE DE LA DIVISION...\n");
            printf("------------------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            if (b != 0)
            {
                res = fmod(a, b);
                printf("%.2f MOD %.2f = %.2f\n", a, b, res);
            }
            else
            {
                printf("Division par zero impossible.\n");
            }
            break;
        case 'q':
            printf("----------------------------------\n");
            printf("RACINE CARREE...\n");
            printf("------------------------\n");
            printf("Entrez le nombre pour calculer la racine carree: ");
            scanf("%lf", &a);
            if (a >= 0)
            {
                res = sqrt(a);
                printf("sqrt(%f) = %.2f\n", a, res);
            }
            else
            {
                printf("Nombre negatif. La racine carree n'est pas definie.\n");
            }
            break;
        case 'c':
            printf("----------------------------------\n");
            printf("COSINUS...\n");
            printf("------------------------\n");
            printf("Entrez l'angle en degres : ");
            scanf("%lf", &angledeg);
            cosres = cos(angledeg * PI / 180); // conversion rad deg
            printf("cos(%.2f) = %.2f\n", angledeg, cosres);
            break;
        case 's':
            printf("----------------------------------\n");
            printf("SINUS...\n");
            printf("------------------------\n");
            printf("Entrez l'angle en degres : ");
            scanf("%lf", &angledeg);
            sinres = sin(angledeg * PI / 180); // Conversion rad deg
            printf("sin(%.2f) = %.2f\n", angledeg, sinres);
            break;
        case 't':
            printf("----------------------------------\n");
            printf("TANGENTE...\n");
            printf("------------------------\n");
            printf("Entrez l'angle en degres : ");
            scanf("%lf", &angledeg);
            tanres = tan(angledeg * PI / 180); // Conversion rad deg
            printf("tan(%.2f) = %.2f\n", angledeg, tanres);
            break;
            ;
        case '^':
            printf("----------------------------------\n");
            printf("PUISSANCE...\n");
            printf("------------------------\n");
            printf("Entrez un nombre: ");
            scanf("%lf", &a);
            printf("Entrez l'exposant: ");
            scanf("%lf", &b);
            res = pow(a, b);
            printf("%f ^ %f = %.2f\n", a, b, res);
            break;
        case '!':
            printf("----------------------------------\n");
            printf("FACTORIELLE...\n");
            printf("------------------------\n");
            printf("Entrez le nombre pour calculer la factorielle: ");
            scanf("%lf", &a);
            if (a >= 0 && fmod(a, 1) == 0)
            {
                res = 1;
                for (int i = 1; i <= a; i++)
                {
                    res = res * i;
                }
                printf("%f! = %.2f\n", a, res);
            }
            else
            {
                printf("Nombre non entier ou negatif. La factorielle n'est pas definie.\n");
            }
            break;
        case 'g':
            printf("----------------------------------\n");
            printf("PGCD...\n");
            printf("------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            int c = (int)a;
            int d = (int)b;
            while (d != 0)
            {
                int temp = d;
                d = c % d;
                c = temp;
            }
            res = c;
            printf("PGCD(%f ; %f) = %.2f\n", a, b, res);
            break;
        case 'p':
            printf("----------------------------------\n");
            printf("PPCM...\n");
            printf("------------\n");
            printf("Entrez le premier nombre: ");
            scanf("%lf", &a);
            printf("Entrez le deuxieme nombre: ");
            scanf("%lf", &b);
            c = (int)a;
            d = (int)b;
            int temp = c * d;
            while (d != 0)
            {
                int r = c % d;
                c = d;
                d = r;
            }
            res = temp / c;
            printf("PPCM(%f ; %f) = %.2f\n", a, b, res);
            break;
        case 'e':
            printf("----------------------------------\n");
            printf("EXPONENTIELLE...\n");
            printf("------------------------\n");
            printf("Entrez le nombre pour calculer l'exponentielle: ");
            scanf("%lf", &a);
            res = exp(a);
            printf("exp(%.2f) = %.2f\n", a, res);
            break;
        case 'l':
            printf("----------------------------------\n");
            printf("LOGARITHME NEPERIEN...\n");
            printf("------------------------\n");
            printf("Entrez le nombre pour calculer le logarithme neperien: ");
            scanf("%lf", &a);
            if (a > 0)
            {
                res = log(a);
                printf("ln(%.2f) = %.2f\n", a, res);
            }
            else
            {
                printf("Nombre non valide pour le logarithme neperien.\n");
            }
            break;
        default:
            printf("Operation non valide.\n");
        }

        key = getch();
        if (key == 13)
            continue;
        else if (key == 27)
            break;
    } while (1);
    printf("-----------------Merci-----------------\n");
    return 0;
}
