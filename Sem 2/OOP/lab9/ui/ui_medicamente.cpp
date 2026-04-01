//
// Created by calin on 02.04.2023.
//

#include "ui_medicamente.h"

void UI::run() {
    while (true) {
        printMeniu();
        int alegere;
        cout << "Alegerea dumneavoastra este: ";
        cin >> alegere;
        if (!(1 <= alegere && alegere <= 10)) {
            cout << "Alegere invalida!";
            continue;
        }
        switch (alegere) {
            case 1:
                adaugareMedicamentUI();
                break;
            case 2:
                modificareMedicamentUI();
                break;
            case 3:
                stergereMedicamentUI();
                break;
            case 4:
                cautareMedicamentUI();
                break;
            case 5:
                afisareMedicamenteUI();
                break;
            case 6:
                filtrareMedicamentPretUI();
                break;
            case 7:
                sortareMedicamenteProducatorPretUI();
                break;
            case 8:
                afisareContorUi();
                break;
            case 9:
                undoUI();
                break;
            default:
                return;
        }
    }
}

void UI::printMeniu() {
    cout << "--------------------------------------------------\n";
    cout << "Meniu:\n";
    cout << "1. Adaugare medicament;\n";
    cout << "2. Modificare medicament;\n";
    cout << "3. Stergere medicament;\n";
    cout << "4. Cautare medicament;\n";
    cout << "5. Afisare medicamente;\n";
    cout << "6. Filtrare medicamente dupa pret;\n";
    cout << "7. Sortare medicamente producator + pret;\n";
    cout << "8. Afisare contorizare;\n";
    cout << "9. UNDO;\n";
    cout << "10. Inapoi;\n";
    cout << "--------------------------------------------------\n";
}

void UI::adaugareMedicamentUI() {
    string denumire, producator, substantaActiva;
    int pret;
    cout << "Denumirea produsului: ";
    cin >> denumire;
    cout << "Producatorul produsului: ";
    cin >> producator;
    cout << "Substanta activa: ";
    cin >> substantaActiva;
    cout << "Pretul: ";
    cin >> pret;
    InputValidator v1(denumire, producator, substantaActiva, pret, -1, serviceCRUD);
    try {
        v1.validareAdaugare();
    } catch (const InputValidationException& e) {
        cout << e;
        return;
    }
    int rez;
    try {
        rez = serviceCRUD.adaugareMedicament(denumire, producator, substantaActiva, pret);
    } catch (const RepositoryException& e) {
        cout << e;
        return;
    }
    if (rez == 0)
        cout << "Medicamentul a fost adaugat cu succes!\n";
}

void UI::modificareMedicamentUI() {
    int index;
    string denumire, producator, substantaActiva;
    int pret;
    afisareMedicamenteUI();
    cout << "Indicele medicamentului de modificat: ";
    cin >> index;
    cout << "Datele medicamentului: \n";
    cout << "Denumirea produsului: ";
    cin >> denumire;
    cout << "Producatorul produsului: ";
    cin >> producator;
    cout << "Substanta activa: ";
    cin >> substantaActiva;
    cout << "Pretul: ";
    cin >> pret;
    InputValidator v1(denumire, producator, substantaActiva, pret, index, serviceCRUD);
    Validator v(denumire, producator, substantaActiva, pret);
    try {
        v1.validareModicare();
    } catch (const InputValidationException& e) {
        cout << e;
        return;
    }
    int rez = serviceCRUD.modificareMedicament(denumire, producator, substantaActiva, pret, index - 1);
    if (rez == 0)
        cout << "Medicamentul a fost modificat cu succes!\n";
}

void UI::afisareMedicamenteUI() {
    int i = 1;
    auto listaMedicamente = serviceCRUD.getMedicamente();
    for (const auto &v: listaMedicamente) {
        cout << i << ". " << v.getDenumire() << ' ' << v.getProducator() << ' ' << v.getSubstantaActiva() << ' ' <<
            v.getPret() << '\n';
        i++;
    }
}

void UI::stergereMedicamentUI() {
    int index;
    afisareMedicamenteUI();
    cout << "Indicele medicamentului de sters: ";
    cin >> index;
    InputValidator v1("", "", "", -3, index, serviceCRUD);
    try {
        v1.validareStergere();
    } catch (const InputValidationException& e) {
        cout << e;
        return;
    }
    serviceCRUD.stergereMedicament(index - 1);
}

void UI::cautareMedicamentUI() {
    afisareMedicamenteUI();
    string denumire, producator, substantaActiva;
    double pret;
    cout << "Denumirea produsului: ";
    cin >> denumire;
    cout << "Producatorul produsului: ";
    cin >> producator;
    cout << "Substanta activa: ";
    cin >> substantaActiva;
    cout << "Pretul: ";
    cin >> pret;
    auto rez = serviceCRUD.cautaMedicament(denumire, producator, substantaActiva, pret);
    cout << rez.getDenumire() << ' ' << rez.getProducator() << ' ' << rez.getSubstantaActiva() << ' ' <<
         rez.getPret() << '\n';
}

void UI::filtrareMedicamentPretUI() {
    int pret;
    while (true) {
        cout << "Pretul este: ";
        cin >> pret;
        if (pret > 0)
            break;

        cout << "Pretul introdus este invalid!\n";
    }
    vector<Medicament> v;
    v = serviceStatistics.filtrareMedicamentePret(pret);
    if (v.empty()) {
        cout << "Nu exista medicamente cu pretul dat!\n";
        return;
    }
    for (const auto& el: v) {
        cout << "Denumirea: " << el.getDenumire() << "; " << "Producator: " << el.getProducator() << "; ";
        cout << "Substanta activa: " << el.getSubstantaActiva() << "; " << "Pret: " << el.getPret() << '\n';
    }
}

void UI::sortareMedicamenteProducatorPretUI() {
    vector<Medicament> v;
    v = serviceStatistics.sortareMedicamenteProducatorPret([] (const Medicament& m1, const Medicament& m2) {
        return m1.getProducator() > m2.getProducator() || (m1.getProducator() == m2.getProducator() && m1.getPret() > m2.getPret());
    });

    for (const auto& el: v) {
        cout << "Denumirea: " << el.getDenumire() << "; " << "Producator: " << el.getProducator() << "; ";
        cout << "Substanta activa: " << el.getSubstantaActiva() << "; " << "Pret: " << el.getPret() << '\n';
    }
}

void UI::afisareContorUi() {
    for (auto& el : serviceCRUD.getContorService()) {
        cout << "Denumire: " << el.first << " " << "Contor: " << el.second << '\n';
    }
}

void UI::undoUI() {
    try {
        serviceCRUD.undo();
        cout << "Undo realizat cu succes!" << std::endl;
    } catch (UndoException& e) {
        cout << e;
        return;
    }
}
