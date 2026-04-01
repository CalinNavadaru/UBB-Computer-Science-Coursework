//
// Created by calin on 13.03.2023.
//

#include "../HEADERS/repo.h"

void init_repo(Repo *r) {
    r->lungime = 0;
}

int cautare(Repo *p, Cheltuiala cheltuiala) {
    for (int i = 0; i < p->lungime; i++) {
        Cheltuiala a = p->date[i];
        if (egalitate(a, cheltuiala))
            return i;
    }
    return -1;
}

int adaugare_cheltuiala(Repo *r, Cheltuiala c) {

    if (cautare(r, c) != -1)
        return 1;
    r->date[r->lungime] = c;
    r->lungime++;

    return 0;
}

int validare_pozitie(const Repo *r, int poz) {
    return poz < 0 || poz > r->lungime;
}

int stergere_cheltuiala(Repo *r, int poz) {
    if (validare_pozitie(r, poz))
        return -1;

    for (int i = poz + 1; i < r->lungime; i++)
        r->date[i - 1] = r->date[i];
    r->lungime--;

    return 0;
}

int modificare_cheltuiala(Repo *r, Cheltuiala c, int poz) {
    if (validare_pozitie(r, poz))
        return -1;

    r->date[poz] = c;

    return 0;
}

