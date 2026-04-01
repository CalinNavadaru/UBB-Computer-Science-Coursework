//
// Created by calin on 27.05.2023.
//

#include "UiExport.h"

void DialogExport::initDialog() {
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

void DialogExport::initLabels() {
    this->l1 = new QLabel("Indicele medicamentului ce trebuie sters: ");
}

void DialogExport::initLineEdit() {
    this->indice = new QLineEdit{};
}
