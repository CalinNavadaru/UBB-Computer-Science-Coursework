//
// Created by calin on 29.05.2023.
//

#include <algorithm>
#include "Observer.h"

void Subject::adaugaObservator(Observer *ob) {
    observatori.push_back(ob);
}

void Subject::eliminaObservator(Observer *ob) {
    observatori.erase(std::remove(observatori.begin(), observatori.end(), ob));
}

void Subject::notifica() {
    for (const auto& el: observatori) {
        el->update();
    }
}
