//
// Created by calin on 20.03.2023.
//

#include "../HEADERS/test_service_statistici.h"


void test_service_statistici() {

    Repo r1;

    r1 = creeaza_repo();

    Cheltuiala c1, c2, c3;

    c1 = creare_Cheltuiala(12, 23, "gaz");
    c3 = creare_Cheltuiala(45, 123124, "apa");
    c2 = creare_Cheltuiala(1234, 1231241, "gaz");

    adauga_cheltuiala(&r1, c1);
    adauga_cheltuiala(&r1, c2);
    adauga_cheltuiala(&r1, c3);

    int lungime;
    Cheltuiala *elemente = filtrare_service(&r1, "gaz", &lungime, compara_tipuri);

    assert(lungime == 2);
    assert(egalitate(elemente[0], c1) != 0);
    assert(egalitate(elemente[1], c2) != 0);

    free(elemente);
    elemente = sortare_service(&r1, compara_suma);
    assert(egalitate(elemente[0], c1) != 0);
    assert(egalitate(elemente[1], c3) != 0);
    assert(egalitate(elemente[2], c2) != 0);

    free(elemente);

    distruge_repo(&r1);

}