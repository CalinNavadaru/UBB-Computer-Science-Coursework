//
// Created by calin on 21.04.2023.
//

#include "service_statistics.h"

vector<Medicament> ServiceStatistics::filtrareMedicamentePret(int pret) const {
    vector<Medicament> rezFiltrare;
    auto v = repo.getMedicamente();
    for (const auto& el: v) {
        if (el.getPret() == pret)
            rezFiltrare.push_back(el);
    }
    return rezFiltrare;
}

vector<Medicament> ServiceStatistics::filtrareMedicamenteSubstantaActiva(const string& subst) const {
    vector<Medicament> rezFiltrare;
    auto v = repo.getMedicamente();
    for (const auto &el: v) {
        if (el.getSubstantaActiva() == subst)
            rezFiltrare.push_back(el);
    }
    return rezFiltrare;
}
vector<Medicament>
ServiceStatistics::sortareMedicamenteProducatorPret(const std::function<bool(const Medicament &, const Medicament &)>& f) {
    auto v = repo.getMedicamente();

    using std::swap;
    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++)
            if (f(v.at(i), v.at(j)))
                repo.interschimbareMedicamente(i, j);

    return v;
}