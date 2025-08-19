#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <string>
class User;
class Manager;
class Transactions {
    public:
    std::string sender;
    int receiverID;
    int receiverAccNum;
    double amount;
    void creatTrans(User *user,int personalID,int accountNumber,int sum,Manager &manager);
    void history(User *user);
    void decide(User *user);


};
#endif