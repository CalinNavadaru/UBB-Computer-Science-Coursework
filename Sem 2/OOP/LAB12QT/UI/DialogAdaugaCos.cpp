//
// Created by calin on 14.05.2023.
//

#include "DialogAdaugaCos.h"

void DialogAdaugaCos::initDialog() {
    initLabels();
    initLineEdit();
    this->btnBox = new QDialogButtonBox{QDialogButtonBox::Cancel | QDialogButtonBox::Ok};
    this->btnBox->setOrientation(Qt::Orientation{Qt::Horizontal});
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this ,&QDialog::reject);
    layoutDialog = new QVBoxLayout{};
    this->layoutDialog->addWidget(l1);
    this->layoutDialog->addWidget(indice);
    this->layoutDialog->addWidget(btnBox);
    this->layoutDialog->setAlignment(Qt::AlignHCenter);
}

void DialogAdaugaCos::initLabels() {
    this->l1 = new QLabel("Indicele medicamentului ce va fi adaugat in cos: ");
}

void DialogAdaugaCos::initLineEdit() {
    this->indice = new QLineEdit{};
}
