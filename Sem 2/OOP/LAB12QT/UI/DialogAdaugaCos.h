//
// Created by calin on 14.05.2023.
//

#pragma once

#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QDialog>

class DialogAdaugaCos: public QDialog{
private:
    QLineEdit *indice{};
    QLabel *l1{};
    QVBoxLayout* layoutDialog{};
    QDialogButtonBox *btnBox{};

    void initDialog();

    void initLabels();

    void initLineEdit();
public:
    DialogAdaugaCos() : QDialog{} {
        initDialog();
        this->setLayout(layoutDialog);
    }

    [[nodiscard]] int getIndice() const {
        return indice->text().toInt();
    }
};

