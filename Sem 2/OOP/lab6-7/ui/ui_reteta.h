//
// Created by calin on 22.04.2023.
//

#pragma once

#include "../services/service_reteta.h"
#include <iostream>

using std::cout;
using std::cin;

class UiReteta {
private:
    ServiceReteta& s;

    static void printMenu();

    void adaugareMedicamentUi();

    void golesteRetetaUi();

    void genereazaRetetaUi();

    void afisareRetetaUi();

    void geNrMedicamenteUi();

public:

    explicit UiReteta(ServiceReteta& s) : s(s) {

    }

    UiReteta(const UiReteta& q) = delete;


    void run();
};
