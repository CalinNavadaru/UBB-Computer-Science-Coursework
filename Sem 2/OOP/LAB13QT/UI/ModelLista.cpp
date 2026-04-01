//
// Created by calin on 03.06.2023.
//

#include <QFont>
#include "ModelLista.h"

int ModelLista::rowCount(const QModelIndex &parent) const {
    return (int)s.getMedicamente().size();
}

int ModelLista::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ModelLista::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto indice = index.row();
        auto element = s.getMedicament(indice);
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


