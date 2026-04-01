//
// Created by calin on 13.05.2023.
//

#pragma once
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class DialogAdd : public QDialog{
private:
    QLineEdit *denumire{}, *producator{}, *substantaActiva{}, *pret{};
    QLabel *l1{}, *l2{}, *l3{}, *l4{};
    QVBoxLayout* layoutDialog{};
    QDialogButtonBox *btnBox{};

    void initDialog();

    void initLabels();

    void initLineEdit();
public:

    DialogAdd() : QDialog() {
        initDialog();
        this->setLayout(layoutDialog);
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
};

