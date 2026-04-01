//
// Created by calin on 07.05.2023.
//

#include "UI.h"
#include "DialogAdd.h"
#include "DialogDelete.h"
#include "DialogModify.h"
#include "UIGenerare.h"
#include "../exceptions/exceptions.h"

void UI::initButtons() {
    AddButton = new QPushButton("Adauga");
    DeleteButton = new QPushButton("Sterge");
    ModifyButton = new QPushButton("Modifica");
    SearchButton = new QPushButton("Cautare");
    StatisticsBtn = new QPushButton("Buton Generare");
}

void UI::initLayoutBtn() {
    initButtons();
    layoutBtn = new QVBoxLayout();
    layoutBtn->addWidget(AddButton);
    layoutBtn->addWidget(DeleteButton);
    layoutBtn->addWidget(ModifyButton);
    layoutBtn->addWidget(SearchButton);
    layoutBtn->addWidget(StatisticsBtn);
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

    connect(StatisticsBtn, &QPushButton::clicked, [this]() {
        auto* window = new UIGenerare{serviceCRUD};
        window->show();
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
