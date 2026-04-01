//
// Created by calin on 15.05.2023.
//
#pragma once
#include "../services/service_crud.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class UIGenerare : public QWidget {
private:
    QHBoxLayout* layout{};
    ServiceCRUD& serviceStatistics;
    void initLayout();
public:

    UIGenerare(ServiceCRUD& s) : QWidget{}, serviceStatistics{s} {
        initLayout();
    }
};

