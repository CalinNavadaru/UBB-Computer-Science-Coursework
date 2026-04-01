//
// Created by calin on 27.05.2023.
//
#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../services/service_reteta.h"
#include "UiExport.h"
#include "DialogFiltrare.h"

class UiCos : public QWidget{
private:
    ServiceReteta& reteta;

    QTableWidget *tabel{};
    QHBoxLayout *layout{};
    QVBoxLayout *layoutBtns{};
    QPushButton *clearBtn, *generateBtn{}, *ExportBtn{};
    QLabel *counter{};

    void initCmps();

    void initLayout();

    void connectBtns();

    void loadData();

public:

    explicit UiCos(ServiceReteta& r) : QWidget{}, reteta{r} {
        initCmps();
        initLayout();
        this->setLayout(layout);
        loadData();
        connectBtns();
    }
};
