//
// Created by ylage on 16/01/2018.
//

#ifndef PROJECT_RENT_H
#define PROJECT_RENT_H

#include <iostream>
#include "Item.h"
#include "Usr.h"

using namespace std;

class Rent {
private:
    int rent_id;
    int item_id;
    string date;
    string returned;
public:
    Rent() {}

    Rent(int rent_id, int item_id, const string &date, const string &returned);

    virtual ~Rent();

    int getItem_id() const;

    void setItem_id(int item_id);

    int getRent_id() const;

    void setRent_id(int rent_id);

    const string &getDate() const;

    void setDate(const string &date);

    const string &getReturned() const;

    void setReturned(const string &returned);
};


#endif //PROJECT_RENT_H
