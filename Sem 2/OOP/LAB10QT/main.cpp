#include <QApplication>
#include "UI/UI.h"
#include "tests/test_all.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    testAll();
    Repository r;
    Reteta reteta(r);
    ServiceCRUD s(r);
    ServiceStatistics ss(r);
    ServiceReteta sReteta(reteta, r);
    UI ui(s, ss, sReteta);
    return QApplication::exec();
}
