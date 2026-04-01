//
// Created by calin on 13.03.2023.
//

#ifndef LAB02_SERVICE_H
#define LAB02_SERVICE_H

#include "../../repository/HEADERS/repo.h"



int adaugare_cheltuiala_service(Repo *, int, double, char[]);

int modificare_cheltuiala_service(Repo*, int, char*, double);

int stergere_cheltuiala_service(Repo*, int);

int cautare_service(Repo*, Cheltuiala);

#endif //LAB02_SERVICE_H

