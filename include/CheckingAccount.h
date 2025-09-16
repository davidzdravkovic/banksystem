#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include "Account.h"


class CheckingAccount : public  Account
{public:
  
   std::shared_ptr<Account> createAccount(pqxx::connection &conn,std::shared_ptr<Account> account,int number)override;
 double deposit(pqxx::connection &conn,double amount,int accountNumber) override;
 double withdraw(pqxx::connection &conn,double amount,int accountNumber)override;
  
};


#endif
