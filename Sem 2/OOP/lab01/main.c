#include <stdio.h>
#include <math.h>

/*
* Trunchiaza un numar rational la un anumit numar de zecimale.
*
* numar: Numarul ce trebuie trunchiat. Numarul trebuie sa fie pozitiv.
* ordin: Numarul de zecimale pe care le va avea numarul trunchiat. Numarul trebuie sa fie pozitiv si nennul.
*
* return: Numarul trunchiat la ordinul specificat. Numarul este pozitiv.
*/
double trunchiere(double numar, int ordin) {
    for (int i = 1; i <= ordin; i++)
        numar *= 10;

    double rezultat = floor(numar);
    for (int i = 1; i <= ordin; i++)
        rezultat /= 10;

    return rezultat;
}
/*
 * Calculeaza radical de ordin doi dintr-un numar transmis ca parametru
 *
 * n: NUmarul pentru care se va calcula radical din ordin 2. Numarul trebuie sa fie pozitiv.
 * return: Radical de ordin 2 din n. Valoarea returnata este pozitiva.
 *
 */
double calcul_radical(int n) {
    double rezultat = 1;
    for (int i = 1; i <= 150; i++)
        rezultat = (n / rezultat + rezultat) / 2;

    return rezultat;
}

int main(){
    int numar, nr_zecimale, optiune;
    while (1) {
        printf("N=");
        scanf("%d", &numar);
        printf("Zecimale=");
        scanf("%d", &nr_zecimale);

        double radical_sqrt = sqrt(numar);

        ///afisare cu functii standard
        printf("Trunchiere radical sqrt: %f\n", trunchiere(radical_sqrt, nr_zecimale));
        ///afisare cu trunchiere propie
        printf("Trunchiere radical calculat manual: %f\n", trunchiere(calcul_radical(numar), nr_zecimale));
        printf("Trunchiere radical calculat sqrt: %f\n", radical_sqrt);

        printf("Apasati 1 daca doriti sa inchideti aplicatia, 2 sa continuati");
        scanf("%d", &optiune);


        while (optiune != 1 && optiune != 2) {
            printf("Apasati 1 daca doriti sa inchideti aplicatia, 2 sa continuati: ");
            scanf("%d", &optiune);
        }

        if (optiune == 1)
            break;

    }
    return 0;
}
