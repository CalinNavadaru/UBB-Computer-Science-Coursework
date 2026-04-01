//
// Created by calin on 19.03.2023.
//

#ifndef LAB03_SERVICE_H
#define LAB03_SERVICE_H

#include "../../repository/HEADERS/repo.h"

int adauga_cheltuiala_service(Repo*, int, double, char *);

int stergere_cheltuiala_service(Repo*, int);

int modifica_cheltuiala_service(Repo*, double, char*, int);

Cheltuiala* get_elemente(Repo*);

int get_nr_elemente_service(Repo*);

int compara_tipuri(char *, char *);

int compara_suma(double, double);

#endif //LAB03_SERVICE_H