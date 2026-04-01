//
// Created by calin on 22.04.2023.
//

#include "service_reteta.h"

void ServiceReteta::addMedicament(const string& denumire) {
    reteta.adauga(denumire);
}

void ServiceReteta::golesteReteta() noexcept {
    reteta.goleste();
}

void ServiceReteta::genereazaMedicamente(int nrMedicamente) noexcept {
    reteta.genereaza(nrMedicamente);
}

int ServiceReteta::nrMedicamenteReteta() const noexcept {
    return reteta.nrMedicamente();
}

const vector<Medicament> &ServiceReteta::getReteta() const noexcept {
    return reteta.getReteta();
}


