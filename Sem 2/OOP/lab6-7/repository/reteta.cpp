//
// Created by calin on 22.04.2023.
//

#include "reteta.h"

void Reteta::goleste() noexcept {
    listaMedicamente.erase(this->listaMedicamente.cbegin(), this->listaMedicamente.cend());
}

void Reteta::adauga(const string& denumire) {

    try {
        auto m = repo.cautaMedicamentDenumire(denumire);
        listaMedicamente.push_back(m);

    } catch (RepositoryException& e) {
        throw RetetaException("Nu exista un medicament cu denumirea oferita!");
    }
}

void Reteta::genereaza(int numarMedicamente) noexcept {
    goleste();

    int curent = 0;
    vector<int> v;
    v.resize(numarMedicamente);
    std::generate(v.begin(), v.end(), [&curent]() {return curent++;});
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(v.begin(),v.end(), std::default_random_engine(seed));

    for (int i = 0; i < numarMedicamente; i++)
        listaMedicamente.push_back(repo.getMedicament(v.at(i)));
}

int Reteta::nrMedicamente() const noexcept {
    return (int)listaMedicamente.size();
}

const vector<Medicament>& Reteta::getReteta() const noexcept {
    return listaMedicamente;
}


