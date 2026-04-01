#include "tests/test_all.h"
#include "ui/ui.h"
#include "ui/ui_reteta.h"
#include "ui/ui_principal.h"

int main() {
    testAll();
    Repository r;
    Reteta reteta(r);
    ServiceCRUD s(r);
    ServiceStatistics ss(r);
    ServiceReteta sReteta(reteta);
    UI u(s, ss);
    UiReteta uReteta(sReteta);
    UiPrincipal uPrincipal(u, uReteta);
    uPrincipal.run();
    return 0;
}
