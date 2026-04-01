//
// Created by calin on 07.05.2023.
//

#include "test_reteta_repo.h"
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>

using std::string;

void test_reteta_repo() {
    Repository r;
    RetetaRepo retetaRepo{"fisier_test.csv"};
    Reteta reteta{r};
    Medicament m1("A", "B", "C", 13);
    Medicament m2("QWERTY", "XXXXX", "DE", 3);

    r.adaugareMedicament(m1);
    r.adaugareMedicament(m2);

    reteta.adauga(m1);
    reteta.adauga(m2);

    retetaRepo.scrieInFisier(reteta.getReteta());

    std::ifstream fin("fisier_test.csv");
    int k = 0;
    while (!fin.eof()) {

        string denumire, producator, substantaActiva;
        string linie;
        int pret;
        fin >> linie;
        if (linie.empty())
            break;
        std::replace(linie.begin(), linie.end(), ',', ' ');
        std::stringstream f(linie);
        f >> denumire >> substantaActiva >> producator >> pret;
//        fin >> denumire >> substantaActiva >> producator >> pret;
        Medicament m{denumire, producator, substantaActiva, pret};
        assert(m == reteta.getReteta().at(k));
        k++;
    }
}
