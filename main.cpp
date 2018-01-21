#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <fileapi.h>

#include "Item.h"
#include "Usr.h"
#include "Rent.h"

using namespace std;

vector<Item *> items;
vector<Usr *> users;

//Returns the actual time in format DD/MM/YYYY
string get_actual_time() {
    time_t time1;
    struct tm *tm1;
    char buffer[80];
    time(&time1);
    tm1 = localtime(&time1);
    strftime(buffer, 80, "%d/%m/%Y", tm1);
    return buffer;
}

// Create the files for items and rental history. Pass it into the vectors.
void setup() {
    //Read from items.txt
    string line;
    ifstream it("../files/items.txt");
    if (it.is_open()) {
        while (getline(it, line)) {
            int i = 0;
            string item[10] = {};
            size_t pos = 0;
            string token;
            while ((pos = line.find('-')) != string::npos) {
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

            auto *ite = new Item(id, item[1], item[2], item[3], item[4], price, rented, sold, total);
            items.emplace_back(ite);
        }
        it.close();
    } else cout << "Unable to open file";

    //Read from users.txt
    string line2;
    ifstream us("../files/users.txt");
    if (us.is_open()) {
        while (getline(us, line)) {
            int i = 0;
            string user[10] = {};
            size_t pos = 0;
            string token;
            while ((pos = line.find('-')) != string::npos) {
                token = line.substr(0, pos);
                user[i] = token;
                i++;
                line.erase(0, pos + 1);
            }
            auto *usr = new Usr(user[0], user[1], user[2], user[3]);
            users.emplace_back(usr);

        }
        us.close();
    } else cout << "Unable to open file";
}

//Save the changes made into the files.
void save_changes() {
    //Save changes on items.txt file
    ofstream it;
    it.open("../files/items.txt", ofstream::out | ofstream::trunc);
    for (Item *item : items) {

        string to_write = to_string(item->getId()) + "-" + item->getType() + "-" + item->getBrand() + "-" +
                          item->getModel() + "-" + item->getSpecs() + "-" + to_string(item->getPrice()) +
                          "-" + to_string(item->getRented()) + "-" + to_string(item->getSold()) + "-" +
                          to_string(item->getTotal()) + "-";

        it << to_write << "\n";
    }
    it.close();

    //Save changes on users.txt file
    ofstream us;
    us.open("../files/users.txt", ofstream::out | ofstream::trunc);
    for (Usr *user : users) {
        string to_write = user->getUsername() + "-" + user->getName() + "-" + user->getSurname() + "-" +
                          user->getDatebirth() + "-";
        us << to_write << "\n";
    }
    us.close();
    cout << "Changes saved successful. See you next time and thank you!\n";
}

//Check if the username uname already exists.
bool username_exists(const string &string1) {
    for (Usr *user : users) {
        if (user->getUsername() == string1) {
            return true;
        }
    }
    return false;
}

//Ask the user for its username and returns it
string ask_username() {
    string username;
    cout << "Okay, first I need your username. You have to be registered.\n";
    cin >> username;
    while (!username_exists(username)) {
        cout << "This username is not in our database. Try again or 'esc' for return to main menu.\n";
        cin >> username;
        if (username == "esc") {
            return username;
        }
    }
    return username;
}

//Get the history of rents of an user given
vector<Rent *> get_user_rents(const string &username, bool print, bool renting) {
    vector<Rent *> rents;
    string line;
    ifstream r("../files/rental_history/" + username + ".txt");
    if (r.is_open()) {
        while (getline(r, line)) {
            int i = 0;
            string string1[10] = {};
            size_t pos = 0;
            string token;
            while ((pos = line.find('-')) != string::npos) {
                token = line.substr(0, pos);
                string1[i] = token;
                i++;
                line.erase(0, pos + 1);
            }
            if (print) {
                string returned;
                if (string1[3] == "0") {
                    returned = "NO";
                } else {
                    returned = "YES";
                }
                cout << "Rent ID: " + string1[0] + " Item ID: " + string1[1] + " Date: " + string1[2] + " Returned: " +
                        returned +
                        "\n";
            }
            auto *re = new Rent(stoi(string1[0]), stoi(string1[1]), string1[2], string1[3]);
            rents.emplace_back(re);
        }
        r.close();
    } else { if (!renting) { cout << "This user may not have rented."; }}
    return rents;
}

//Ask the user for the type of the item he wants
string ask_type() {
    string type;
    bool valid = false;
    while (!valid) {
        cout
                << "We have different types:\nL for Laptops.\nM for Mobile.\nD for Desktop.\nC for Console\nWhat do you want to rent?\n";
        cin >> type;
        if (type != "M" || type != "L" || type != "D" || type != "C") {
            valid = true;
        }
    }
    return type;
}

//Print the items, depending on if they have to be available or not
vector<Item *> print_items(bool av_rent, bool av_buy, const string &type) {
    vector<Item *> rent;
    for (Item *i : items) {
        if (av_rent) {
            if (i->getType() == type && i->getRented() > 0) { //Just print available products for rent
                rent.emplace_back(i);
                string item_to_print =
                        "ID " + to_string(i->getId()) + " - " + i->getBrand() + " " + i->getModel() + " / " +
                        i->getSpecs() +
                        "\t\tItems available: " +
                        to_string(i->getRented()) + "\n";
                cout << item_to_print;
            }
        } else if (av_buy) {
            if (i->getType() == type && i->getSold() > 0) { //Just print available products for sell
                rent.emplace_back(i);
                string item_to_print =
                        "ID " + to_string(i->getId()) + " - " + i->getBrand() + " " + i->getModel() + " / " +
                        i->getSpecs() +
                        "\t\tItems available: " +
                        to_string(i->getRented()) + "\n";
                cout << item_to_print;
            }
        } else {
            if (i->getType() == type) { //Print all products
                rent.emplace_back(i);
                string item_to_print =
                        "ID " + to_string(i->getId()) + " - " + i->getBrand() + " " + i->getModel() + " / " +
                        i->getSpecs() +
                        "\t\tItems available: " +
                        to_string(i->getRented()) + "\n";
                cout << item_to_print;
            }
        }

    }
    return rent;
}

//Ask the user for the id of the item wanted
string ask_item_id(vector<Item *> rent) {
    string item_for_rent;
    cout << "What item do you want? Choose one id:\n";
    cin >> item_for_rent;
    bool good_id = false;
    while (!good_id) {
        for (Item *i : rent) {
            if (item_for_rent == to_string(i->getId())) {
                i->setRented(i->getRented() - 1); //Decrease the rented available.
                good_id = true;
            }
        }
        if (!good_id) {
            cout << "The item has to be on the list. Try again:\n";
            cin >> item_for_rent;
        }
    }
    return item_for_rent;
}

//Function for renting items
void rent() {
    CreateDirectory("../files/rental_history", nullptr);

    string username = ask_username();

    if (username == "esc") {
        return;
    }

    string type = ask_type();

    cout << "Here you have the available items:\n";

    vector<Item *> rent = print_items(true, false, type);

    if (rent.empty()) {
        cout << "We don't have at this moments this kind of items. Sorry.\n";
        return;
    }

    string item_for_rent = ask_item_id(rent);

    vector<Rent *> rental_register = get_user_rents(username, false, true);

    //Create file in rental_history for the user or use an existing one.
    string actual_time = get_actual_time();

    ofstream us;
    us.open("../files/rental_history/" + username + ".txt", ofstream::out | ofstream::app);
    int new_id;
    if (!rental_register.empty()) {
        new_id = rental_register.back()->getRent_id() + 1;
    } else {
        new_id = 0;
    }
    string to_write = to_string(new_id) + "-" + item_for_rent + "-" + actual_time +
                      "-0-";
    us << to_write << "\n";
    us.close();
    cout << "Item rented perfectly! Thank you " + username;
}

//Function for return rented items
void return_item() {
    static vector<Rent *> rents_return;

    string username = ask_username();

    if (username == "esc") {
        return;
    }

    string line;
    ifstream r("../files/rental_history/" + username + ".txt");
    if (r.is_open()) {
        while (getline(r, line)) {
            int i = 0;
            string rent[10] = {};
            size_t pos = 0;
            string token;
            while ((pos = line.find('-')) != string::npos) {
                token = line.substr(0, pos);
                rent[i] = token;
                i++;
                line.erase(0, pos + 1);
            }
            string returned;
            if (rent[3] == "0") {
                returned = "NO";
                cout << "Rent ID: " + rent[0] + " / Item ID: " + rent[1] + " Date: " + rent[2] + " Returned: " +
                        returned +
                        "\n";
                auto *re = new Rent(stoi(rent[0]), stoi(rent[1]), rent[2], rent[3]);
                rents_return.emplace_back(re);
            }
        }
        r.close();
    } else cout << "Unable to open file. This user may not have rented.\n";

    if (rents_return.empty()) {
        cout << "You have all your items returned.\n";
        return;
    }

    int return_id = 0;
    cout << "Select the rent id you want to return:\n";
    cin >> return_id;

    bool good_id = false;
    while (!good_id) {
        for (Rent *rentsReturn : rents_return) {
            if (return_id == (*rentsReturn).getRent_id()) {
                for (Item *i:items) {
                    if (i->getId() == return_id) {
                        i->setRented(i->getRented() + 1); //Add one to the available for rent.
                    }
                }
                (*rentsReturn).setReturned("1");
                good_id = true;
            }
        }
        if (!good_id) {
            cout << "The rental has to be on the list. Try again:\n";
            cin >> return_id;
        }
    }

    ofstream us;
    us.open("../files/rental_history/" + username + ".txt", ofstream::out | ofstream::trunc);
    for (Rent *re:rents_return) {
        string to_write =
                to_string((*re).getRent_id()) + "-" + to_string((*re).getItem_id()) + "-" + (*re).getDate() + "-" +
                (*re).getReturned() + "-";
        us << to_write << "\n";
    }
    us.close();

    cout << "Item returned successful! Thank you " + username;
}

//Function for buy items
void buy() {
    string type = ask_type();

    vector<Item *> sell = print_items(false, true, type);

    if (sell.empty()) {
        cout << "We don't have at this moments this kind of items. Sorry.\n";
        return;
    }

    string item_for_sell = ask_item_id(sell);

    //Create file in rental_history for the user or use an existing one.
    string actual_time = get_actual_time();

    ofstream us;
    us.open("../files/sold.txt", ofstream::out | ofstream::app);
    string to_write = item_for_sell + "-" + actual_time + "-";
    us << to_write << "\n";
    us.close();
    cout << "Item bought perfectly! Thank you!";
}

//Function for show the rental history of an user
void rental_history() {
    string username = ask_username();

    if (username == "esc") {
        return;
    }
    cout << "Items rented by " + username + ":\n";
    vector<Rent *> r = get_user_rents(username, true, false);
}

//Ask info for new user and add it to the vector users.
void new_user() {
    string name, surname, date_birth, username;
    cout << "Okay, let's register you. What's your name?\n";
    cin >> name;
    cout << "What's your surname?\n";
    cin >> surname;
    cout << "What's your birthday date? (Format DD/MM/YYYY)\n";
    cin >> date_birth;
    cout << "Finally, choose your username:\n";
    cin >> username;
    while (username_exists(username)) {
        cout << "This username is already on use. Please select other:\n";
        cin >> username;
    }
    auto *us = new Usr(username, name, surname, date_birth);
    users.emplace_back(us);
    cout << "User " << username << " created successful.";
}

//Show the main menu with the options.
void main_menu() {
    int option;
    cout << "Welcome to our shop.";
    while (true) {
        cout
                << "\n\tWhat do you want to do?\n\t1. Rent. 2. Return item. 3. Buy 4. See your rental history. 5. Register new user. 6. Exit.\n";
        cin >> option;
        switch (option) {
            case 1:
                rent();
                break;
            case 2:
                return_item();
                break;
            case 3:
                buy();
                break;
            case 4:
                rental_history();
                break;
            case 5:
                new_user();
                break;
            case 6:
                return;
            default:
                cout << "Incorrect option.\n";
        }
    }

}

//Basic operations.
int main() {
    setup(); //Prepare the vectors with the file content.
    main_menu(); //Show main menu.
    save_changes(); //Save vector changes into the files.
    exit(0); //Finish program.
}
