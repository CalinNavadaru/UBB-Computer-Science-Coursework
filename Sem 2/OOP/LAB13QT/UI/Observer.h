//
// Created by calin on 29.05.2023.
//
#pragma once
#include <vector>

using std::vector;

class Observer {

public:
    virtual void update() = 0;
};

class Subject {
private:
    vector<Observer*> observatori;

public:

    void adaugaObservator(Observer* ob);

    void eliminaObservator(Observer* ob);

protected:
    void notifica();
};
