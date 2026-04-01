//
// Created by calin on 01.04.2023.
//
#pragma once
#include <string>
#include <utility>
#include <vector>
#include <atomic>


using std::string;

class Medicament {

private:
    string denumire, producator, substantaActiva;
    double pret{};
    int id = ++nrId;

protected:
    static std::atomic<int> nrId;

public:

    Medicament(string   denumire, string   producator, string   substantaActiva, double const pret) :
            substantaActiva{std::move(substantaActiva)}, denumire{std::move(denumire)}, producator{std::move(producator)}, pret{pret}{
    };

    Medicament(const Medicament& other): denumire{other.denumire}, id{nrId++}, producator{other.producator}, substantaActiva{other.substantaActiva}, pret{other.pret} {
            //id nou
    };

    Medicament() = default;

    string getDenumire() const;

    string getProducator() const;

    string getSubstantaActiva() const;

    double getPret() const;

    int getId() const;

    void setDenumire(string denumireNoua);

    void setProducator(string producatorNou);

    void setSubstantaActiva(string substantaActivaNoua);

    void setPret(double pretNou);

    bool operator==(const Medicament& m) const;

};

bool eq(const Medicament& m1, const Medicament& m2);

