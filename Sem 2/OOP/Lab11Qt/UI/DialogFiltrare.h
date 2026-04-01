//
// Created by calin on 25.05.2023.
//

#pragma once
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <string>
#include <utility>

using std::string;
class DialogFiltrare : public QDialog {
private:
    string labelStr;
    QLabel* label{};
    QLineEdit* linie{};
    QDialogButtonBox* btnBox{};
    QVBoxLayout* layout{};

    void initComponents();

    void initLayout();

    void connectBtn();
public:
    explicit DialogFiltrare(string labelStr) : QDialog{}, labelStr{std::move(labelStr)} {
        initComponents();
        initLayout();
        connectBtn();
    }

    [[nodiscard]] QString getText() const {
        return linie->text();
    }
};
