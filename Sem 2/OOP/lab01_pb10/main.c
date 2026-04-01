#include <stdio.h>
#include <math.h>
/*
 * Functie ce calculeaza sin(x) pentru un argument dat.
 *
 * x: Argumentul fucntiei sin.
 * return: O valoare double reprezentand valoarea sin(x). Valoarea apartine intervalului (-1, 1);
 *
 */
double calcul(double x) {
    int d = 1;
    int fact = 1;
    int k = 1;
    double exponent = x;
    double suma = 0;

    for (int i = 1; i <= 6; i++) {
        suma += (exponent / fact) * d;
        d = d * (-1);
        exponent *= x * x;
        fact *= (k + 1) * (k + 2);
        k += 2;
    }

    return suma;
}

int main() {

    double x;
    int optiune;
    while (1) {
        printf("X = ");
        scanf("%lf", &x);

        printf("Rezultat cu ajutor functiei sin(): %lf\n", sin(x));
        printf("Rezultatul este = %lf\n", calcul(x));

        printf("Apasati 1 daca doriti sa inchideti aplicatia, 2 daca doriti sa continuati.\n");
        scanf("%d", &optiune);

        while (optiune != 1 && optiune != 2) {
            printf("Optiune = ");
            scanf("%d", &optiune);
        }

        if (optiune == 1)
            break;
    }
    return 0;
}
