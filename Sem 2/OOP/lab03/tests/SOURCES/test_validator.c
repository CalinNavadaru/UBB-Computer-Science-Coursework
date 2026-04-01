//
// Created by calin on 18.03.2023.
//

#include "../HEADERS/test_validator.h"

typedef struct {
    int numar_ap;
    double suma;
    char tip[25];
}Cheltuiala_test;

void test_validator() {
    Cheltuiala_test c1, c2, c3, c4;

    c1.numar_ap = -1;
    c1.suma = 3.14;
    strcpy(c1.tip, "gaz");

    c2.numar_ap = 5;
    c2.suma = -213;
    strcpy(c2.tip, "incalzire");

    c3.numar_ap = 4;
    c3.suma = 21;
    strcpy(c3.tip, "");

    c4.numar_ap = 5;
    c4.suma = 1.123;
    strcpy(c4.tip, "gaz");

    int *erori;
    erori = validator(c1.numar_ap, c1.suma, c1.tip);
    assert(erori[0] == 1);

    free(erori);

    erori = validator(c2.numar_ap, c2.suma, c2.tip);
    assert(erori[1] == 1);

    free(erori);

    erori = validator(c3.numar_ap, c3.suma, c3.tip);
    assert(erori[2] == 1);

    free(erori);

    erori = validator(c4.numar_ap, c4.suma, c4.tip);
    for (int i = 0; i < 3; i++)
        assert(erori[i] == 0);

    free(erori);
}
