//
// Created by calin on 16.05.2023.
//

#include "WindowAfisare.h"

void WindowAfisare::initLayout() {
    layout = new QHBoxLayout{};
    lista = new QListWidget{};
    int i = 1;
    for (const auto& e: listaElemente) {
        auto *p = new QListWidgetItem{QString{(QString::number(i, 10).toStdString() + ". " +
                                               e.getDenumire() + " " + e.getProducator() + " " + e.getSubstantaActiva() +
                                               " " + QString::number(e.getPret(), 'g', 10).toStdString()).c_str()}};

        i++;
        lista->addItem(p);
    }
    layout->addWidget(lista);
    layout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
}
