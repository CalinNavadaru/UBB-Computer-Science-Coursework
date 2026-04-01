//
// Created by calin on 21.04.2023.
//

#include "medicament_validator.h"

void Validator::validare() {
    string erori;
    if (denumire.empty())
        erori.append("Denumirea este vida!\n");

    if (producator.empty())
        erori.append("Numele producatorului este vid!\n");

    if (substantaActiva.empty())
        erori.append("Numele substantei active este vid!\n");

    if (pret <= 0)
        erori.append("Pretul trebuie sa fie nenegativ!\n");

    if (!erori.empty())
        throw ValidationException(erori);
}
