//
// Created by calin on 19.03.2023.
//

#include "../HEADERS/service.h"

int compara_suma(double s1, double s2) {
    return s1 > s2;
}

int compara_tipuri(char *tip1, char *tip2) {
    return strcmp(tip1, tip2);
}

int adauga_cheltuiala_service(Repo *r, int numar_ap, double suma, char *tip) {
    Cheltuiala c = creare_Cheltuiala(numar_ap, suma, tip);
    return adauga_cheltuiala(r, c);
}

int stergere_cheltuiala_service(Repo *r, int index) {
    sterge_cheltuiala(r, index);
    return 0;
}

int modifica_cheltuiala_service(Repo *r, double suma_noua, char *tip, int index) {
    Cheltuiala c_curent = get_cheltuiala(r, index);
    set_tip(&c_curent, tip);
    set_suma(&c_curent, suma_noua);
    return modifca_cheltuiala(r, c_curent, index);
}

Cheltuiala* get_elemente(Repo* r) {
    int lungime = get_nr_elemente(r);

    Cheltuiala* elemente = (Cheltuiala*) malloc(lungime * sizeof(Cheltuiala));

    for (int i = 0; i < lungime; i++)
        elemente[i] = get_cheltuiala(r, i + 1);

    return elemente;
}

int get_nr_elemente_service(Repo *r) {
    return get_nr_elemente(r);
}