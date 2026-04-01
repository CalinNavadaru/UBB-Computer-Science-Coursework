//
// Created by calin on 22.04.2023.
//

#pragma once
#include "medicament.h"
#include "../exceptions/exceptions.h"
#include <iostream>
#include "../repository/repo.h"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using std::vector;
using std::string;
using std::cout;

class Reteta {
private:
    vector<Medicament> listaMedicamente;
    Repository& repo;

public:

    explicit Reteta(Repository& r) : repo(r) {

    }

    Reteta(const Reteta& r) = delete;

    void goleste() noexcept;

    void adauga(const Medicament& m);

    void genereaza(int numarMedicamente) noexcept;

    int nrMedicamente() const noexcept;

    const vector<Medicament>& getReteta() const noexcept;
};
