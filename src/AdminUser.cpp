#include "../include/AdminUser.h"
#include "../include/Manager.h"
#include "../include/functions.h"
#include <iostream>
#include <cctype>
#include "../include/CheckingAccount.h"
#include "../include/User.h"




void AdminUser :: adminProfile() {
      std::string displayName = name; 
    if (!name.empty()) {
   displayName[0] = std::toupper(displayName[0]);
}
 std::cout<<"Name: "<<displayName<<std::endl;

 std::cout<<"1.List users. "<<std::endl;
 std::cout<<"2.View all accounts. "<<std::endl;
 std::cout<<"3.Exit!"<<std::endl;

}
void AdminUser :: listUser(Manager &manager) {
    if(manager.getUsers().empty()) {
        std::cout<<"No user on the list!"<<std::endl;
        return;
    }
    for(int i = 0; i < manager.getUsers().size(); i++) {
        std::cout << "User type: " <<manager.getUsers()[i]->getUserType() << std::endl;
        std::cout << "Full name: " <<manager.getUsers()[i]->getFullName() << std::endl;
        std::cout << "Personal ID: " <<manager.getUsers()[i]->getPersonalID() << std::endl;
        std::cout << "Contact: " << manager.getUsers()[i]->getContact() << std::endl;
      
    }
}
void AdminUser :: viewAccounts (Manager &manager) {
     if(manager.getUsers().empty()) {
        std::cout<<"No user on the list!"<<std::endl;
        return;
    }
    
    for(int i = 0; i < manager.getUsers().size(); i++) {
        std::cout<<i+1.<<"User's name: "<<manager.getUsers()[i]->getFullName()<<"  "
        <<"User's personal ID "<<manager.getUsers()[i]->getPersonalID()<<std::endl;
       
    } 
    int personalID=digitVal("Enter user's personal ID: ");
     for(int i = 0; i < manager.getUsers().size(); i++) 
     {
        if(manager.getUsers()[i]->getPersonalID()==personalID)
         {
   for(int j=0; j<manager.getUsers()[i]->getAccounts().size(); j++)
    {
    std::cout<<"Account type: "<<manager.getUsers()[i]->getAccounts()[j]->getAccountType()<<"  "
    <<"Account number: "<<manager.getUsers()[i]->getAccounts()[j]->getAccountNumber()<<"  "
    <<"Balance: "<<manager.getUsers()[i]->getAccounts()[j]->getBalance()<<std::endl;

} 
     }

}



}