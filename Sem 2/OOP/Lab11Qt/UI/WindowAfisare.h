//
// Created by calin on 16.05.2023.
//

#pragma once
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <vector>
#include "../entities/medicament.h"

using std::vector;

class WindowAfisare : public QWidget {
private:
    QListWidget* lista{};
    QHBoxLayout* layout{};
    vector<Medicament> listaElemente;

    void initLayout();
public:
    WindowAfisare(vector<Medicament> v) : QWidget{}, listaElemente{std::move(v)} {
        initLayout();
        this->setLayout(layout);
    }
};
