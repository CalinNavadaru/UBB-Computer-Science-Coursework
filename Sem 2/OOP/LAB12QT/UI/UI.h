//
// Created by calin on 07.05.2023.
//

#pragma once
#include "../services/service_validateInput.h"
#include "../services/service_statistics.h"
#include "../services/service_crud.h"
#include "../services/service_reteta.h"
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "Observer.h"

class UI : public QWidget{
private:
    ServiceReteta& serviceReteta;
    ServiceStatistics& serviceStatistics;
    ServiceCRUD& serviceCRUD;

    QPushButton *AddButton{}, *DeleteButton{}, *ModifyButton{},  *SearchButton{}, *StatisticsBtn{};
    QPushButton *UndoButton{}, *SortButtonPret{}, *FiltrarePret{}, *FiltrareSubstActiva{}, *AdaugaCos{}, *VeziCos{};
    QPushButton *VeziCosReadOnly{}, *golesteCos{}, *genereazaCos{};
    QHBoxLayout* layoutPrincipal{}, *layoutTable{};
    QVBoxLayout* layoutBtn{};
    QListWidget* lista{};

    void initLayoutBtn();

    void initButtons();

    void initLayout();

    void connectBtns();

    void refresh();

public:

    UI(ServiceCRUD& s1, ServiceStatistics& s2, ServiceReteta& s3) : QWidget{}, serviceReteta{s3}, serviceStatistics{s2}, serviceCRUD{s1} {
        this->setWindowTitle("Farmacie");
        initLayoutBtn();
        initLayout();
        this->setLayout(layoutPrincipal);
        connectBtns();
        this->show();
    }

    ServiceReteta* getReteta() {
        return &serviceReteta;
    }
};
