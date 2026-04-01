//
// Created by calin on 02.04.2023.
//

#include "test_serviceCRUD.h"


void test_serviceCRUD() {
    Repository r;
    ServiceCRUD s(r);

    Medicament m1("A", "B", "C", 13);
    Medicament m2("QWERTY", "XXXXX", "DE", 3);
    Medicament m3("A", "D", "C", 13);

    s.adaugareMedicament("A", "B", "C", 13);
    assert(r.getNrMedicamente() == 1);
    assert(s.getContorService().size() == 1);
    assert(eq(s.getMedicament(0), m1) == true);
    s.undo();
    assert(s.getMedicamente().empty());

    s.adaugareMedicament("A", "B", "C", 13);
    s.stergereMedicament(0);
    assert(r.getNrMedicamente() == 0);

    s.adaugareMedicament("A", "B", "C", 13);
    s.adaugareMedicament("QWERTY", "XXXXX", "DE", 3);
    assert(r.getNrMedicamente() == 2);
    assert(eq(s.cautaMedicament("A", "B", "C", 13), m1) == true);

    auto rezultat = s.getMedicamente();
    assert(eq(rezultat.at(0), m1) == true);
    assert(eq(rezultat.at(1), m2) == true);

    s.modificareMedicament("A", "D", "C", 13, 0);
    rezultat = s.getMedicamente();
    assert(eq(rezultat.at(0), m3) == true);
}