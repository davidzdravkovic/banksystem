#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
class User;
class Account {
   protected:
    std :: string owner;
    double balance;
    int accountNumber;
    std :: string accountType;
    public:
    int getAccountNumber() {return accountNumber;}
    std :: string accountTime;
    std :: string getOwnerName() {return owner;}
    int getBalance(){return balance;}
    virtual bool createAccount(std::vector<User*> &users, int personalID)=0;
    virtual void deposit (double amount)= 0;
    virtual void withdraw (double amount)=0;
    virtual void printAccount()=0;


};
#endif