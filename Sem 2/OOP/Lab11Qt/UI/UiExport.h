//
// Created by calin on 27.05.2023.
//

#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <string>

using std::string;

class DialogExport: public QDialog{
private:
    QLineEdit *indice{};
    QLabel *l1{};
    QVBoxLayout* layoutDialog{};
    QDialogButtonBox *btnBox{};

    void initDialog();

    void initLabels();

    void initLineEdit();
public:
    DialogExport() : QDialog{} {
        initDialog();
        this->setLayout(layoutDialog);
    }

    [[nodiscard]] string getPath() const {
        return indice->text().toStdString();
    }
};