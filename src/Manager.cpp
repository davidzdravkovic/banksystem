#include "../include/Manager.h"
#include "../include/personalUser.h"
#include "../include/studentUser.h"
#include "../include/businessUser.h"
#include <iostream>

 void manager::userCreate(int number)  {
     User* user = nullptr;

    switch(number) {
        case 1:
            user = new personalUser();
            break;
        case 2:
            user = new businessUser();
            break;
        case 3:
            user = new studentUser();
            break;
        default:
            std::cout << "Invalid number!" << std::endl;
            return;
    }

    user->createUser();
    users.push_back(user);
    user->print();
}
    

void manager::listUser() {
    for(int i = 0; i < users.size(); i++) {
        std::cout << "Full name: " << users[i]->getFullName() << std::endl;
        std::cout << "Personal ID: " << users[i]->getPersonalID() << std::endl;
        std::cout << "Contact: " << users[i]->getContact() << std::endl;
        std::cout << "Address: " << users[i]->getAddress() << std::endl;
    }
}

void manager::removeUser() {
    for(int i=0; i<users.size(); i++) {

    }

}