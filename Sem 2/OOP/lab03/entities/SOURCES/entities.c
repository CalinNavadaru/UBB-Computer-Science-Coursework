//
// Created by calin on 18.03.2023.
//

#include "../HEADERS/entities.h"

Cheltuiala creare_Cheltuiala(int numar_apartament, double suma, char *tip) {
    Cheltuiala c;
    c.suma = suma;
    c.numar_apartament = numar_apartament;
    c.lungime_tip = (int) (unsigned int) strlen(tip);
    c.tip = (char *) malloc((c.lungime_tip + 1) * sizeof(char));
    strcpy(c.tip, tip);
    return c;
}

void set_suma(Cheltuiala* c, double suma_noua) {
    c->suma = suma_noua;
}

void set_numar_apartament(Cheltuiala *c, int numar_apartament_nou) {
    c->numar_apartament = numar_apartament_nou;
}

void set_tip(Cheltuiala *c, char *tip_nou) {
    c->lungime_tip = (int) strlen(tip_nou);
    char *tip_nou_ptr = (char *) malloc((c -> lungime_tip + 1) * sizeof(char));
    strcpy(tip_nou_ptr, tip_nou);
    free(c->tip);
    c->tip = tip_nou_ptr;
}

int get_numar_apartament(Cheltuiala *c) {
    return c->numar_apartament;
}

double get_suma(Cheltuiala *c) {
    return c->suma;
}

char* get_tip(Cheltuiala *c) {
    return c->tip;
}

int egalitate(Cheltuiala c1, Cheltuiala c2) {
    return c1.numar_apartament == c2.numar_apartament && c1.suma == c2.suma && strcmp(c1.tip, c2.tip) == 0;
}

void distrugere_cheltuiala(Cheltuiala *c) {
    free(c->tip);
}