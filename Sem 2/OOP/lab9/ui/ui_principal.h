//
// Created by calin on 23.04.2023.
//

#pragma once
#include "ui_reteta.h"
#include "ui_medicamente.h"

using std::cout;
class UiPrincipal {
private:
    UI& uiFarmacie;
    UiReteta& uireteta;

    void farmacieUi();

    void retetaUi();

    static void printMenu();

public:

    explicit UiPrincipal(UI& i, UiReteta& t) : uiFarmacie(i), uireteta(t) {

    }

    UiPrincipal(const UiPrincipal& q) = delete;

    void run();
};
