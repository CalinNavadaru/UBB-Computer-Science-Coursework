//
// Created by calin on 20.03.2023.
//

#ifndef LAB03_SERVICE_STATISTICI_H
#define LAB03_SERVICE_STATISTICI_H

#include "service.h"

Cheltuiala* filtrare_service(Repo *r, char *tip, int *lungime_filtrare, int(*f)(char*, char*));

Cheltuiala* sortare_service(Repo*, int(*f)(double , double));
#endif //LAB03_SERVICE_STATISTICI_H
