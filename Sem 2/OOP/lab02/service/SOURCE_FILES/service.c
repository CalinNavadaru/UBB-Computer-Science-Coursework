//
// Created by calin on 13.03.2023.
//

#include "../HEADERS/service.h"

int adaugare_cheltuiala_service(Repo *r, int nr, double suma, char tip[]) {
    Cheltuiala c;
    set_tip(&c, tip);
    set_suma(&c, suma);
    c.numarul_apartamentului = nr;

    if (validator(c) < 0)
        return -1;

    return adaugare_cheltuiala(r, c);
}

int modificare_cheltuiala_service(Repo *r, int poz, char tip_nou[], double suma) {
    Cheltuiala *c = &(r->date[poz]);
    set_suma(c, suma);
    set_tip(c, tip_nou);
    if (validator(*c) < 0)
        return -1;

    return modificare_cheltuiala(r, *c, poz);
}

int stergere_cheltuiala_service(Repo *r, int poz) {
    return stergere_cheltuiala(r, poz);
}

int cautare_service(Repo *r, Cheltuiala c) {
    return cautare(r, c);
}