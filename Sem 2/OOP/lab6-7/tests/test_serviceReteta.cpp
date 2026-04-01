//
// Created by calin on 23.04.2023.
//

#include "test_serviceReteta.h"

void test_serviceReteta() {

    Repository r;
    Reteta reteta(r);
    ServiceReteta serviceReteta(reteta);

    Medicament m1("A", "B", "C", 3.14);
    Medicament m2("D", "E", "F", 123);
    Medicament m3("Theta", "B", "gh", 68.69);
    Medicament m4("Beta", "Gamma", "Phi", 68.69);

    r.adaugareMedicament(m1);
    r.adaugareMedicament(m2);
    r.adaugareMedicament(m3);
    r.adaugareMedicament(m4);

    assert(serviceReteta.nrMedicamenteReteta() == 0);

    serviceReteta.addMedicament("D");
    assert(serviceReteta.nrMedicamenteReteta() == 1);

    serviceReteta.golesteReteta();
    assert(serviceReteta.nrMedicamenteReteta() == 0);

    serviceReteta.genereazaMedicamente(2);
    assert(serviceReteta.nrMedicamenteReteta() == 2);

    serviceReteta.golesteReteta();

    serviceReteta.addMedicament("D");
    assert(eq(serviceReteta.getReteta().at(0), m2));
}
