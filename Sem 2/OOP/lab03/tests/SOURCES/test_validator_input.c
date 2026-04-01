//
// Created by calin on 21.03.2023.
//

#include "../HEADERS/test_validator_input.h"


void test_validator_input() {

    Repo r1;

    r1 = creeaza_repo();

    Cheltuiala c1, c2;

    c1 = creare_Cheltuiala(12, 23, "gaz");
    c2 = creare_Cheltuiala(13, 23, "gaz");

    adauga_cheltuiala(&r1, c1);
    adauga_cheltuiala(&r1, c2);

    int index = validare_index(&r1, 1);
    assert(index != 0);

    index = validare_index(&r1, 123);
    assert(index == 0);

    int *erori;
    erori = validate_input_adaugare(12, 23, "gaz");
    assert(erori[0] == 0);
    assert(erori[1] == 0);
    assert(erori[2] == 0);

    free(erori);

    erori = validate_input_adaugare(-1, -4, "sdadsad");

    assert(erori[0] == 1);
    assert(erori[1] == 1);
    assert(erori[2] == 1);

    free(erori);

    erori = validate_input_modificare(12, "gaz", 1, &r1);
    assert(erori[1] == 0);
    assert(erori[2] == 0);

    free(erori);

    distruge_repo(&r1);

}