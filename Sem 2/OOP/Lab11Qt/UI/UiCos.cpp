//
// Created by calin on 27.05.2023.
//

#include <QMessageBox>
#include "UiCos.h"
#include "../services/service_validateInput.h"

void UiCos::initCmps() {
    this->ExportBtn = new QPushButton{"Exporta"};
    this->clearBtn = new QPushButton{"Goleste"};
    this->generateBtn = new QPushButton{"Genereaza"};
    this->tabel = new QTableWidget{10, 4};
    this->counter = new QLabel{};
}

void UiCos::initLayout() {
    this->layoutBtns = new QVBoxLayout{};
    layoutBtns->addWidget(generateBtn);
    layoutBtns->addWidget(clearBtn);
    layoutBtns->addWidget(ExportBtn);
    layoutBtns->addWidget(counter);
    layoutBtns->setAlignment(Qt::AlignmentFlag::AlignVCenter);

    this->layout = new QHBoxLayout{};
    layout->addWidget(tabel);
    layout->addLayout(layoutBtns);
    layout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
}

void UiCos::connectBtns() {
    connect(clearBtn, &QPushButton::clicked, [this](){
        tabel->clear();
        reteta.golesteReteta();
        counter->setText("Nr. de medicaemnte: " + QString::number(reteta.nrMedicamenteReteta()));
    });

    connect(generateBtn, &QPushButton::clicked, [this](){
        auto inputWindow = new DialogFiltrare{"Nr medicamente: "};
        if (inputWindow->exec()) {
            int nrMedicamente = inputWindow->getText().toInt();
            try {
                if (nrMedicamente <= 0 || nrMedicamente > reteta.nrMedicamenteReteta())
                    throw InputException("Nr de medicamente invalid!");
            } catch (InputException& e) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Eraore la generare"});
                windowEroare->setText( QString{e.getMsg().c_str()});
                return windowEroare->exec();
            }
            reteta.genereazaMedicamente(nrMedicamente);
            loadData();
        }

    });

    connect(ExportBtn, &QPushButton::clicked, [this](){
        auto exportWindow = new DialogExport{};
        if (exportWindow->exec()) {
            string path;
            path = exportWindow->getPath();
            if (path.size() == 0) {
                auto *windowEroare = new QMessageBox{};
                windowEroare->setWindowTitle(QString{"Eraore la export"});
                windowEroare->setText( QString{"Nu se poate crea acest fisier"});
                return windowEroare->exec();
            }
            reteta.scrieInFisier(path);
        }
    });
}

void UiCos::loadData() {
    tabel->clear();
    auto medicamente = reteta.getReteta();
    int lungime = reteta.nrMedicamenteReteta();
    tabel->setRowCount(std::max(lungime, tabel->rowCount()));
    int i = 0;
    for (const auto& e: medicamente) {
        auto *denumire = new QTableWidgetItem{QString::fromStdString(e.getDenumire())};
        auto *producator = new QTableWidgetItem{QString::fromStdString(e.getProducator())};
        auto *substantaActiva = new QTableWidgetItem{QString::fromStdString(e.getSubstantaActiva())};
        auto *pret = new QTableWidgetItem{QString::number(e.getPret(), 'g', 10).toStdString().c_str()};
        tabel->setItem(i, 0, denumire);
        tabel->setItem(i, 1, producator);
        tabel->setItem(i, 2, substantaActiva);
        tabel->setItem(i, 3, pret);
        i++;
    }
    counter->setText("Nr. de medicaemnte: " + QString::number(medicamente.size()));
}
