//
// Created by calin on 23.04.2023.
//

#include "ui_principal.h"

void UiPrincipal::printMenu() {

    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    cout << "Meniu: \n";
    cout << "1. Gestionare farmacie;\n";
    cout << "2. Gestionare reteta;\n";
    cout << "3. Iesire;\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

}

void UiPrincipal::farmacieUi() {
    uiFarmacie.run();
}

void UiPrincipal::retetaUi() {
    uireteta.run();
}

void UiPrincipal::run() {

    int alegere;
    while (true) {
        while (true) {
            printMenu();
            cout << "Alegerea dumneavoastra este: ";
            cin >> alegere;

            if (alegere >= 1 && alegere <= 3)
                break;

            cout << "Alegere invalida!\n";
        }

        switch (alegere) {
            case 1:
                farmacieUi();
                break;
                /*
            case 2:
                retetaUi();
                break;
                 */
            default:
                return;
        }
    }
}