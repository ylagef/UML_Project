//
// Created by ylage on 13/01/2018.
//

#include "Usr.h"

Usr::Usr(const string &username, const string &name, const string &surname, const string &datebirth) : username(
        username), name(name), surname(surname), datebirth(datebirth) {}

const string &Usr::getUsername() const {
    return username;
}

void Usr::setUsername(const string &username) {
    Usr::username = username;
}

const string &Usr::getName() const {
    return name;
}

void Usr::setName(const string &name) {
    Usr::name = name;
}

const string &Usr::getSurname() const {
    return surname;
}

void Usr::setSurname(const string &surname) {
    Usr::surname = surname;
}

const string &Usr::getDatebirth() const {
    return datebirth;
}

void Usr::setDatebirth(const string &datebirth) {
    Usr::datebirth = datebirth;
}
