//
// Created by calin on 22.04.2023.
//

#include "service_reteta.h"

void ServiceReteta::addMedicament(const string& denumire) {
    Medicament m;
    try {
        m = r.cautaMedicamentDenumire(denumire);


    } catch (RepositoryException& e) {
        throw RetetaException("Nu exista un medicament cu denumirea oferita!");
    }
    reteta.adauga(m);
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

void ServiceReteta::scrieInFisier(const string &numeFisier) const {
    auto vectorMedicamente = getReteta();
    RetetaRepo t(numeFisier);
    t.scrieInFisier(vectorMedicamente);
}


