//
// Created by calin on 25.05.2023.
//

#include "DialogFiltrare.h"

void DialogFiltrare::initComponents() {
    label = new QLabel{labelStr.c_str()};
    linie = new QLineEdit{};
    this->btnBox = new QDialogButtonBox{QDialogButtonBox::Cancel | QDialogButtonBox::Ok};
    this->btnBox->setOrientation(Qt::Orientation{Qt::Horizontal});
}

void DialogFiltrare::initLayout() {
    layout = new QVBoxLayout{};
    layout->addWidget(label);
    layout->addWidget(linie);
    layout->addWidget(btnBox);
    layout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->setLayout(layout);
}

void DialogFiltrare::connectBtn() {
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this ,&QDialog::reject);
}
