//
// Created by calin on 29.04.2023.
//

#include "service_validateInput.h"

void InputValidator::validareAdaugare() const{
    try {
    Validator v(denumire, producator, substantaActiva, pret);
    v.validare();
    } catch (ValidationException& e) {
        throw InputValidationException(e.getMsg());
    }
}

void InputValidator::validareModicare() const {
    try {
        Validator v(denumire, producator, substantaActiva, pret);
        v.validare();
    } catch (ValidationException& e) {
        throw InputValidationException(e.getMsg());
    }

    if (!(1 <= indice && indice <= s.getMedicamente().size())) {
        throw InputValidationException("Index invalid!\n");
    }
}

void InputValidator::validareStergere() const {
    if (!(1 <= indice && indice <= s.getMedicamente().size())) {
        throw InputValidationException("Index invalid!\n");
    }
}
