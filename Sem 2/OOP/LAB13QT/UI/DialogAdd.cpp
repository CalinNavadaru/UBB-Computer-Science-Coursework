//
// Created by calin on 13.05.2023.
//

#include "DialogAdd.h"

void DialogAdd::initLabels() {
    l1 = new QLabel{"Denumire:"};
    l2 = new QLabel{"Producator:"};
    l3 = new QLabel{"Substanta activa:"};
    l4 = new QLabel{"Pret:"};
}

void DialogAdd::initDialog() {
    layoutDialog = new QVBoxLayout{};

    auto* layout1 = new QHBoxLayout{};
    auto* layout2 = new QHBoxLayout{};
    auto* layout3 = new QHBoxLayout{};
    auto* layout4 = new QHBoxLayout{};

    btnBox = new QDialogButtonBox{QDialogButtonBox::Ok | QDialogButtonBox::Cancel};
    btnBox->setOrientation(Qt::Orientation{Qt::Horizontal});
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this ,&QDialog::reject);
    initLabels();
    initLineEdit();
    layout1->addWidget(l1, 0, Qt::AlignLeft);
    layout1->addWidget(denumire, 0, Qt::AlignLeft);

    layout2->addWidget(l2, 0, Qt::AlignLeft);
    layout2->addWidget(producator, 0, Qt::AlignLeft);

    layout3->addWidget(l3, 0, Qt::AlignLeft);
    layout3->addWidget(substantaActiva, 0, Qt::AlignLeft);

    layout4->addWidget(l4, 0, Qt::AlignLeft);
    layout4->addWidget(pret, 0, Qt::AlignLeft);

    layoutDialog->addLayout(layout1);
    layoutDialog->addLayout(layout2);
    layoutDialog->addLayout(layout3);
    layoutDialog->addLayout(layout4);
    layoutDialog->addWidget(btnBox);
    layoutDialog->setSpacing(10);
    layoutDialog->setAlignment(Qt::AlignVCenter);
}

void DialogAdd::initLineEdit() {
    denumire = new QLineEdit();
    producator = new QLineEdit();
    substantaActiva = new QLineEdit();
    pret = new QLineEdit();
}
