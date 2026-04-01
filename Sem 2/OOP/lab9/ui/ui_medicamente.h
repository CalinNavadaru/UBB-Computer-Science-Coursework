//
// Created by calin on 02.04.2023.
//

#pragma once

#include "../services/service_crud.h"
#include "../services/service_statistics.h"
#include "../entities/medicament_validator.h"
#include "../services/service_validateInput.h"
#include <iostream>

using std::cout;
using std::cin;
using std::string;


class UI {

private:
    ServiceCRUD& serviceCRUD;
    ServiceStatistics& serviceStatistics;

    static void printMeniu();

    void adaugareMedicamentUI();

    void modificareMedicamentUI();

    void afisareMedicamenteUI();

    void stergereMedicamentUI();

    void cautareMedicamentUI();

    void filtrareMedicamentPretUI();

    void sortareMedicamenteProducatorPretUI();

    void afisareContorUi();

    void undoUI();


public:

    explicit UI(ServiceCRUD &s, ServiceStatistics &ss) : serviceCRUD{s}, serviceStatistics{ss} {

    };
    UI(const UI& other) = delete;

    void run();
};
