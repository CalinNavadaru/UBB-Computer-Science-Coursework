//
// Created by calin on 03.06.2023.
//

#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "../services/service_crud.h"
using std::vector;

class ModelWIndowAfisare : public QAbstractTableModel {
private:

    vector<Medicament>& v;
public:
    explicit ModelWIndowAfisare(QObject* parent, vector<Medicament>& v) : QAbstractTableModel{parent}, v{v} {

    }

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex{}) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //[[nodiscard]] bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    void notifica() {
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }
};



