//
// Created by calin on 19.03.2023.
//

#include "../HEADERS/validator_input.h"

int* validate_input_adaugare(int numar, double suma, char tip[]) {
    return validator(numar, suma, tip);
}

int validare_index(Repo* r, int index) {
    return 1 <= index && index <= get_nr_elemente(r);
}

int* validate_input_modificare(double suma, char tip[], int index, Repo *r) {
    Cheltuiala c = get_cheltuiala(r, index);
    return validator(get_numar_apartament(&c), suma, tip);
}