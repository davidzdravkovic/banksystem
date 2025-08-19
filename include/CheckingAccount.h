#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include "Account.h"
#include <vector>

class CheckingAccount : public  Account
{public:
  bool createAccount(std::vector<User*> &users, int personalID)override;
  void deposit(User *user,int accountNumber,double amount) override;
  void withdraw(User *user,int accountNumber,double amount)override;
  void printAccount(User *user,int accountNumber)override;
};


#endif
