#ifndef ACCOUNT_H
#define ACCOUNT_H
class Account {
   protected:
    double balance;
    int accountNumber;
    public:
     
    virtual void deposit (double amount)= 0;
    virtual void withdraw (double amount)=0;


};
#endif