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
#include "../entities/reteta.h"
#include "UiExport.h"
#include "DialogFiltrare.h"
#include "Observer.h"
#include "UI.h"

class UiCos : public QWidget, public Observer {
private:
    Reteta& reteta;

    QTableWidget *tabel{};
    QHBoxLayout *layout{};
    QVBoxLayout *layoutBtns{};
    QPushButton *clearBtn{}, *generateBtn{}, *ExportBtn{};
    QLabel *counter{};

    void initCmps();

    void initLayout();

    void connectBtns();

    void loadData();

    void update() override {
        loadData();
    };

public:

    explicit UiCos(Reteta& r) : QWidget{}, reteta{r}{
        initCmps();
        initLayout();
        this->setLayout(layout);
        loadData();
        connectBtns();
        setAttribute(Qt::WA_DeleteOnClose);
    }

    ~UiCos() override {
        reteta.
    }

};
