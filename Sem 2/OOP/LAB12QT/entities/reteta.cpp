//
// Created by calin on 22.04.2023.
//

#include "reteta.h"

void Reteta::goleste() noexcept {
    listaMedicamente.erase(this->listaMedicamente.cbegin(), this->listaMedicamente.cend());
    notifica();
}

void Reteta::adauga(const Medicament& m) {
    listaMedicamente.push_back(m);
    notifica();
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

    notifica();
}

int Reteta::nrMedicamente() const noexcept {
    return (int)listaMedicamente.size();
}

const vector<Medicament>& Reteta::getReteta() const noexcept {
    return listaMedicamente;
}


