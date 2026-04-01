//
// Created by calin on 29.04.2023.
//

#include "test_validateInput.h"

void test_InputValidator() {

    Repository r;
    ServiceCRUD s(r);

    Medicament m1("A", "B", "C", 13);
    Medicament m2("QWERTY", "XXXXX", "DE", 3);
    Medicament m3("A", "D", "C", 13);

    s.adaugareMedicament("A", "B", "C", 13);
    s.adaugareMedicament("U", "D", "C", 13);

    InputValidator v("A", "B", "C", 15, 1, s);

    try {
        v.validareAdaugare();
        assert(true);
    } catch (InputValidationException& e) {
        assert(false);
    }

    InputValidator v1("", "B", "C", 15, 3, s);

    try {
        v1.validareAdaugare();
        assert(false);
    } catch (InputValidationException& e) {
        assert(true);
    }

    InputValidator v2("D", "C", "e", 17, 1, s);

    try {
        v2.validareModicare();
        assert(true);
    } catch (InputValidationException& e) {
        assert(false);
    }

    InputValidator v3("D", "C", "", 17, 1, s);
    try {
        v3.validareModicare();
        assert(false);
    } catch (InputValidationException& e) {
        assert(true);
    }

    InputValidator v4("AA", "B", "C", 123, -1, s);
    try {
        v4.validareModicare();
        assert(false);
    } catch (InputValidationException& e) {
        assert(true);
    }

    try {
        v4.validareStergere();
        assert(false);
    } catch (InputValidationException& e) {
        assert(true);
    }

    try {
        v.validareStergere();
        assert(true);
    } catch (InputValidationException& e) {
        assert(false);
    }
}
