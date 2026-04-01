//
// Created by calin on 18.03.2023.
//

#ifndef LAB03_ENTITIES_H
#define LAB03_ENTITIES_H

#include <string.h>
#include <malloc.h>

typedef struct {

    char *tip;
    int numar_apartament;
    int lungime_tip;
    double suma;
}Cheltuiala;

/*
 * Creeaza o cheltuiala.
 * @param numar_apartament: int - numarul apartamentului de creat.
 * @param suma: double - pretul cheltuieli.
 * @param tip: char* - sir de caractere ce semnifica tipul platii.
 *
 * @return: Cheltuiala - cheltuiala creata.
 */
Cheltuiala creare_Cheltuiala(int numar_apartament, double suma, char *tip);

/*
 * Seteaza unei cheltuieli suma de platit.
 *
 */
void set_suma(Cheltuiala*, double);

void set_numar_apartament(Cheltuiala*, int);

void set_tip(Cheltuiala*, char*);

int get_numar_apartament(Cheltuiala*);

double get_suma(Cheltuiala*);

char* get_tip(Cheltuiala*);

int egalitate(Cheltuiala, Cheltuiala);

void distrugere_cheltuiala(Cheltuiala*);

#endif //LAB03_ENTITIES_H
