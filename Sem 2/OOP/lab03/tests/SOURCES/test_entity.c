//
// Created by calin on 18.03.2023.
//

#include "../HEADERS/test_entity.h"

void test_entity() {
    Cheltuiala c1, c2, c3;

    c1 = creare_Cheltuiala(1, 600.56, "gaz");
    assert(c1.numar_apartament == 1);
    assert(c1.suma == 600.56);
    assert(strcmp(c1.tip, "gaz") == 0);

    c2 = creare_Cheltuiala(2, 3.14, "apa");
    set_suma(&c2, 4.56);
    set_numar_apartament(&c2, 6);
    set_tip(&c2, "incalzire");

    assert(c2.numar_apartament == 6);
    assert(c2.suma == 4.56);
    assert(strcmp(c2.tip, "incalzire") == 0);

    c3 = creare_Cheltuiala(3, 3.14, "canalizare");
    assert(get_numar_apartament(&c3) == 3);
    assert(get_suma(&c3) == 3.14);
    assert(strcmp(get_tip(&c3), "canalizare") == 0);

    assert(egalitate(c1, c2) == 0);

    distrugere_cheltuiala(&c1);
    distrugere_cheltuiala(&c2);
    distrugere_cheltuiala(&c3);
}