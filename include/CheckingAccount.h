#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include "Account.h"
#include <vector>

class CheckingAccount : public  Account
{public:
  bool createAccount(std::vector<User*> &users, int personalID)override;
  void deposit(double amount) override;
  void withdraw(double amount)override;
  void printAccount()override;
};


#endif
