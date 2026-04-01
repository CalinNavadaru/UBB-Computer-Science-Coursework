//
// Created by calin on 03.06.2023.
//

#include "ModelWindowAfisare.h"
#include <QFont>

int ModelWIndowAfisare::rowCount(const QModelIndex &parent) const {
    return (int) v.size();
}

int ModelWIndowAfisare::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ModelWIndowAfisare::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto indice = index.row();
        auto element = v.at(indice);
        return QString{QString::fromStdString(element.getDenumire() + " " + element.getProducator() + " " + element.getSubstantaActiva() +
                                              " ") + QString::number(element.getPret(), 'g', 10)};
    }
    else if(role == Qt::FontRole) {
        QFont f;
        f.setBold(false);
        return f;
    }
    return QVariant{};
}
