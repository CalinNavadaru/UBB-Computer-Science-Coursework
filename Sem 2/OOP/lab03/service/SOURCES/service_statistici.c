//
// Created by calin on 20.03.2023.
//

#include "../HEADERS/service_statistici.h"



Cheltuiala* filtrare_service(Repo *r, char *tip, int *lungime_filtrare, int(*f)(char*, char*)) {
    Cheltuiala *elemente = get_elemente(r);
    int lungime = get_nr_elemente_service(r), k = 0;
    Cheltuiala *elemente_filtrate = (Cheltuiala *) malloc(lungime * sizeof(Cheltuiala));
    for (int i = 0; i < lungime; i++)
        if ((*f)(tip, elemente[i].tip) == 0)
        elemente_filtrate[k++] = elemente[i];

    free(elemente);

    *lungime_filtrare = k;
    return elemente_filtrate;
}

Cheltuiala* sortare_service(Repo *r, int(*f)(double, double)) {
    Cheltuiala *elemente = get_elemente(r);
    int lungime = get_nr_elemente_service(r);


    for (int i = 0; i < lungime; i++)
        for (int j = i + 1; j < lungime; j++)
                if ((*f)(get_suma(&elemente[i]), get_suma(&elemente[j]))) {
                    Cheltuiala aux;
                    aux = elemente[i];
                    elemente[i] = elemente[j];
                    elemente[j] = aux;
                }

    return elemente;
}