//
// Created by calin on 23.04.2023.
//

#include "test_validatorMedicament.h"

void test_validator() {
    string denumire, producator, substantaActiva;
    int pret;

    denumire = producator = substantaActiva = "";
    pret = -9;

    Validator v(denumire, producator, substantaActiva, pret);
    try {
        v.validare();
        assert(false);
    } catch (ValidationException& e) {
        assert(true);
    }

    denumire = "A";
    producator = "B";
    substantaActiva = "C";
    pret = 4;

    Validator v2(denumire, producator, substantaActiva, pret);
    try {
        v2.validare();
        assert(true);
    } catch (ValidationException& e) {
        assert(false);
    }
}
