//
// Created by calin on 07.05.2023.
//

#include "reteta_repo.h"

void RetetaRepo::scrieInFisier(const vector<Medicament>& v) {
    std::ofstream fout(filename);
    fout << std::flush;
    for (const auto& el: v) {
        fout << el.getDenumire() << ",";
        fout << el.getSubstantaActiva() << ",";
        fout << el.getProducator() << ",";
        fout << el.getPret() << std::endl;
    }
    fout.close();
}
