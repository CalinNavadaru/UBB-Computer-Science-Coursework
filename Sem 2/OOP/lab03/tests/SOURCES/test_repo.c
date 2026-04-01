//
// Created by calin on 19.03.2023.
//

#include "../HEADERS/test_repo.h"


void test_repo() {
    Repo r1, r2, r3;

    r1 = creeaza_repo();

    assert(r1.dimensiune == 1);
    assert(r1.lungime == 0);
    assert(sizeof(r1.date_cheltuieli) == sizeof(Cheltuiala*));
    assert(get_nr_elemente(&r1) == 0);

    r2 = creeaza_repo();
    redim(&r2);
    assert(r2.dimensiune == 2);

    r3 = creeaza_repo();
    Cheltuiala c1, c2, c3, c4, c5;
    c1 = creare_Cheltuiala(1, 3.14, "gaz");
    c2 = creare_Cheltuiala(3, 3.14, "incalzire");
    c3 = creare_Cheltuiala(4, 5.456, "apa");
    c4 = creare_Cheltuiala(5, 123.3, "apa");



    adauga_cheltuiala(&r3, c1);
    assert(egalitate(r3.date_cheltuieli[0],c1) != 0);
    adauga_cheltuiala(&r3, c2);
    assert(egalitate(r3.date_cheltuieli[1],c2) != 0);
    adauga_cheltuiala(&r3, c3);
    assert(egalitate(r3.date_cheltuieli[2],c3) != 0);

    c5 = get_cheltuiala(&r3, 1);
    assert(egalitate(c5, c1) != 0);

    sterge_cheltuiala(&r3, 1);
    assert(egalitate(r3.date_cheltuieli[0], c2) != 0);

    assert(modifca_cheltuiala(&r3, c4, 1) == 0);
    assert(egalitate(r3.date_cheltuieli[0], c4) != 0);

    distruge_repo(&r1);
    distruge_repo(&r2);
    distruge_repo(&r3);

    distrugere_cheltuiala(&c2);
}