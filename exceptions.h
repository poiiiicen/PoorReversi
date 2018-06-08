//
// Created by poiii on 2018/6/9.
//

#ifndef POORREVERSI_EXCEPTIONS_H
#define POORREVERSI_EXCEPTIONS_H

#include <iostream>
#include <exception>

class StatusCodeException : public std::exception {
    int status_code;

public:
    const char *what() const noexcept override { return "Unexpected Status Code"; }

    explicit StatusCodeException(int code) : status_code(code) {};

    int get_status_code() { return status_code; }
};

class PlayerException : public std::exception {
public:
    const char *what() const noexcept override { return "Unexpected Player"; }
};

class TurnException : public std::exception {
public:
    const char *what() const noexcept override { return "Unexpected Turn"; }
};

class BoardException : public std::exception {
public:
    const char *what() const noexcept override { return "Unexpected Board"; }
};

class MoveException : public std::exception {
public:
    const char *what() const noexcept override { return "Unexpected Move"; }
};

#endif //POORREVERSI_EXCEPTIONS_H
