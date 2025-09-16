#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H
#include "Account.h"


class SavingAccount : public  Account
{public:
 std::shared_ptr<Account> createAccount(pqxx::connection &conn,std::shared_ptr<Account> account,int number)override;
 double deposit(pqxx::connection &conn,double amount,int accountNumber) override;
 double withdraw(pqxx::connection &conn,double amount,int accountNumber)override;

};


#endif
