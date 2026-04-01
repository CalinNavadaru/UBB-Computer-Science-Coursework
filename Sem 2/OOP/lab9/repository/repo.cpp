//
// Created by calin on 01.04.2023.
//

#include "repo.h"

int Repository::getNrMedicamente() const {
    return (int)this->medicamente.size();
}

const vector<Medicament>& Repository::getMedicamente() const {
    return this->medicamente;
}

bool Repository::existAlready(const Medicament& m) const {
    auto v = find_if(medicamente.cbegin(), medicamente.cend(), [&m](const Medicament& medicament) {
        return m.getDenumire() == medicament.getDenumire();
    });

    return v != medicamente.cend();
}

int Repository::adaugareMedicament(const Medicament &m) {
    if (existAlready(m))
        throw (RepositoryException("Medicamentul exista deja!"));

    this->medicamente.push_back(m);
    vectorUndo.push_back(std::make_unique<AdaugareUndo>(AdaugareUndo{(int) medicamente.size() - 1, *this}));
    auto v = contor.find(m.getProducator());
    if (v != contor.end()) {
        v->second++;
    } else {
        contor.insert(std::make_pair(m.getProducator(), 1));
    }
    return 0;
}

int Repository::modificareMedicament(const Medicament& m, int index) {
    //this->medicamente[index] = m;
    auto v = contor.find(m.getProducator());
    v->second--;
    vectorUndo.push_back(std::make_unique<ModificareUndo>(ModificareUndo{this->medicamente[index], index, *this}));
    this->medicamente[index] = m;
    v = contor.find(m.getProducator());
    v->second++;
    return 0;
}

int Repository::stergereMedicament(int index) {

    auto v = contor.find(this->medicamente[index].getProducator());
    v->second--;
    vectorUndo.push_back(std::make_unique<StergereUndo>(StergereUndo{this->medicamente[index], *this}));
//    vectorUndo.push_back();
    if (index < this->medicamente.size()) {
    for (int i = index; i < this->medicamente.size() - 1; i++)
        //this->medicamente.set(i, this->medicamente.get(i+1));
        this->medicamente[i] = this->medicamente[i + 1];
    }
    this->medicamente.pop_back();
    return 0;
}

const Medicament& Repository::cautaMedicament(const string &denumire, const string &producator, const string &substantaActiva, double pret) const {

    auto v = find_if(this->medicamente.cbegin(), medicamente.cend(), [&](const Medicament& v) {
        return v.getPret() == pret && v.getProducator() == producator && v.getSubstantaActiva() == substantaActiva &&
               v.getDenumire() == denumire;
    });
    if (v == medicamente.cend())
        throw RepositoryException("Medicamentul cautat nu exista!");

    return v.operator*();
}

const Medicament& Repository::getMedicament(int index) const {
    return this->medicamente.at(index);
}

void Repository::interschimbareMedicamente(int i, int j) {
    Medicament aux;
    aux = medicamente.at(i);
    medicamente[i] = medicamente.at(j);
    medicamente[j] = aux;
}

const Medicament& Repository::cautaMedicamentDenumire(const string &denumire) const {
    auto v = find_if(this->medicamente.begin(), this->medicamente.end(), [&denumire](const Medicament& m) {
        return denumire == m.getDenumire();
    });
    if (v == medicamente.cend())
        throw RepositoryException("Medicamentul cautat nu exista!");

    return v.operator*();
}

const map<string, int>& Repository::getContor() const noexcept {
    return this->contor;
}

void Repository::undo() {
    if (vectorUndo.empty()) {
        throw UndoException("Nu se mai poate face undo!\n");

    }
    auto m = vectorUndo.at(vectorUndo.size() - 1).get();

    m->doUndo();
    vectorUndo.pop_back();
//    delete m;
//    delete vectorUndo.back();
    vectorUndo.pop_back();
//    delete m;
}


