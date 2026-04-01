//
// Created by calin on 13.03.2023.
//

#ifndef LAB02_REPO_H
#define LAB02_REPO_H

#include "../../entities/HEADERS/validator.h"

struct Repo {
    Cheltuiala date[1000];
    int lungime;
};

typedef struct Repo Repo;

void init_repo(Repo*);

int adaugare_cheltuiala(Repo*, Cheltuiala);

int modificare_cheltuiala(Repo*, Cheltuiala, int);

int stergere_cheltuiala(Repo*, int);

int cautare(Repo*, Cheltuiala);

#endif //LAB02_REPO_H
