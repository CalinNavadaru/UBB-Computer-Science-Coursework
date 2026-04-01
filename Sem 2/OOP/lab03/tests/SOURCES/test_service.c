//
// Created by calin on 20.03.2023.
//

#include "../HEADERS/test_service.h"


void test_service() {
    Repo r1;
    Cheltuiala c1, c2;
    Cheltuiala *elemente;

    c1 = creare_Cheltuiala(12, 23.45, "gaz");
    c2 = creare_Cheltuiala(12, 23.45678, "apa");

    r1 = creeaza_repo();

    assert(adauga_cheltuiala_service(&r1, 12, 23.45, "gaz") == 0);
    assert(adauga_cheltuiala_service(&r1, 12, 23.45678, "apa") == 0);
    assert(egalitate(get_cheltuiala(&r1,1), c1) != 0);
    assert(modifica_cheltuiala_service(&r1, 23.45678, "apa", 2) == 0);
    assert(egalitate(get_cheltuiala(&r1,2), c2) != 0);
    elemente = get_elemente(&r1);
    assert(egalitate(elemente[0], c1) != 0);
    assert(egalitate(elemente[1], c2) != 0);
    assert(stergere_cheltuiala_service(&r1, 1) == 0);
    assert(stergere_cheltuiala_service(&r1, 1) == 0);
    assert(get_nr_elemente_service(&r1) == 0);

    free(elemente);

    distruge_repo(&r1);
    distrugere_cheltuiala(&c1);
    distrugere_cheltuiala(&c2);
}