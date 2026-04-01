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

    string& getMsg() {
        return msg;
    };
};

class ValidationException: std::exception {
private:
    string msg;
public:
    explicit ValidationException(string msg): msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const ValidationException& ex);

    string& getMsg();
};


class RetetaException: std::exception {
private:
    string msg;

public:

    explicit RetetaException(string msg): msg{std::move(msg)} {

    }

    friend ostream& operator<<(ostream& ot, const RetetaException& exx);
};

class InputValidationException: std::exception {
private:
    string msg;
public:
    explicit InputValidationException(string msg): msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const InputValidationException& ex);

    string& getMsg();
};

class UndoException: std::exception {
private:
    string msg;



public:
    explicit UndoException(string msg) : msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const UndoException& ex);

    string& getMsg() {
        return msg;
    }
};

class InputException: std::exception {
private:
    string msg;



public:
    explicit InputException(string msg) : msg{std::move(msg)} {

    }
    friend ostream& operator<<(ostream& ot, const InputException& ex);

    string& getMsg() {
        return msg;
    }
};