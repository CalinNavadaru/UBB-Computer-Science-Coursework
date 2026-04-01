//
// Created by calin on 12.03.2023.
//

#include "../HEADERS/test_entity.h"
#include <string.h>


int test_entitate() {

    Cheltuiala c;
    init_Cheltuiala(&c);
    if (c.lungime_tip != 0 || strcmp(c.tip_plata, "\0") == 0)
        return -1;

    char tip_nou[] = "incalzire";
    set_tip(&c, tip_nou);

    if (strcmp(c.tip_plata, tip_nou) != 0)
        return -2;

    double suma = 3.14;
    set_suma(&c, suma);

    if (c.suma != 3.14)
        return -3;

    if (get_suma(c) != 3.14)
        return -4;

    c.numarul_apartamentului = 4;
    if (get_numarul_apartamentului(c) != 4)
        return -5;

    if (strcmp(get_tip_plata(&c), tip_nou) != 0)
        return -6;
}
