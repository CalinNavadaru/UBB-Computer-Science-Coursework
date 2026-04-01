//
// Created by calin on 18.03.2023.
//

#include "../HEADERS/repo.h"

Repo creeaza_repo() {
    Repo r;
    r.dimensiune = 1;
    r.lungime = 0;
    r.date_cheltuieli = (Cheltuiala*) malloc(sizeof(Cheltuiala));

    return r;
}

void redim(Repo* r) {
    Cheltuiala *date_cheltuieli_nou = (Cheltuiala*) malloc(2 * r->dimensiune * sizeof(Cheltuiala));

    for (int i = 0; i < r->dimensiune; i++)
        date_cheltuieli_nou[i] = r->date_cheltuieli[i];

    free(r->date_cheltuieli);
    r->date_cheltuieli = date_cheltuieli_nou;
    r->dimensiune*=2;
}

int adauga_cheltuiala(Repo* r, Cheltuiala c) {
    if (r->lungime == r->dimensiune)
        redim(r);

    r->date_cheltuieli[(r->lungime)++] = c;

    return 0;
}

int sterge_cheltuiala(Repo *r, int index) {

    index--;
    distrugere_cheltuiala(&r->date_cheltuieli[index]);
    for (int i = index; i < r->lungime - 1; i++)
        r->date_cheltuieli[i] = r->date_cheltuieli[i + 1];

    r->lungime--;
}

int modifca_cheltuiala(Repo* r, Cheltuiala c, int index) {
    r->date_cheltuieli[index - 1] = c;
    return 0;
}

void distruge_repo(Repo *r) {
    for (int i = 0; i < r->lungime; i++)
        distrugere_cheltuiala(&(r->date_cheltuieli[i]));
    free(r->date_cheltuieli);
}

Cheltuiala get_cheltuiala(Repo* r, int index) {
    return r->date_cheltuieli[index - 1];
}

int get_nr_elemente(Repo *r) {
    return r->lungime;
}