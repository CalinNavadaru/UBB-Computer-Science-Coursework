//
// Created by calin on 15.05.2023.
//

#include <QMessageBox>
#include "UIGenerare.h"

void UIGenerare::initLayout() {
    layout = new QHBoxLayout{};
    vector<QPushButton*> listBtn;
    auto p = serviceStatistics.getContorService();
    for (const auto& el: p) {
        int ap = el.second;
        auto btn =  new QPushButton{el.first.c_str()};
        listBtn.push_back(btn);
        layout->addWidget(btn);
        connect(listBtn.back(), &QPushButton::clicked, [ap, btn]() {
            auto *window = new QMessageBox{};
            window->setText( QString{"Numarul de aparitii al cartii: "} + btn->text() + QString{" este "} + QString::number(ap));
            window->exec();
        });
    }
    setLayout(layout);
}
