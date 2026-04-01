//
// Created by calin on 07.05.2023.
//

#include <QFormLayout>
#include "UI.h"
#include "DialogAdd.h"
#include "DialogDelete.h"
#include "DialogModify.h"
#include "UIGenerare.h"
#include "WindowAfisare.h"
#include "DialogFiltrare.h"
#include "DialogAdaugaCos.h"
#include "UiCos.h"
#include "UiCosReadOnly.h"

void UI::initButtons() {
    AddButton = new QPushButton("Adauga");
    DeleteButton = new QPushButton("Sterge");
    ModifyButton = new QPushButton("Modifica");
    SearchButton = new QPushButton("Cautare");
    StatisticsBtn = new QPushButton("Buton Generare");
    UndoButton = new QPushButton("Undo");
    SortButtonPret = new QPushButton("Sort Pret");
    FiltrarePret = new QPushButton("Filtrare pret");
    FiltrareSubstActiva = new QPushButton("Filtrare subst activa");
    AdaugaCos = new QPushButton("Adauga in cos!");
    VeziCos = new QPushButton("Vezi cos!");
    VeziCosReadOnly = new QPushButton("Vezi cos read only!");
    golesteCos = new QPushButton("Goleste Cos");
    genereazaCos = new QPushButton("GenereazaCos");
}

void UI::initLayoutBtn() {
    initButtons();
    layoutBtn = new QVBoxLayout();
    layoutBtn->addWidget(AddButton);
    layoutBtn->addWidget(DeleteButton);
    layoutBtn->addWidget(ModifyButton);
    layoutBtn->addWidget(SearchButton);
    layoutBtn->addWidget(StatisticsBtn);
    layoutBtn->addWidget(UndoButton);
    layoutBtn->addWidget(SortButtonPret);
    layoutBtn->addWidget(FiltrarePret);
    layoutBtn->addWidget(FiltrareSubstActiva);
    layoutBtn->addWidget(AdaugaCos);
    layoutBtn->addWidget(VeziCos);
    layoutBtn->addWidget(VeziCosReadOnly);
    layoutBtn->addWidget(golesteCos);
    layoutBtn->addWidget(genereazaCos);
    layoutBtn->setAlignment(Qt::AlignVCenter);
}

void UI::initLayout() {
    layoutPrincipal = new QHBoxLayout{};
    layoutTable = new QHBoxLayout{};
    lista = new QListWidget{};
    layoutTable->addWidget(lista);
    layoutPrincipal->addLayout(layoutTable, 0);
    layoutPrincipal->addLayout(layoutBtn, 0);

}

