//
// Created by calin on 19.03.2023.
//

#include "../HEADERS/ui.h"

#include <stdio.h>
#include <stdlib.h>


void print_menu() {
    printf("---------------------------------------------------------------\n");
    printf("Meniu:\n");
    printf("1. Adugare cheltuiala;\n");
    printf("2. Modificare cheltuiala;\n");
    printf("3. Stergere cheltuiala;\n");
    printf("4. Afisare cheltuieli;\n");
    printf("5. Filtrare cheltuieli dupa tip;\n");
    printf("6. Ordonare cheltuieli dupa suma;\n");
    printf("7. Iesire;\n");
    printf("----------------------------------------------------------------\n");
}

void adaugare_cheltuiala_ui(Repo *r) {
    int numar_apartament;
    double suma;
    char tip[1000];
    int *erori = (int *) malloc (3 * sizeof(int));
    for (int i = 0; i < 3; i++)
        erori[i] = 1;
    int are_eroare = 0;
    do {
        if (erori[0] == 1) {
            printf("Introduceti numarul apartamentului: \n");
            scanf("%d", &numar_apartament);
            are_eroare = 1;
        } else {
            printf("Numarul apartamentului introdus: %d\n", numar_apartament);
        }

        if (erori[1] == 1) {
            printf("Introduceti suma: \n");
            scanf("%lf", &suma);
            are_eroare = 1;
        } else {
            printf("Suma introdusa este: %lf\n", suma);
        }

        if (erori[2] == 1) {
            printf("Introduceti tipul: \n");
            scanf("%s", tip);
            are_eroare = 1;
        } else {
            printf("Tipul platii introduse este: %s\n", tip);
        }

        if (are_eroare == 0) {
            adauga_cheltuiala_service(r, numar_apartament, suma, tip);
            printf("Cheltuiala a fost adaugata!\n");
            free(erori);
            break;
        } else {
            free(erori);
            erori = validate_input_adaugare(numar_apartament, suma, tip);
            are_eroare = 0;
        }
    }while(1);
}

void afisare_cheltuiala_ui(Repo *r) {
    Cheltuiala *elemente = get_elemente(r);
    int lungime = get_nr_elemente_service(r);
    for (int i = 0; i < lungime; i++)
        printf("%d. Nr: %d; Suma: %lf; Tip: %s\n", i + 1, get_numar_apartament(&elemente[i]), get_suma(&elemente[i]), \
        get_tip(&elemente[i]));
    free(elemente);
}

void modifca_cheltuiala_ui(Repo *r) {
    afisare_cheltuiala_ui(r);

    int index;
    double suma;
    char tip[1000];
    int *erori = (int *) malloc (3 * sizeof(int));
    for (int i = 0; i < 3; i++)
        erori[i] = 1;
    int are_eroare = 0;

    while (1) {
        printf("Indicele apartamentului dorit este: ");
        scanf("%d", &index);

        if (validare_index(r, index) != 0)
            break;

        fprintf(stderr, "INdex invalid!");
    }

    do {
        if (erori[1] == 1) {
            printf("Introduceti suma: \n");
            scanf("%lf", &suma);
            are_eroare = 1;
        } else {
            printf("Suma introdusa este: %lf\n", suma);
        }

        if (erori[2] == 1) {
            printf("Introduceti tipul: \n");
            scanf("%s", tip);
            are_eroare = 1;
        } else {
            printf("Tipul platii introduse este: %s\n", tip);
        }

        if (are_eroare == 0) {
            modifica_cheltuiala_service(r, suma, tip, index);
            printf("Cheltuiala a fost modificata!\n");
            free(erori);
            break;
        } else {
            free(erori);
            erori = validate_input_modificare(suma, tip, index, r);
            are_eroare = 0;
        }

    }while(1);
}

void sterge_cheltuiala_ui(Repo *r) {
    afisare_cheltuiala_ui(r);

    int index;
    while (1) {
        printf("Indicele apartamentului dorit este: ");
        scanf("%d", &index);

        if (validare_index(r, index) != 0)
            break;

        fprintf(stderr, "INdex invalid!\n");
    }

    stergere_cheltuiala_service(r, index);
    printf("Cheltuiala a fost stearsa!\n");
}

void filtrare_cheltuieli_ui(Repo *r) {


    char tip[250];
    int lungime;
    printf("Tipul dorit: ");
    scanf("%s", tip);
    Cheltuiala *elemente_filtrare = filtrare_service(r, tip, &lungime, compara_tipuri);
    for (int i = 0; i < lungime; i++)
        printf("%d. Nr: %d; Suma: %lf; Tip: %s\n", i + 1, get_numar_apartament(&elemente_filtrare[i]), get_suma(&elemente_filtrare[i]), \
        get_tip(&elemente_filtrare[i]));

    free(elemente_filtrare);
}

void sortare_cheltuieli_ui(Repo *r) {
    Cheltuiala *elemente = sortare_service(r, compara_suma);
    int lungime = get_nr_elemente_service(r);
    for (int i = 0; i < lungime; i++)
        printf("%d. Nr: %d; Suma: %lf; Tip: %s\n", i + 1, get_numar_apartament(&elemente[i]), get_suma(&elemente[i]), \
        get_tip(&elemente[i]));
    free(elemente);
}

void run(Repo *r) {

    int alegere;
    while(1) {
        print_menu();
        printf("Alegerea este: ");
        scanf("%d", &alegere);

        if (!(1 <= alegere && alegere <= 7))
            continue;

        switch (alegere) {
            case 1:
                adaugare_cheltuiala_ui(r);
                break;
            case 2:
                modifca_cheltuiala_ui(r);
                break;
            case 3:
                sterge_cheltuiala_ui(r);
                break;
            case 4:
                afisare_cheltuiala_ui(r);
                break;
            case 5:
                filtrare_cheltuieli_ui(r);
                break;
            case 6:
                sortare_cheltuieli_ui(r);
                break;
            default:
                return;
        }
    }
}