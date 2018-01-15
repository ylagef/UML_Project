#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "Item.h"
#include "Usr.h"

using namespace std;
vector<Item> items;
vector<Usr> users;


// Create the files for items and rental history
void setup() {
    //Read from files
    //items.txt
    string line;
    ifstream it("../files/items.txt");
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

            items.emplace_back(id, item[1], item[2], item[3], item[4], price, rented, sold, total);
        }
        it.close();
    } else cout << "Unable to open file";

    //users.txt
    string line2;
    ifstream us("../files/users.txt");
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

            users.emplace_back(user[0], user[1], user[2], user[3]);

        }
        us.close();
    } else cout << "Unable to open file";
}


void save_changes() {

    ofstream it("../files/items.txt");
    if (it.is_open()) {
        for (Item i : items) {
            string to_write;
            to_write = i.getId() + "-" + i.getType() + "-" + i.getBrand() + "-" +
                       i.getModel() + "-" + i.getSpecs() + "-" + to_string(i.getPrice()) +
                       "-" + to_string(i.getRented()) + "-" + to_string(i.getSold()) + "-" +
                       to_string(i.getTotal()) + "-";
            it << to_write << "\n";
        }
        it.close();
    } else cout << "Unable to open file";

    ofstream us("../files/users.txt");
    if (us.is_open()) {
        for (Usr u:users) {
            string to_write;
            to_write = u.getUsername() + "-" + u.getName() + "-" + u.getSurname() + "-" +
                       u.getDatebirth() + "-";
            us << to_write << "\n";
        }
        us.close();
    } else cout << "Unable to open file";
}

void rent() {

}

void buy() {

}

void rental_history() {

}

bool username_exists(string uname) {
    for (int i = 0; i < sizeof(users); i++) {
        if (users[i].getUsername() == uname) {
            return true;
        }
    }
    return false;
}

void new_user() {
    string name, surname, date_birth, username;
    cout << "Okay, let's register you. What's your name?";
    cin >> name;
    cout << "What's your surname?";
    cin >> surname;
    cout << "What's your birthday date? (Format DD/MM/YYY)";
    cin >> date_birth;
    cout << "Finally, choose your username:";
    cin >> username;
    while (username_exists(username)) {
        cout << "This username is already on use. Please select other.";
        cin >> username;
    }
    users.emplace_back(Usr(username, name, surname, date_birth));
    cout << "User " << username << " created successful.";
}

void main_menu() {
    int option;
    cout << "Welcome to our shop.";
    while (true) {
        cout << " What do you want to do?\n1. Rent. 2. Buy 3. See your rental history. 4. Register new user. 5. Exit.";
        cin >> option;
        switch (option) {
            case 1:
                rent();
                break;
            case 2:
                buy();
                break;
            case 3:
                rental_history();
                break;
            case 4:
                new_user();
                break;
            case 5:
                return;
            default:
                cout << "Incorrect option.";
        }
    }

}


int main() {
    setup();
    main_menu();
    save_changes();
    exit(0);
}