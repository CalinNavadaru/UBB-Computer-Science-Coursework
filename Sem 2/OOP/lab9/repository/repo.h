//
// Created by calin on 01.04.2023.
//

#pragma once
#include "../entities/medicament.h"
#include "../exceptions/exceptions.h"
#include "../../lab9/vectordinamic.h"
#include <algorithm>
#include <map>
#include <memory>


using std::vector;
using std::find_if;
using std::map;
using std::unique_ptr;

class Undo;

class Repository {

private:
    vector<Medicament> medicamente;

    vector<unique_ptr<Undo>> vectorUndo;

    std::map<string, int> contor;

    bool existAlready(const Medicament& m) const;


public:

    Repository() = default;

    Repository(const Repository& ot) = delete;

    int getNrMedicamente() const;

    const vector<Medicament>& getMedicamente() const;

    int adaugareMedicament(const Medicament& m);

    int modificareMedicament(const Medicament& m, int index);

    int stergereMedicament(int index);

    const Medicament& cautaMedicament(const string& denumire, const string& producator, const string& substantaActiva, double pret) const;

    const Medicament& cautaMedicamentDenumire(const string& denumire) const;

    const Medicament& getMedicament(int index) const;

    void interschimbareMedicamente(int i, int j);

    const map<string, int>& getContor() const noexcept;

    void undo();
};

class Undo {
public:
    virtual void doUndo() = 0;
    virtual ~Undo() = default;
};

class AdaugareUndo : public Undo {
private:
    int index;
    Repository& r;
public:
    AdaugareUndo(int indice, Repository& r) : index{indice}, r{r} {

    }

    void doUndo() override {
        r.stergereMedicament(index);
    }
};

class StergereUndo: public Undo {
private:
    Medicament m;
    Repository& r;
public:
    StergereUndo(const Medicament& m, Repository& r) : m{m}, r{r} {

    }

    void doUndo() override {
        r.adaugareMedicament(m);
    }
};

class ModificareUndo : public Undo {
private:
    Medicament m;
    int index;
    Repository& r;
public:
    ModificareUndo(const Medicament& m1, int index, Repository& r) : m{m1}, index{index}, r{r} {

    }

    void doUndo() override {
        r.modificareMedicament(m, index);
    }
};
