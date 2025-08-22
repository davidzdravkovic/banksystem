#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <string>
class User;
class Manager;
class Account;

class Transactions {
    public:
    int accountNumber;
    int indetification;
    int transactionType;
    std::string sender;
    std::string receiver;
    double amount1;
    int transactionNumber;
    std::string date;
    double amount;
    std::string transStatus;
    Transactions*createTrans(Manager &manager,Account *acc,User *user);
    void printSent(Account *acc);
    void printInbox(Account *acc);
    void decision(Manager &manager, Account *acc,Transactions*trans);
    
    
    
};
#endif