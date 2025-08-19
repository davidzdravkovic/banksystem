#ifndef USER_H
#define USER_H
#include "Account.h"
#include "Manager.h"
#include <vector>
#include <string>
class Manager;
class User {
    protected:
    std :: string password;
    std :: string userType;
    std :: string fullName;
    int personalID;
    int contact;
    std :: string address;
    std :: vector<Account*> accounts;
    
    public:
    std::string getUserType() {return userType;}
    std::string getUsersPass() {return password;}
    void setUserType (std::string Utype) {userType=Utype;}
    std::vector<Account*> &getAccounts() {return accounts;}
    std::string getFullName() const { return fullName; }
    int getPersonalID() const { return personalID;}
    int getContact() const {return contact;}
    std :: string getAddress() const {return address;}

    virtual bool createUser(std::vector<User*> &users)=0;
    virtual void printUsers() const =0;
    virtual void printAccounts(User *user) const=0;
};
#endif