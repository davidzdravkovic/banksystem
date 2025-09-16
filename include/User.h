#ifndef USER_H
#define USER_H
#include "Account.h"
#include <vector>
#include <string>
#include <pqxx/pqxx>
class Account;

class User {
    protected:
    std :: string password;
    std :: string userType;
    std :: string fullName;
    int personalID;
    int contact;
    std::string address;
    std::vector<Account*> accounts;
    
    public:
    std::string getUserType() {return userType;}
    std::string getUsersPass() {return password;}
    void setUsersPass(std::string pass) {password=pass;}
    void setUserType (std::string Utype) {userType=Utype;}
    std::vector<Account*> &getAccounts() {return accounts;}
    std::string getFullName() const { return fullName; }
    void setFullName(std::string name) {fullName=name;}
    int getPersonalID() const { return personalID;}
    void setPersonalID(int persID) {personalID=persID;}
    int getContact() const {return contact;}
    void setContact(int cont) {contact=cont;}
    std :: string getAddress() const {return address;}
    void setAddress(std::string add) {address=add;}

    virtual bool createUser(pqxx::connection &conn,std::shared_ptr<User> user)=0;
    virtual void printUsers(pqxx::connection &conn) const =0;
    virtual void printAccounts(pqxx::connection &conn) const=0;
};
#endif