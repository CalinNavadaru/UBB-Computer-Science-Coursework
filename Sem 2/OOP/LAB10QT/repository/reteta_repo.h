//
// Created by calin on 07.05.2023.
//

#pragma once
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "../entities/medicament.h"

using std::string;
using std::vector;


class RetetaRepo {
private:
    string filename;
public:

    explicit RetetaRepo(string f) : filename{std::move(f)} {

    }

    RetetaRepo(const RetetaRepo& e) = delete;

    void scrieInFisier(const vector<Medicament>& v);
};
