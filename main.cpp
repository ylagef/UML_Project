#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "Item.h"
#include "Usr.h"
#include "Rent.h"

using namespace std;

vector<Item> items;
vector<Usr> users;

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

            items.emplace_back(id, item[1], item[2], item[3], item[4], price, rented, sold, total);
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

            users.emplace_back(user[0], user[1], user[2], user[3]);

        }
        us.close();
    } else cout << "Unable to open file";
}

//Save the changes made into the files.
void save_changes() {
    //Save changes on items.txt file
    ofstream it;
    it.open("../files/items.txt", ofstream::out | ofstream::trunc);
    for (const Item &item : items) {

        string to_write = to_string(item.getId()) + "-" + item.getType() + "-" + item.getBrand() + "-" +
                          item.getModel() + "-" + item.getSpecs() + "-" + to_string(item.getPrice()) +
                          "-" + to_string(item.getRented()) + "-" + to_string(item.getSold()) + "-" +
                          to_string(item.getTotal()) + "-";

        it << to_write << "\n";
    }
    it.close();

    //Save changes on users.txt file
    ofstream us;
    us.open("../files/users.txt", ofstream::out | ofstream::trunc);
    for (const Usr &user : users) {
        string to_write = user.getUsername() + "-" + user.getName() + "-" + user.getSurname() + "-" +
                          user.getDatebirth() + "-";
        us << to_write << "\n";
    }
    us.close();
}

//Check if the username uname already exists.
bool username_exists(const string &string1) {
    for (auto &user : users) {
        if (user.getUsername() == string1) {
            return true;
        }
    }
    return false;
}

void rent() {
    string username;
    cout << "Okay, first I need your username. You have to be registered for rent: ";
    cin >> username;
    while (!username_exists(username)) {
        cout << "This username is not in our database. Try again: ";
        cin >> username;
    }

    string type;
    bool valid = false;
    while (!valid) {
        cout
                << "We have different types:\nL for Laptops.\nM for Mobile.\nD for Desktop.\nC for Console\nWhat do you want to rent?";
        cin >> type;
        if (type != "M" || type != "L" || type != "D" || type != "C") {
            valid = true;
        }
    }

    vector<Item> rent;
    for (Item i : items) {
        if (i.getType() == type && i.getRented() > 0) { //Just print available products
            rent.emplace_back(i);
            string item_to_print =
                    "ID " + to_string(i.getId()) + " - " + i.getBrand() + " " + i.getModel() + " / " + i.getSpecs() +
                    "\t\tItems available: " +
                    to_string(i.getRented()) + "\n";
            cout << item_to_print;
        }
    }

    string item_for_rent;
    cout << "What item do you want? Choose one id:";
    cin >> item_for_rent;
    bool good_id = false;
    while (!good_id) {
        for (Item i : rent) {
            if (item_for_rent == to_string(i.getId())) {
                i.setRented(i.getRented() - 1); //Decrease the rented available. //TODO Fix this.
                good_id = true;
            }
        }
        if (!good_id) {
            cout << "The item has to be on the list. Try again: ";
            cin >> item_for_rent;
        }
    }
    vector<Rent *> rents;
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
            Rent *re = new Rent(stoi(rent[0]), stoi(rent[1]), rent[2], rent[3]);
            rents.emplace_back(re);
        }
        r.close();
    } else cout << "Unable to open file. This user may not have rented.\n";

    //Create file in rental_history for the user or use an existing one.
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d/%m/%Y", timeinfo);

    ofstream us;
    us.open("../files/rental_history/" + username + ".txt", ofstream::out | ofstream::app);
    string to_write = to_string(rents.back()->getRent_id() + 1) + "-" + item_for_rent + "-" + buffer +
                      "-0-"; //TODO rents.back() not working
    us << to_write << "\n";
    us.close();
    cout << "Item rented perfectly! Thank you " + username + "\n\n";
}

