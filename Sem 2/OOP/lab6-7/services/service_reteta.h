//
// Created by calin on 22.04.2023.
//

#pragma once
#include "../repository/reteta.h"

class ServiceReteta {
private:
    Reteta& reteta;

public:

    explicit ServiceReteta(Reteta& r) : reteta{r} {

    }

    ServiceReteta(const ServiceReteta& s) = delete;


    void addMedicament(const string& denumire);

    void golesteReteta() noexcept;

    void genereazaMedicamente(int nrMedicamente) noexcept;

    int nrMedicamenteReteta() const noexcept;

    const vector<Medicament>& getReteta() const noexcept;
};
