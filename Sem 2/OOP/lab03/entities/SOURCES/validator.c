//
// Created by calin on 18.03.2023.
//

#include "../HEADERS/validator.h"


int tip_valid(char *tip) {
    return strcmp(tip, "apa") == 0 || strcmp(tip, "canalizare") == 0 || strcmp(tip, "incalzire") == 0 || \
            strcmp(tip, "curent") == 0 || strcmp(tip, "gaz") == 0;
}

int* validator(int numar_apartament, double suma, char* tip) {

    int *erori = (int *) calloc(3, sizeof(int));
    if (numar_apartament < 0) {
        fprintf(stderr, "Numarul apartamentului este invalid(Trebuie sa fie un numar natural!).\n");
        erori[0] = 1;
    }

    if (suma <= 0) {
        fprintf(stderr, "Suma este invalida(Trebuie sa fie un numar mai mare ca zero!).\n");
        erori[1] = 1;
    }

    if (!tip_valid(tip)) {
        fprintf(stderr, "Tipul platii este invalid(Poate fi doar apa, canalizare, incalzire, curent, gaz!)\n");
        erori[2] = 1;
    }

    return erori;
}