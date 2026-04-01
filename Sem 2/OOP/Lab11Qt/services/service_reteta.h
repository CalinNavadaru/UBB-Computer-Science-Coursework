//
// Created by calin on 22.04.2023.
//

#pragma once
#include "../entities/reteta.h"
#include "../repository/reteta_repo.h"

class ServiceReteta {
private:
    Reteta& reteta;
    Repository& r;

public:

    ServiceReteta(Reteta &r, Repository &repo) : reteta{r} , r{repo}{

    }

    ServiceReteta(const ServiceReteta& s) = delete;


    void addMedicament(const string& denumire);

    void golesteReteta() noexcept;

    void genereazaMedicamente(int nrMedicamente) noexcept;

    int nrMedicamenteReteta() const noexcept;

    void scrieInFisier(const string& numeFisier) const;

    const vector<Medicament>& getReteta() const noexcept;
};
