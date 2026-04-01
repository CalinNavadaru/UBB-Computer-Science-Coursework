//
// Created by calin on 01.04.2023.
//

#pragma once
#include <string>
#include <iostream>
#include <utility>

using std::string;
using std::ostream;
class RepositoryException: std::exception {

private:
    string msg;
public:

    explicit RepositoryException(string msg): msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const RepositoryException& ex);
};

class ValidationException: std::exception {
private:
    string msg;
public:
    explicit ValidationException(string msg): msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const ValidationException& ex);
};


class RetetaException: std::exception {
private:
    string msg;

public:

    explicit RetetaException(string msg): msg{std::move(msg)} {

    }

    friend ostream& operator<<(ostream& ot, const RetetaException& exx);
};