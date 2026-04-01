//
// Created by calin on 21.04.2023.
//

#pragma once

#include <utility>

#include "medicament.h"
#include "../exceptions/exceptions.h"

class Validator {
private:
    string denumire, producator, substantaActiva;
    int pret;

public:

    void validare();

    Validator(string denumire, string producator, string substantaActiva, int pret): denumire(std::move(denumire)), producator(std::move(producator))
    , pret(pret), substantaActiva(std::move(substantaActiva)){

    }
};
