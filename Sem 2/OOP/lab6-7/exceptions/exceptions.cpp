//
// Created by calin on 01.04.2023.
//

#include "exceptions.h"

ostream &operator<<(ostream &out, const RepositoryException& ex) {
    out << ex.msg;
    return out;
}

ostream &operator<<(ostream &ot, const ValidationException &ex) {
    ot << ex.msg;
    return ot;
}

ostream &operator<<(ostream &ot, const RetetaException &exx) {
    ot << exx.msg;
    return ot;
}
