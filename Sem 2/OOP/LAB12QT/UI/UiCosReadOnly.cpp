//
// Created by calin on 29.05.2023.
//

#include "UiCosReadOnly.h"

void UiCosReadOnly::initCmps() {
    tabel = new QTableWidget{10, 4};
    tabel->setFixedSize(800, 600);
}

void UiCosReadOnly::initLayout() {
    layout = new QHBoxLayout{};
    layout->addWidget(tabel);
    layout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
}

void UiCosReadOnly::loadData() {
    tabel->clear();
    auto reteta = ui.getReteta();
    auto medicamente = reteta->getReteta();
    int lungime = reteta->nrMedicamenteReteta();
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
        k++;
        i++;
    }
}

void UiCosReadOnly::paintEvent(QPaintEvent* ev) {
    QPainter p{ this };
    int l = (int) reteta.nrMedicamenteReteta();
    for (int i = 0; i < l; i++) {
        p.drawLine(0 + i + 500, i * 100 + 100, width(), height());
    }
}