void UI::connectBtns() {
    connect(AddButton, &QPushButton::clicked ,[this](){
        refresh();
        auto *inputDialog = new DialogAdd{};
        if ( inputDialog->exec() ) {
            string denumire, producator, substantaActiva;
            int pret;

            denumire = inputDialog->getDenumire();
            producator = inputDialog->getProducator();
            substantaActiva = inputDialog->getSubstantaActiva();
            pret = inputDialog->getPret();

            InputValidator v(denumire, producator, substantaActiva, pret, -1, this->serviceCRUD);
            try {
                v.validareAdaugare();
            } catch (InputValidationException &e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Date invalide"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            } catch (RepositoryException &e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Date invalide"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }
            try {
                serviceCRUD.adaugareMedicament(denumire, producator, substantaActiva, pret);

            }catch (RepositoryException &e) {
                    auto *windowEroare = new QMessageBox{};
                    windowEroare->setWindowTitle(QString{"Producator deja existent!"});
                    windowEroare->setText( QString{e.getMsg().c_str()});
                    return windowEroare->exec();
                }
            refresh();
        }
    });

    connect(DeleteButton, &QPushButton::clicked, [this](){
        refresh();
        auto* inputDelete = new DialogDelete{};
        if (inputDelete->exec()) {
            int indiceInput = inputDelete->getIndice();
            InputValidator v("", "", "", -1, indiceInput, serviceCRUD);
            try {
                v.validareStergere();
            } catch (InputValidationException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Date invalide"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }

            serviceCRUD.stergereMedicament(indiceInput - 1);
            refresh();
        }
    });

    connect(ModifyButton, &QPushButton::clicked, [this]() {
        refresh();
        auto *inputDialog = new DialogModify{};
        if ( inputDialog->exec() ) {
            string denumire, producator, substantaActiva;
            int pret, indice;

            denumire = inputDialog->getDenumire();
            producator = inputDialog->getProducator();
            substantaActiva = inputDialog->getSubstantaActiva();
            pret = inputDialog->getPret();
            indice = inputDialog->getIndice();

            InputValidator v(denumire, producator, substantaActiva, pret, indice, this->serviceCRUD);
            try {
                v.validareModicare();
            } catch (InputValidationException &e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Date invalide"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }

            serviceCRUD.modificareMedicament(denumire, producator, substantaActiva, pret, indice - 1);
            refresh();
        }
    });

    connect(SearchButton, &QPushButton::clicked, [this](){
        int x;
        auto* inputDialog = new DialogAdd{};
        if (inputDialog->exec()) {
            string denumire, producator, substantaActiva;
            int pret;

            denumire = inputDialog->getDenumire();
            producator = inputDialog->getProducator();
            substantaActiva = inputDialog->getSubstantaActiva();
            pret = inputDialog->getPret();
            try {
                x = serviceCRUD.cautaMedicamentIndice(denumire, producator, substantaActiva, pret);
            } catch(RepositoryException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Date invalide"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }
            this->lista->item(x)->setBackground(Qt::blue);
        }

    });

    connect(FiltrarePret, &QPushButton::clicked, [this](){
        int pret;
        auto inputWindow = new DialogFiltrare{"Pret"};
        if (inputWindow->exec()) {

            try {
                pret = inputWindow->getText().toInt();
                if (pret <= 0)
                    throw InputException("Pret invalid!");
            } catch(InputException& e) {
                QMessageBox::information(this,"Eroare!" , QString{e.getMsg().c_str()});
                return;
            }
        }
        auto v = serviceStatistics.filtrareMedicamentePret(pret);
        auto *p = new WindowAfisare{v};
        return p->show();
    });

    connect(FiltrareSubstActiva, &QPushButton::clicked, [this](){
        string input;
        auto inputWindow = new DialogFiltrare{"Substanta Activa"};
        if (inputWindow->exec()) {

            try {
                input = inputWindow->getText().toStdString();
                if (input.empty())
                    throw InputException("Substanta invalida!");
            } catch(InputException& e) {
                QMessageBox::information(this,"Eroare!" , QString{e.getMsg().c_str()});
                return;
            }
        }
        auto v = serviceStatistics.filtrareMedicamenteSubstantaActiva(input);
        auto *p = new WindowAfisare{v};
        return p->show();
    });

    connect(StatisticsBtn, &QPushButton::clicked, [this]() {
        auto* window = new UIGenerare{serviceCRUD};
        return window->show();
    });


    connect(UndoButton, &QPushButton::clicked, [this]() {
        try {
            serviceCRUD.undo();
        } catch (UndoException& e) {
            auto *windowEroare = new QMessageBox{};
            windowEroare->setWindowTitle(QString{"Undo"});
            windowEroare->setText( QString{e.getMsg().c_str()});
            return windowEroare->exec();
        }
        refresh();
    });

    connect(SortButtonPret, &QPushButton::clicked, [this]() {
       auto v = serviceStatistics.sortareMedicamenteProducatorPret([](const Medicament& m1, const Medicament& m2) {
           bool cond1 = m1.getDenumire() < m2.getDenumire();
           bool cond2 = m1.getDenumire() == m2.getDenumire() && m1.getProducator() < m2.getProducator();
           bool cond3 = m1.getDenumire() == m2.getDenumire() && m1.getProducator() == m2.getProducator() && m1.getSubstantaActiva() < m2.getSubstantaActiva();
           return cond1 || cond2 || cond3;
       });

       auto *p = new WindowAfisare{v};
       return p->show();
    });

    connect(AdaugaCos, &QPushButton::clicked, [this](){
        auto inputWindow = new DialogAdaugaCos{};
        if (inputWindow->exec()) {
            auto valoare = inputWindow->getIndice();
            auto validator = InputValidator{"", "", "", -1, valoare, serviceCRUD};
            try {
                validator.validareStergere();
                auto denumire = serviceCRUD.getMedicament(valoare - 1).getDenumire();
                serviceReteta.addMedicament(denumire);
            } catch (RepositoryException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Adaugare in cos!"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            } catch (InputValidationException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Adaugare in cos!"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }
        }
    });

    connect(VeziCos, &QPushButton::clicked, [this](){
        auto cosWindow = new UiCos{*this};
        adaugaObservator(cosWindow);
        cosCRUDVector.push_back(cosWindow);
        for (int i = 0; i < cosCRUDVector.size() - 1; i++) {
            cosCRUDVector.at(i)->adaugaObservator(cosWindow);
        }
        for (int i = 0; i < cosCRUDVector.size() - 1; i++) {
            cosCRUDVector.at(cosCRUDVector.size() - 1)->adaugaObservator((Observer*)cosCRUDVector.at(i));
        }
            cosWindow->show();
    });

    connect(VeziCosReadOnly, &QPushButton::clicked, [this](){
        auto cosWindow = new UiCosReadOnly{*this, cosCRUDVector};
        adaugaObservator(cosWindow);
        for (int i = 0; i < (int) cosCRUDVector.size(); i++) {
            cosCRUDVector.at(i)->adaugaObservator(cosWindow);
        }
        cosWindow->show();
    });

    connect(golesteCos, &QPushButton::clicked, [this](){
        serviceReteta.golesteReteta();
        notifica();
    });

    connect(genereazaCos, &QPushButton::clicked, [this](){
        auto inputWindow = new DialogFiltrare{"Nr medicamente: "};
        if (inputWindow->exec()) {
            int nrMedicamente = inputWindow->getText().toInt();
            try {
                if (nrMedicamente <= 0 || nrMedicamente > serviceReteta.nrMedicamenteReteta())
                    throw InputException("Nr de medicamente invalid!");
            } catch (InputException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Eraore la generare"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }
            serviceReteta.genereazaMedicamente(nrMedicamente);
            notifica();
        }
    });
}

void UI::refresh() {
    auto medicamente = serviceCRUD.getMedicamente();
    lista->clear();
    int i = 1;
    for (const auto& e: medicamente) {
        auto *p = new QListWidgetItem{QString{(QString::number(i, 10).toStdString() + ". " +
        e.getDenumire() + " " + e.getProducator() + " " + e.getSubstantaActiva() +
        " " + QString::number(e.getPret(), 'g', 10).toStdString()).c_str()}};
        lista->addItem(p);
        i++;
    }
}
