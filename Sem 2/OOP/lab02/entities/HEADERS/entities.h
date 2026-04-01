//
// Created by calin on 12.03.2023.
//

#ifndef LAB02_ENTITIES_H
#define LAB02_ENTITIES_H

struct Cheltuiala {
    double suma;
    int numarul_apartamentului;
    char tip_plata[25];
    int lungime_tip;
};

typedef struct Cheltuiala Cheltuiala;

void init_Cheltuiala(Cheltuiala *);

void set_tip(Cheltuiala*, char[]);

void set_suma(Cheltuiala*, double);

double get_suma(Cheltuiala);

int get_numarul_apartamentului(Cheltuiala);

char* get_tip_plata(Cheltuiala*);

int egalitate(Cheltuiala, Cheltuiala);

#endif //LAB02_ENTITIES_H
