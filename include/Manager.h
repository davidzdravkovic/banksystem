#ifndef MANEGER_H
#define MANEGER_H

#include "../include/User.h"
#include <vector>

class manager {
    public:
    std::vector<User*> users;
    void userCreate(int number);
    void listUser();
    void removeUser();
};

#endif