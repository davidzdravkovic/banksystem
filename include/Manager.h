#ifndef MANAGER_H
#define MANAGER_H
#include "../include/User.h"
#include <vector>

class Manager {
 private:
    std::vector<User*> users;
    public:
    std::vector<User*> &getUsers () {return users;}
    User* getTheLastUser();
    User& userCreate(int number);
    void accountCreate(int number);
    void listUser();
    void removeUser();
    void printProfiles();
    void promt();
    void accounts();
};

#endif