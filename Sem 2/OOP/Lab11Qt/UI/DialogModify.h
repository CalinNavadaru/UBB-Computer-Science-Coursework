//
// Created by calin on 14.05.2023.
//

#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class DialogModify : public QDialog{
private:
    QLineEdit *denumire{}, *producator{}, *substantaActiva{}, *pret{}, *indice{};
    QLabel *l1{}, *l2{}, *l3{}, *l4{}, *l5{};
    QVBoxLayout* layoutDialog{};
    QDialogButtonBox* btnBox{};


    void initButtons();

    void initLayout();

public:

    DialogModify() : QDialog{} {
        initButtons();
        initLayout();
        setLayout(layoutDialog);
    }

    [[nodiscard]] std::string getDenumire() const {
        return denumire->text().toStdString();
    }

    [[nodiscard]] std::string getProducator() const {
        return producator->text().toStdString();
    }

    [[nodiscard]] std::string getSubstantaActiva() const {
        return substantaActiva->text().toStdString();
    }

    [[nodiscard]] int getPret() const {
        return pret->text().toInt();
    }

    [[nodiscard]] int getIndice() const {
        return indice->text().toInt();
    }
};
