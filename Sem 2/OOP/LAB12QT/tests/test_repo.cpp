//
// Created by calin on 01.04.2023.
//

#include "test_repo.h"
#include <iostream>

using std::cout;

void testRepo() {

    Medicament m1("A", "B", "C", 3);
    Medicament m2("D", "E", "F", 123);
    Medicament m3("Theta", "B", "gh", 68);
    Medicament m4("Beta", "Gamma", "Phi", 68);

    Repository repository, r;
    assert(repository.getNrMedicamente() == 0);

    repository.adaugareMedicament(m1);
    assert(repository.getNrMedicamente() == 1);
    auto g = repository.getContor();
    assert(g.size() == 1);
    repository.undo();
    try {
        repository.undo();
        assert(false);
    } catch(UndoException& e) {
        assert(true);
    }
    assert(repository.getNrMedicamente() == 0);
    repository.adaugareMedicament(m1);
    auto m = repository.getMedicament(0);

    assert(eq(m, m1));

    repository.adaugareMedicament(m2);
    assert(repository.getNrMedicamente() == 2);

    auto rez = repository.cautaMedicamentDenumire("A");
    assert(eq(rez, m1));

    try {
        auto rez11 = repository.cautaMedicamentDenumire("sadsaddasdasdasasd");
        assert(false);
    } catch (RepositoryException& e) {
        assert(true);
    }


    auto rezultatCautare2 = repository.getMedicamente();
    assert(eq(repository.getMedicament(0), m1));
    assert(eq(repository.getMedicament(1), m2));

    repository.adaugareMedicament(m3);
    repository.stergereMedicament(1);
    repository.stergereMedicament(2);
    repository.undo();
    assert(repository.getNrMedicamente() == 2);
    repository.stergereMedicament(2);
    assert(repository.getNrMedicamente() == 1);
    assert(m.getDenumire() == m1.getDenumire() && m.getSubstantaActiva() == m1.getSubstantaActiva() &&
           m.getPret() == m1.getPret());

    repository.modificareMedicament(m3, 0);
    repository.undo();
    assert(eq(repository.getMedicament(0), m1));
    repository.modificareMedicament(m3, 0);
    assert(eq(repository.getMedicament(0), m3));

    repository.adaugareMedicament(m4);

    auto rezultatCautare = repository.cautaMedicament("Beta", "Gamma", "Phi", 68);
    assert(eq(rezultatCautare, m4));

    try {
        repository.adaugareMedicament(m4);
        assert(false);
    } catch (RepositoryException&) {
        assert(true);
    }

    try {
        repository.cautaMedicament("", "", "", 0);
        assert(false);
    } catch (RepositoryException&) {
        assert(true);
    }
    r.adaugareMedicament(m1);
    r.adaugareMedicament(m2);
    r.interschimbareMedicamente(0, 1);
    assert(eq(r.getMedicament(0), m2));
    assert(eq(r.getMedicament(1), m1));
}