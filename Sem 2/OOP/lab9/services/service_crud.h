//
// Created by calin on 01.04.2023.
//

#pragma once
#include "../repository/repo.h"
#include <algorithm>

using std::string;

class ServiceCRUD {

private:
        Repository& repo;
public:
    explicit ServiceCRUD(Repository& repo): repo{repo} {

    };
    ServiceCRUD(const ServiceCRUD& other) = delete;

    const vector<Medicament>& getMedicamente() const;

    int adaugareMedicament(string denumire, string producator, string substantaActiva, double pret);

    int modificareMedicament(string denumire, string producator, string substantaActiva, double pret, int index);

    int stergereMedicament(int index) noexcept;

    const Medicament& cautaMedicament(const string& denumire, const string& producator, const string& substantaActiva, double pret) const;

    const Medicament& getMedicament(int index) const;

    const map<string, int>& getContorService() const noexcept;

    void undo();
};
