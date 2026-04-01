//
// Created by calin on 01.04.2023.
//

#include "service_crud.h"

#include <utility>

const vector<Medicament>& ServiceCRUD::getMedicamente() const {
    return this->repo.getMedicamente();
}

int ServiceCRUD::adaugareMedicament(string denumire, string producator, string substantaActiva, double pret) {
    Medicament m(std::move(denumire), std::move(producator), std::move(substantaActiva), pret);
    return this->repo.adaugareMedicament(m);
}

int ServiceCRUD::modificareMedicament(string denumire, string producator, string substantaActiva, double pret, int index) {
    Medicament m(std::move(denumire), std::move(producator), std::move(substantaActiva), pret);
    return this->repo.modificareMedicament(m, index);
}

int ServiceCRUD::stergereMedicament(int index) noexcept{
    return this->repo.stergereMedicament(index);
}

const Medicament &ServiceCRUD::getMedicament(int index) const {
    return this->repo.getMedicament(index);
}

const Medicament& ServiceCRUD::cautaMedicament(const string &denumire, const string &producator, const string &substantaActiva,
                             double pret) const {
    return this->repo.cautaMedicament(denumire, producator, substantaActiva, pret);
}

const map<string, int> &ServiceCRUD::getContorService() const noexcept {
    return repo.getContor();
}

void ServiceCRUD::undo() {
    repo.undo();
}







