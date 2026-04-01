//
// Created by calin on 29.04.2023.
//
#pragma once

#include <utility>

#include "../entities/medicament_validator.h"
#include "../exception"
#include "service_crud.h"

class InputValidator {

private:
    string denumire, producator, substantaActiva;
    int pret;
    int indice;
    ServiceCRUD& s;

public:

    InputValidator(string denumire, string producator, string substantaActiva, int pret, int indice, ServiceCRUD& s) : denumire{std::move(denumire)} ,
        producator{std::move(producator)}, substantaActiva{std::move(substantaActiva)}, pret{pret} , indice{indice}, s{s}{

    };

    InputValidator(const InputValidator& a) = delete;

    void validareAdaugare() const;

    void validareModicare() const;

    void validareStergere() const;

    friend class ServiceCRUD;
};