#ifndef USER_H
#define USER_H

#include "../include/Account.h"
#include <vector>
#include <string>

class User {
    protected:
   std :: string fullName;
    int personalID;
    int contact;
    std :: string address;
    public:
    std :: vector<Account*> accounts;
    std::string getFullName() const { return fullName; }
    int getPersonalID() const { return personalID;}
    int getContact() const {return contact;}
    std :: string getAddress() const {return address;}

    virtual void createUser()=0;
    virtual void print() const =0;

};
#endif