//
// Created by calin on 21.04.2023.
//

#ifndef LAB6_7_SERVICE_STATISTICS_H
#define LAB6_7_SERVICE_STATISTICS_H

#include "../repository/repo.h"
#include <functional>
#include <algorithm>

using std::string;

class ServiceStatistics {
private:
    Repository& repo;

public:
    explicit ServiceStatistics(Repository& repo): repo{repo} {

    }
    ServiceStatistics(const ServiceStatistics& s) = delete;

    vector<Medicament> filtrareMedicamentePret(int pret) const;

    vector<Medicament> sortareMedicamenteProducatorPret(const std::function<bool(const Medicament& m1, const Medicament& m2)>& f);
};
#endif //LAB6_7_SERVICE_STATISTICS_H
