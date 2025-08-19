#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/Account.h"
#include "../include/personalUser.h"
#include "../include/studentUser.h"
#include "../include/businessUser.h"
#include "../include/functions.h"
#include <iostream>
#include <ctime>

 User& Manager::userCreate(int number)  {
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
            throw std::runtime_error("Invalid user type");    }

    user->createUser();
    users.push_back(user);
    return *user;
}



 void Manager::accountCreate(int number) {
    User* user=nullptr;
    bool exist=false;
for(int i=0; i<users.size(); i++) {
    if(users[i]->getPersonalID()==number) {
        user=users[i];
        exist=true;
     break;

    }


}
if(exist) { 
    accounts();
    int option=digitVal("Choose account that you want to create: ");
  
    Account* acc=nullptr;
    switch (option) {
    
    case 1:
    acc=new CheckingAccount();
   
        break;
    
    default :
        break;
    }
    bool approved=false;
    approved=acc->createAccount(users,number);
    if(approved) {
    user->getAccounts().push_back(acc);
    std :: cout<<"Account owner name: "<<acc->getOwnerName()<<std::endl;
    std::cout<<"Account created on: "<<getCurrentTime()<<std::endl;
    }

}
else{
std::cout<<"User does not exist!"<< std::endl;
}

 
}
void Manager::listUser() {
    for(int i = 0; i < users.size(); i++) {
        std::cout << "Full name: " << users[i]->getFullName() << std::endl;
        std::cout << "Personal ID: " << users[i]->getPersonalID() << std::endl;
        std::cout << "Contact: " << users[i]->getContact() << std::endl;
        std::cout << "Address: " << users[i]->getAddress() << std::endl;
    }
}

void Manager::removeUser() {
    for(int i=0; i<users.size(); i++) {

    }

}
void Manager::printProfiles() {
  std :: cout<< "Personal user profile"<< std :: endl;
  std :: cout<< "Business user profile"<< std :: endl;
  std :: cout<< "Student user profile"<< std :: endl;
}
User* Manager::getTheLastUser() {
    if(!users.empty()) {
        return users.back();
    }
    return nullptr;
}
void Manager :: promt() {
  std :: cout<<"1. Sign up"<< std :: endl;
  std :: cout<<"2. See the list of users!"<< std :: endl;
  std :: cout<<"3. Exit!"<<std :: endl;
}
void Manager :: accounts() {
    std:: cout<<"1. Checking account"<< std :: endl;
    std:: cout<<"2.Credit account"<< std :: endl;
    std:: cout<<"1.Saving account"<< std :: endl;
}