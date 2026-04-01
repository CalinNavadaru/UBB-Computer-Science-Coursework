//
// Created by calin on 03.06.2023.
//

#include "ModelTable.h"

int ModelTable::rowCount(const QModelIndex &parent) const {
    return (int) reteta.nrMedicamenteReteta();
}

int ModelTable::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ModelTable::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto element = reteta.getReteta().at(index.row());
        return QString{"%1 %2 %3 %4"}.arg(QString::fromStdString(element.getDenumire())).arg(QString::fromStdString(element.getProducator()))
        .arg(QString::fromStdString(element.getSubstantaActiva())).arg(QString::number(element.getPret(), 'g', 10));
    }
    return QVariant{};
}


