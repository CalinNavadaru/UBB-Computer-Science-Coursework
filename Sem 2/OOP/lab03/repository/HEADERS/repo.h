//
// Created by calin on 18.03.2023.
//

#ifndef LAB03_REPO_H
#define LAB03_REPO_H

#include "../../entities/HEADERS/validator.h"

typedef struct {
    Cheltuiala* date_cheltuieli;
    int lungime;
    int dimensiune;
}Repo;

Repo creeaza_repo();

void redim(Repo*);

int adauga_cheltuiala(Repo*, Cheltuiala);

int sterge_cheltuiala(Repo*, int);

int modifca_cheltuiala(Repo*, Cheltuiala, int);

void distruge_repo(Repo *r);

Cheltuiala get_cheltuiala(Repo*, int);

int get_nr_elemente(Repo*);

#endif //LAB03_REPO_H
