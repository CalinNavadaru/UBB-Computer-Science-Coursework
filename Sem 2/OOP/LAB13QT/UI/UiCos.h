//
// Created by calin on 27.05.2023.
//
#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include "../services/service_reteta.h"
#include "UiExport.h"
#include "DialogFiltrare.h"
#include "Observer.h"
#include "UI.h"

class UiCos : public QWidget, public Observer {
private:
    UI& ui;
    QListView* tabel{};
    ModelTable* modelTable;
    //QTableWidget *tabel{};
    QHBoxLayout *layout{};
    QVBoxLayout *layoutBtns{};
    QPushButton *clearBtn{}, *generateBtn{}, *ExportBtn{};
    QLabel *counter{};

    void initCmps();

    void initLayout();

    void connectBtns();

    void loadData();

//    void update() override {
////        loadData();
//        modelTable->notifica();
//        this->counter->setText("Nr. de medicaemnte: " + QString::number(ui.getReteta()->nrMedicamenteReteta()));
//        this->tabel->viewport()->update();
//    };
protected:
    void update() override {
//        loadData();
        modelTable->notifica();
        this->counter->setText("Nr. de medicaemnte: " + QString::number(ui.getReteta()->nrMedicamenteReteta()));
        this->tabel->viewport()->repaint();
    };
public:

    explicit UiCos(UI& ui, ModelTable* t) : QWidget{}, ui{ui}, modelTable{t}{
        initCmps();
        initLayout();
        this->setLayout(layout);
        connectBtns();
        setAttribute(Qt::WA_DeleteOnClose);
    }

    ~UiCos() override {
        ui.eliminaObservator(this);
    }

};
