#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
#include <Transactions.h>
class User;
class Account {
   protected:
    std :: string owner;
    double balance;
    int accountNumber;
   
    std :: string accountType;
    std :: string accountTime;
    public:
     double transAmount;
    std::vector<Transactions*> transInbox;
    std::vector<Transactions*> transSent;
    std::string getAccountType() {return accountType;}
    void SetAccountType(std::string accType) {accountType=accType;}
    int getAccountNumber() {return accountNumber;}
    std::string getAccountTime() {return accountTime;}
    void setAccountTime(std::string Atime) {accountTime=Atime;}
    std :: string getOwnerName() {return owner;}
    int getBalance(){return balance;}
    void setBalanceDepo(double amount) {if (amount > 0) balance+=amount;}
    void setBalanceWith(double amount) { if (amount > 0 && amount <= balance)balance-=amount;}
    virtual bool createAccount(std::vector<User*> &users, int personalID)=0;
    virtual void deposit (User *user,int accountNumber,double amount)= 0;
    virtual void withdraw (User *user,int accountNumber,double amount)=0;
    virtual void printAccount(User *user,int accountNumber)=0;


};
#endif