void return_item() {
    static vector<Rent *> rents_return;

    string username;
    cout << "Okay, first I need your username. You have to be registered: ";
    cin >> username;
    while (!username_exists(username)) {
        cout << "This username is not in our database. Try again: ";
        cin >> username;
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
                Rent* re = new Rent(stoi(rent[0]), stoi(rent[1]), rent[2], rent[3]);
                rents_return.emplace_back(re);
            }
        }
        r.close();
    } else cout << "Unable to open file. This user may not have rented.\n";

    int return_id = 0;
    cout << "Select the rent id you want to return:";
    cin >> return_id;

    bool good_id = false;
    while (!good_id) {
        for (Rent *r : rents_return) {
            if (return_id == (*r).getRent_id()) {
                for (Item i:items) {
                    if (i.getId() == return_id) {
                        i.setRented(i.getRented() + 1); //Add one to the available for rent. //TODO Fix this
                    }
                }
                (*r).setReturned("1"); //TODO este es el set que te digo que es necesario pero no funciona
                good_id = true;
            }
        }
        if (!good_id) {
            cout << "The rental has to be on the list. Try again: ";
            cin >> return_id;
        }
    }

    ofstream us;
    us.open("../files/rental_history/" + username + ".txt", ofstream::out | ofstream::trunc);
    for (Rent *r:rents_return) {
        string to_write =
                to_string((*r).getRent_id()) + "-" + to_string((*r).getItem_id()) + "-" + (*r).getDate() + "-" +
                (*r).getReturned() + "-";
        us << to_write << "\n";
    }
    us.close();

    cout << "Item returned successful! Thank you " + username + "\n";
}

void buy() {
    string type;
    bool valid = false;
    while (!valid) {
        cout
                << "We have different types:\nL for Laptops.\nM for Mobile.\nD for Desktop.\nC for Console\nWhat do you want to buy?";
        cin >> type;
        if (type != "M" || type != "L" || type != "D" || type != "C") {
            valid = true;
        }
    }

    vector<Item> sell;
    for (Item i : items) {
        if (i.getType() == type && i.getTotal() > 0) { //Just print available products
            sell.emplace_back(i);
            string item_to_print =
                    "ID " + to_string(i.getId()) + " - " + i.getBrand() + " " + i.getModel() + " / " + i.getSpecs() +
                    "\t\tItems available: " +
                    to_string(i.getTotal()) + "\n";
            cout << item_to_print;
        }
    }

    string item_for_sell;
    cout << "What item do you want? Choose one id:";
    cin >> item_for_sell;
    bool good_id = false;
    while (!good_id) {
        for (Item i : sell) {
            if (item_for_sell == to_string(i.getId())) {
                i.setTotal(i.getTotal() - 1); //Decrease the total.     //TODO this set is not working.
                i.setSold(i.getSold() + 1); //Increase the sold value.  //TODO this set is not working
                good_id = true;
            }
        }
        if (!good_id) {
            cout << "The item has to be on the list. Try again: ";
            cin >> item_for_sell;
        }
    }

    //Create file in rental_history for the user or use an existing one.
    time_t time1;
    struct tm *tm1;
    char buffer[80];
    time(&time1);
    tm1 = localtime(&time1);
    strftime(buffer, 80, "%d/%m/%Y", tm1);

    ofstream us;
    us.open("../files/sold.txt", ofstream::out | ofstream::app);
    string to_write = item_for_sell + "-" + buffer + "-";
    us << to_write << "\n";
    us.close();
    cout << "Item bought perfectly! Thank you!\n\n";
}

void rental_history() {
    string username;
    cout << "Okay, tell me your username: ";
    cin >> username;
    while (!username_exists(username)) {
        cout << "This username is not in our database. Try again: ";
        cin >> username;
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
            } else {
                returned = "YES";
            }
            cout << "Rent ID: " + rent[0] + " Item ID: " + rent[1] + " Date: " + rent[2] + " Returned: " + returned +
                    "\n";
        }
        r.close();
    } else cout << "Unable to open file. This user may not have rented.\n";
}

//Ask info for new user and add it to the vector users.
void new_user() {
    string name, surname, date_birth, username;
    cout << "Okay, let's register you. What's your name?";
    cin >> name;
    cout << "What's your surname?";
    cin >> surname;
    cout << "What's your birthday date? (Format DD/MM/YYYY)";
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

//Show the main menu with the options.
void main_menu() {
    int option;
    cout << "Welcome to our shop.";
    while (true) {
        cout
                << " What do you want to do?\n1. Rent. 2. Return item. 3. Buy 4. See your rental history. 5. Register new user. 6. Exit.";
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
                cout << "Incorrect option.";
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
