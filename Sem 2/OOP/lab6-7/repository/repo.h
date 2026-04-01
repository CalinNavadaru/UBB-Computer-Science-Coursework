//
// Created by calin on 01.04.2023.
//

#pragma once
#include "../entities/medicament.h"
#include "../exceptions/exceptions.h"
#include "../../lab6-7 (copy)/vectordinamic.h"
#include <algorithm>
#include <map>


using std::vector;
using std::find_if;
using std::map;

class Repository {

private:
    vector<Medicament> medicamente;

    std::map<string, int> contor;

    bool existAlready(const Medicament& m) const;


public:

    Repository() = default;

    Repository(const Repository& ot) = delete;

    int getNrMedicamente() const;

    const vector<Medicament>& getMedicamente() const;

    int adaugareMedicament(const Medicament& m);

    int modificareMedicament(const Medicament& m, int index);

    int stergereMedicament(int index);

    const Medicament& cautaMedicament(const string& denumire, const string& producator, const string& substantaActiva, double pret) const;

    const Medicament& cautaMedicamentDenumire(const string& denumire) const;

    const Medicament& getMedicament(int index) const;

    void interschimbareMedicamente(int i, int j);

    const map<string, int>& getContor() const noexcept;
};
