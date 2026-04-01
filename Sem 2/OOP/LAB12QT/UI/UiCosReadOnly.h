//
// Created by calin on 29.05.2023.
//

#pragma once
#include <QWidget>
#include "Observer.h"
#include "../services/service_reteta.h"
#include <vector>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPainter>
#include "UI.h"

using std::vector;

class UiCosReadOnly : public QWidget , public Observer {
private:
    ServiceReteta& reteta;
    QTableWidget* tabel{};
    QHBoxLayout* layout{};
    int k = 0;

    void initCmps();

    void initLayout();

    void loadData();


public:

    explicit UiCosReadOnly(ServiceReteta& r): QWidget{}, Observer{}, reteta{r}{
        //setAttribute(Qt::WA_DeleteOnClose);
        initCmps();
        initLayout();
        this->setLayout(layout);
        loadData();
        setAutoFillBackground(true);
        setAttribute(Qt::WA_DeleteOnClose);
    }

    void update() override {
        loadData();
        this->repaint();
    }

    void paintEvent(QPaintEvent* ev) override;

};

