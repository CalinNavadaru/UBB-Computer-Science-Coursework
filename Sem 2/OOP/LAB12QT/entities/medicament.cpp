//
// Created by calin on 01.04.2023.
//

#include "medicament.h"

#include <utility>

std::atomic<int> Medicament::nrId;

string Medicament::getDenumire() const {
    return this->denumire;
}

string Medicament::getSubstantaActiva() const {
    return this->substantaActiva;
}

string Medicament::getProducator() const {
    return this->producator;
}

double Medicament::getPret() const {
    return this->pret;
}

int Medicament::getId() const {
    return this->id;
}

void Medicament::setDenumire(std::string denumireNoua) {
    this->denumire = std::move(denumireNoua);
}

void Medicament::setPret(double pretNou) {
    this->pret = pretNou;
}

void Medicament::setProducator(std::string producatorNou) {
    this->producator = std::move(producatorNou);
}

void Medicament::setSubstantaActiva(std::string substantaActivaNoua) {
    this->substantaActiva = std::move(substantaActivaNoua);
}

bool Medicament::operator==(const Medicament &m) const {
    return this->getPret() == m.getPret() && this->getDenumire() == m.getDenumire() && this->getProducator() == m.producator &&
            this->getSubstantaActiva() == m.getSubstantaActiva();
}

bool eq(const Medicament& m1, const Medicament& m2) {
    return m1.getPret() == m2.getPret() && m1.getSubstantaActiva() == m2.getSubstantaActiva() && m1.getProducator() == \
        m2.getProducator() && m1.getDenumire() == m2.getDenumire();
}

