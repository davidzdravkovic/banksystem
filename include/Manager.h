#ifndef MANAGER_H
#define MANAGER_H
#include "User.h"
#include <vector>

class Manager {
 private:
    std::vector<User*> users;
    public:
    std::vector<User*> &getUsers () {return users;}
    User* getTheLastUser();
    User* userCreate(int number);
    Account* accountCreate(int number);
    void listUser();
    void removeUser();
    void printProfiles();
    void promt();
    void typeAccounts();
    void logIN(int personalID,std::string password);
    User* checkPass(std::string password,int personalID);
    Account* checkAccountNum(User *user,int accountNumber);
    void userPromt ();
    void printTrans();
    void transOption();
    void transactionProfile( Account *acc);
};
#endif