//
// Created by calin on 13.03.2023.
//

#include "../HEADERS/validator.h"
#include <string.h>

int validator(Cheltuiala c) {
    if (c.suma < 0)
        return -1;

    if (c.numarul_apartamentului <= 0)
        return -2;

    if (strlen(c.tip_plata) == 0)
        return -3;

    return 0;
}