//
// Created by ylage on 13/01/2018.
//

#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H

#include <iostream>

using namespace std;

class Item {
private:
    int id;
    string type;
    string brand;
    string model;
    string specs;
    float price;
    int rented;
    int sold;
    int total;

public:
    Item(int id, const string &type, const string &brand, const string &model, const string &specs, float price,
         int rented, int sold, int total);

    int getId() const;

    void setId(int id);

    const string &getType() const;

    void setType(const string &type);

    const string &getBrand() const;

    void setBrand(const string &brand);

    const string &getModel() const;

    void setModel(const string &model);

    const string &getSpecs() const;

    void setSpecs(const string &specs);

    float getPrice() const;

    void setPrice(float price);

    int getRented() const;

    void setRented(int rented);

    int getSold() const;

    void setSold(int sold);

    int getTotal() const;

    void setTotal(int total);
};


#endif //PROJECT_ITEM_H
