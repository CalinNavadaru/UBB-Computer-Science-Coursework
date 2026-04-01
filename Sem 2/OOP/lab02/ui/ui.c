//
// Created by calin on 13.03.2023.
//
#include <stdio.h>
#include "ui.h"


void print_meniu() {
    printf("Meniu:\n");
    printf("1. Adaugare cheltuiala.\n");
    printf("2. Modificare cheltuiala.\n");
    printf("3. Stergere cheltuiala.\n");
    printf("4. Afiseaza toate cheltuielile.\n");
    printf("5. Iesire.\n");
}

void afisare_cheltuieli_UI(Repo *r) {

    for (int i = 0; i < r->lungime; i++) {
        printf ("%d. %s %lf %d\n", i + 1, r->date[i].tip_plata, r->date[i].suma, r->date[i].numarul_apartamentului);
    }
}

void afisare_eroare(int rez) {
    if (rez < 0)
        printf("A aparut o eroare!");
}

void adaugare_cheltuiala_UI(Repo *r) {
    int numarul_apar;
    double suma;
    char tip[25];
    printf("Numarul apartamentului: ");
    scanf("%d", &numarul_apar);
    printf("Suma cheltuieli: ");
    scanf("%lf", &suma);
    printf("Tipul cheltuieli: ");
    scanf("%s", tip);

    int rez = adaugare_cheltuiala_service(r, numarul_apar, suma, tip);

    afisare_eroare(rez);

    printf("Cheltuiala a fost adaugata!");
}

void modificare_cheltuiala_UI(Repo *r) {
    afisare_cheltuieli_UI(r);
    int poz;
    double suma;
    char tip[25];
    printf("Indexul apartamentului: ");
    scanf("%d", &poz);
    poz--;
    printf("Suma cheltuieli: ");
    scanf("%lf", &suma);
    printf("Tipul cheltuieli: ");
    scanf("%s", tip);

    int rez = modificare_cheltuiala_service(r, poz, tip, suma);

    afisare_eroare(rez);
    if (rez == 0)
        printf("Modificarea a fost facuta cu succes!");
}

void stergere_cheltuiala_UI(Repo *r) {
    afisare_cheltuieli_UI(r);
    int poz;
    printf("Indexul apartamentului: ");
    scanf("%d", &poz);
    poz--;
    int rez = stergere_cheltuiala_service(r, poz);

    afisare_eroare(rez);
    if (rez == 0)
        printf("Stergerea a fost facuta cu succes!");
}



int run(Repo *r) {

    while (1) {
        print_meniu();
        int alegere;
        while (scanf("%d", &alegere) == 1) {
            if (!(1 <= alegere && alegere <= 5)) {
                printf("Alegere invalida!");
                continue;
            }
            break;
        }
        switch (alegere) {
            case 1: adaugare_cheltuiala_UI(r); break;
            case 2: modificare_cheltuiala_UI(r); break;
            case 3: stergere_cheltuiala_UI(r); break;
            case 4: afisare_cheltuieli_UI(r); break;
            default: return 0;
        }

        printf("\n");
    }
}