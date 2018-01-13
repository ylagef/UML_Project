#include <iostream>
#include <fstream>
#include "Item.h"
#include "Usr.h"

using namespace std;

Item items[1000];
Usr users[1000];

// Create the files for items and rental history
void setup() {
    ofstream items;
    items.open("../files/items.txt");
    //items << "Writing this to a file.\n";
    items.close();

    ofstream users;
    users.open("../files/users.txt");
    //items << "Writing this to a file.\n";
    users.close();
}

int main() {
    users[0] = Usr("ylagef", "Yeray", "Lage", "23/09/1995");
    items[0] = Item(0, "M", "Apple", "iPhone X", "8GB 128GB", 1000.0, 0, 1, 10);
    setup();
}