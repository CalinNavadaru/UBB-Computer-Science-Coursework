//
// Created by calin on 14.05.2023.
//

#include "DialogModify.h"

void DialogModify::initButtons() {
    btnBox = new QDialogButtonBox{QDialogButtonBox::Cancel | QDialogButtonBox::Ok};
    btnBox->setOrientation(Qt::Orientation::Horizontal);
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this ,&QDialog::reject);
}

void DialogModify::initLayout() {
    layoutDialog = new QVBoxLayout{};

    l5 = new QLabel{"Indice"};
    indice = new QLineEdit{};

    auto *layout5 = new QHBoxLayout{};
    layout5->addWidget(l5, Qt::AlignLeft);
    layout5->addWidget(indice);
    layout5->setAlignment(Qt::AlignmentFlag::AlignHCenter);


    l1 = new QLabel{"Denumire: "};
    denumire = new QLineEdit{};

    auto *layout1 = new QHBoxLayout{};
    layout1->addWidget(l1, Qt::AlignLeft);
    layout1->addWidget(denumire);
    layout1->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    l2 = new QLabel{"Producator: "};
    producator = new QLineEdit{};

    auto *layout2 = new QHBoxLayout{};
    layout2->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    layout2->addWidget(l2, Qt::AlignLeft);
    layout2->addWidget(producator);

    l3 = new QLabel{"Substanta Activa: "};
    substantaActiva = new QLineEdit{};

    auto *layout3 = new QHBoxLayout{};
    layout3->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    layout3->addWidget(l3, Qt::AlignLeft);
    layout3->addWidget(substantaActiva);

    l4 = new QLabel{"Pret: "};
    pret = new QLineEdit{};

    auto *layout4 = new QHBoxLayout{};
    layout4->addWidget(l4, Qt::AlignLeft);
    layout4->addWidget(pret);
    layout4->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    layoutDialog->addWidget(l4);
    layoutDialog->addWidget(pret);

    layoutDialog->addLayout(layout5, 0);
    layoutDialog->addLayout(layout1, 0);
    layoutDialog->addLayout(layout2, 0);
    layoutDialog->addLayout(layout3, 0);
    layoutDialog->addLayout(layout4, 0);
    layoutDialog->addWidget(btnBox);
    layoutDialog->addSpacing(10);

    layoutDialog->setAlignment(Qt::AlignmentFlag::AlignVCenter);
}
