//
// Created by calin on 21.04.2023.
//

#include "test_service_statistics.h"

void test_service_statistics() {

    Repository r;
    ServiceStatistics s(r);
    Medicament m1("A", "B", "C", 12);
    Medicament m2("J", "M", "D", 1234);
    Medicament m3("K", "N", "E", 123);
    Medicament m4("G", "N", "E", 123);
    Medicament m5("T", "B", "E", 11);

    r.adaugareMedicament(m1);
    r.adaugareMedicament(m2);
    r.adaugareMedicament(m3);
    r.adaugareMedicament(m4);
    r.adaugareMedicament(m5);

    auto v = s.filtrareMedicamentePret(123);
    assert(eq(v.at(0), m3));
    assert(eq(v.at(1), m4));

    v = s.sortareMedicamenteProducatorPret([] (const Medicament& m1, const Medicament& m2) {
        return m1.getProducator() > m2.getProducator() || (m1.getProducator() == m2.getProducator() && m1.getPret() > m2.getPret());
    });

    assert(eq(v.at(0), m1));
    assert(eq(v.at(1), m2));
    assert(eq(v.at(2), m3));
    assert(eq(v.at(3), m4));
    assert(eq(v.at(4), m5));
}
