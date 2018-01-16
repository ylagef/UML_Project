//
// Created by ylage on 16/01/2018.
//

#include "Rent.h"


Rent::~Rent() {

}


const string &Rent::getDate() const {
    return date;
}

void Rent::setDate(const string &date) {
    Rent::date = date;
}


int Rent::getItem_id() const {
    return item_id;
}

void Rent::setItem_id(int item_id) {
    Rent::item_id = item_id;
}


const string &Rent::getReturned() const {
    return returned;
}

void Rent::setReturned(const string &returned) {
    Rent::returned = returned;
}

Rent::Rent(int rent_id, int item_id, const string &date, const string &returned) : rent_id(rent_id), item_id(item_id),
                                                                                   date(date), returned(returned) {}

int Rent::getRent_id() const {
    return rent_id;
}

void Rent::setRent_id(int rent_id) {
    Rent::rent_id = rent_id;
}


