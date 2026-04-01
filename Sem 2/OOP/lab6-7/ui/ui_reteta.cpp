//
// Created by calin on 22.04.2023.
//

#include "ui_reteta.h"

void UiReteta::printMenu() {

    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Meniu: \n";
    cout << "1. Adauga medicament;\n";
    cout << "2. Goleste reteta;\n";
    cout << "3. Genereaza o reteta;\n";
    cout << "4. Afisare reteta;\n";
    cout << "5. Inapoi;\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";

}


void UiReteta::adaugareMedicamentUi() {
    string denumire;
    cout << "Denumirea medicamentului dorit este: ";
    cin >> denumire;
    try {
        s.addMedicament(denumire);
    } catch (RetetaException& r) {
        cout << r;
        return;
    }
    cout << "Medicamentul a fost adaugat in reteta cu succes!\n";

}

void UiReteta::golesteRetetaUi() {
    s.golesteReteta();
    cout << "Reteta este vida!\n";
}


void UiReteta::geNrMedicamenteUi() {
    cout << "Numarul de medicamente din reteta este: " << s.nrMedicamenteReteta() << '\n';
}

void UiReteta::afisareRetetaUi() {
    auto v = s.getReteta();

    int i = 0;
    for (const auto& el : v) {
        cout << i + 1 << ". " << "Medicamentul cu denumirea: " << el.getDenumire() << '\n';
    }
}

void UiReteta::genereazaRetetaUi() {

    int nrMdicamente;
    while (true) {
        cout << "Numarul de medicamente este: ";
        cin >> nrMdicamente;
        if (nrMdicamente > 0)
            break;

        cout << "Numarul de medicamente trebuie sa fie nenegativ!\n";
    }
    s.genereazaMedicamente(nrMdicamente);
    cout << "Reteta a fost generata!\n";
}

void UiReteta::run() {

    int choice;
    while (true) {
        printMenu();
        while (true) {
            cout << "Alegerea dumneavoastra este: ";
            cin >> choice;

            if (choice >= 1 && choice <= 5)
                break;

            cout << "Alegere invalida!\n";
        }

        switch (choice) {
            case 1:
                adaugareMedicamentUi();
                break;
            case 2:
                golesteRetetaUi();
                break;
            case 3:
                genereazaRetetaUi();
                break;
            case 4:
                afisareRetetaUi();
                break;
            default:
                return;
        }
        geNrMedicamenteUi();
    }
}
