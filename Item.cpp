//
// Created by ylage on 13/01/2018.
//

#include "Item.h"

Item::Item(int id, const string &type, const string &brand, const string &model, const string &specs, float price,
           int rented, int sold, int total) : id(id), type(type), brand(brand), model(model), specs(specs),
                                              price(price), rented(rented), sold(sold), total(total) {}

int Item::getId() const {
    return id;
}

void Item::setId(int id) {
    Item::id = id;
}

const string &Item::getType() const {
    return type;
}

void Item::setType(const string &type) {
    Item::type = type;
}

const string &Item::getBrand() const {
    return brand;
}

void Item::setBrand(const string &brand) {
    Item::brand = brand;
}

const string &Item::getModel() const {
    return model;
}

void Item::setModel(const string &model) {
    Item::model = model;
}

const string &Item::getSpecs() const {
    return specs;
}

void Item::setSpecs(const string &specs) {
    Item::specs = specs;
}

float Item::getPrice() const {
    return price;
}

void Item::setPrice(float price) {
    Item::price = price;
}

int Item::getRented() const {
    return rented;
}

void Item::setRented(int rented) {
    Item::rented = rented;
}

int Item::getSold() const {
    return sold;
}

void Item::setSold(int sold) {
    Item::sold = sold;
}

int Item::getTotal() const {
    return total;
}

void Item::setTotal(int total) {
    Item::total = total;
}

Item::~Item() {

}
