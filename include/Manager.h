#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include "User.h"
class Account;
class User;
class Manager {
 private:
    std::vector<User*> users;
    public:
    std::vector<User*> &getUsers () {return users;}
    User* getTheLastUser();
  //  static User* userCreate(int number,pqxx::connection &conn);
    // Account* accountCreate(pqxx::connection &conn,int number);
    void removeUser();
    void printProfiles();
    void promt();
    void typeAccounts();
  static  User* checkPass(pqxx::connection &conn,const int personalID,const std::string password,int userOption);
 static std::vector<std::shared_ptr<Account>> checkAccountNum(pqxx::connection &conn,int personalID);
    void userPromt ();
    void printTrans();
    void transOption();
    int transactionProfile( Account *acc,pqxx::connection &conn,bool listInbox,bool listSent);
    void decisionPrint(bool listInbox,bool listSent);
   static bool transValidation(pqxx::connection &conn,const int sendecNumber,int receiverNumber, int transactionType, double amount);
   static std::shared_ptr<Account> getAccount (pqxx::connection &conn,int accNumber);
};
#endif