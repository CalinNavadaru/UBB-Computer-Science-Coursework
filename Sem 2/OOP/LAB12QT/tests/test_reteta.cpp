//
// Created by calin on 23.04.2023.
//

#include "test_reteta.h"


void test_reteta() {

    Medicament m1("A", "B", "C", 3);
    Medicament m2("D", "E", "F", 123);
    Medicament m3("Theta", "B", "gh", 68);
    Medicament m4("Beta", "Gamma", "Phi", 68);
    Medicament m7("ASDASDASDABeta", "Gamma", "Phi", 68);
    Repository r;

    r.adaugareMedicament(m1);
    r.adaugareMedicament(m2);
    r.adaugareMedicament(m3);
    r.adaugareMedicament(m4);

    Reteta reteta(r);

    assert(reteta.nrMedicamente() == 0);

    reteta.adauga(m1);
    assert(reteta.nrMedicamente() == 1);
    assert(eq(reteta.getReteta().at(0), m1));

    reteta.goleste();
    assert(reteta.nrMedicamente() == 0);

//    try {
//        reteta.adauga(m7);
//        assert(false);
//    } catch (RetetaException& e) {
//        assert(true);
//    }
    reteta.genereaza(2);
    assert(reteta.nrMedicamente() == 2);
}
