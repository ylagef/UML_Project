//
// Created by ylage on 13/01/2018.
//

#ifndef PROJECT_USR_H
#define PROJECT_USR_H

#include <iostream>

using namespace std;

class Usr {
private:
    string username;
    string name;
    string surname;
    string datebirth;

public:
    Usr() {}

    Usr(const string &username, const string &name, const string &surname, const string &datebirth);

    virtual ~Usr();

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getName() const;

    void setName(const string &name);

    const string &getSurname() const;

    void setSurname(const string &surname);

    const string &getDatebirth() const;

    void setDatebirth(const string &datebirth);
};


#endif //PROJECT_USR_H
