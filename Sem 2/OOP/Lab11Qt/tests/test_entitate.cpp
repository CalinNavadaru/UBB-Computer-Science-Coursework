//
// Created by calin on 01.04.2023.
//

#include "test_entitate.h"


void testEntitate() {

    Medicament m1("A", "B", "C", 13);
    Medicament m2("QWERTY", "XXXXX", "DE", 3);
    Medicament m3("A", "B", "C", 13);
    Medicament m4("A", "B", "C", 13);

    assert(m3 == m4);
    assert(m1.getId() == 1);
    assert(m2.getId() == 2);
    assert(m2.getDenumire() == "QWERTY");
    assert(m2.getPret() == 3);
    assert(m1.getProducator() == "B");
    assert(m2.getSubstantaActiva() == "DE");

    m1.setPret(1);
    assert(m1.getPret() == 1);

    m2.setDenumire(string("WSXZAQ"));
    assert(m2.getDenumire() == string("WSXZAQ"));

    m2.setSubstantaActiva(string("azxse"));
    assert(m2.getSubstantaActiva() == string("azxse"));

    m1.setProducator("z");
    assert(m1.getProducator() == string("z"));

    assert(eq(m1, m2) == false);
    assert(eq(m4, m3) == true);
}