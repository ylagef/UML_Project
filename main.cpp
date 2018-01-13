#include <iostream>
#include <fstream>
#include <cstring>

#include "Item.h"
#include "Usr.h"

using namespace std;

Item items[1000] = {};
Usr users[1000] = {};

// Create the files for items and rental history
void setup() {
    //Read from files
    //items.txt
    string line;
    ifstream it("../files/items.txt");
    int numitem = 0;
    if (it.is_open()) {
        while (getline(it, line)) {
            int i = 0;
            string item[10] = {};
            size_t pos = 0;
            std::string token;
            while ((pos = line.find("-")) != std::string::npos) {
                token = line.substr(0, pos);
                item[i] = token;
                i++;
                line.erase(0, pos + 1);
            }

            int id = stoi(item[0]);
            float price = stof(item[5], nullptr);
            int rented = stoi(item[6]);
            int sold = stoi(item[7]);
            int total = stoi(item[8]);

            items[numitem] = Item(id, item[1], item[2], item[3], item[4], price, rented, sold, total);

            numitem++;
        }
        it.close();
    } else cout << "Unable to open file";

    //users.txt
    string line2;
    ifstream us("../files/users.txt");
    int itemnum = 0;
    if (us.is_open()) {
        while (getline(us, line)) {
            int i = 0;
            string user[10] = {};
            size_t pos = 0;
            std::string token;
            while ((pos = line.find("-")) != std::string::npos) {
                token = line.substr(0, pos);
                user[i] = token;
                i++;
                line.erase(0, pos + 1);
            }

            users[itemnum] = Usr(user[0], user[1], user[2], user[3]);

            itemnum++;
        }
        us.close();
    } else cout << "Unable to open file";
}

int main() {
    setup();

}