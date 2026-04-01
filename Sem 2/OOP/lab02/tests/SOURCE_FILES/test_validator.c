//
// Created by calin on 13.03.2023.
//

#include "../HEADERS/test_validator.h"
#include <string.h>

int test_validator() {
    Cheltuiala c1, c2;
    c1.suma = 5;
    c1.numarul_apartamentului = 4;
    char tip[] = "incalzire";
    strcpy(c1.tip_plata, tip);
    c1.lungime_tip = strlen(c1.tip_plata);

    c2.suma = -3;
    c2.numarul_apartamentului = 3;
    char tip2[] = "incalzire";
    strcpy(c2.tip_plata, tip2);
    c2.lungime_tip = strlen(c2.tip_plata);

    if (validator(c1) < 0)
       return -1;

    if (validator(c2) < 0)
        return -2;
}

