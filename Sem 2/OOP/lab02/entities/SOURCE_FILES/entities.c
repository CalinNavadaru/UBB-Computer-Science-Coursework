//
// Created by calin on 12.03.2023.
//

#include "../HEADERS/entities.h"
#include <string.h>

void init_Cheltuiala(Cheltuiala *c) {
    c->lungime_tip = 0;
    c->tip_plata[0] = '\0';
}

void set_tip(Cheltuiala* c, char tip_nou[]) {
    strcpy(c->tip_plata, tip_nou);
    c->lungime_tip = (int)strlen(c->tip_plata);
}

void set_suma(Cheltuiala* c, double suma_noua) {
    c->suma = suma_noua;
}

double get_suma(Cheltuiala c) {
    return c.suma;
}

int get_numarul_apartamentului(Cheltuiala c) {
    return c.numarul_apartamentului;
}

char* get_tip_plata(Cheltuiala *c) {
    return c->tip_plata;
}

int egalitate(Cheltuiala c1, Cheltuiala c2) {
    return c1.lungime_tip == c2.lungime_tip && c1.suma == c2.suma && c1.numarul_apartamentului == c2.numarul_apartamentului &&
            strcmp(c1.tip_plata, c2.tip_plata) == 0;
}