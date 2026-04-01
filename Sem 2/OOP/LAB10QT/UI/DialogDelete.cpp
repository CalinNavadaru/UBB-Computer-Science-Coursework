//
// Created by calin on 14.05.2023.
//

#include "DialogDelete.h"

void DialogDelete::initDialog() {
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

void DialogDelete::initLabels() {
    this->l1 = new QLabel("Indicele medicamentului ce trebuie sters: ");
}

void DialogDelete::initLineEdit() {
    this->indice = new QLineEdit{};
}
