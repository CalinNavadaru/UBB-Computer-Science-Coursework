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
#include "../UI/Observer.h"

using std::vector;
using std::string;
using std::cout;

class Reteta : public Subject {
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

    [[nodiscard]] int nrMedicamente() const noexcept;

    [[nodiscard]] const vector<Medicament>& getReteta() const noexcept;
};
