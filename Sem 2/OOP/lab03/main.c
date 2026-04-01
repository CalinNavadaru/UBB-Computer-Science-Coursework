#include "tests/HEADERS/test_all.h"
#include "ui/HEADERS/ui.h"
#include <unistd.h>

int main() {
    Repo r;
    r = creeaza_repo();
    test_all();
    sleep(5);
    run(&r);
    distruge_repo(&r);
    return 0;
}
