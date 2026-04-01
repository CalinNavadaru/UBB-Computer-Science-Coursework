//
// Created by calin on 03.06.2023.
//

#pragma once
#include <QAbstractTableModel>
#include "../services/service_reteta.h"

class ModelTable : public QAbstractListModel {
private:
    ServiceReteta& reteta;
public:
    explicit ModelTable(QObject* parent, ServiceReteta& reteta) : QAbstractListModel{parent}, reteta{reteta} {

    }

    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void notifica() {
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }
};

