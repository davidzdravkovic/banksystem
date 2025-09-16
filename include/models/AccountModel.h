#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H
#include <iostream>
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "CreditAccount.h"
#include "Manager.h"




class AccountModel {
public:
std::shared_ptr<CheckingAccount> checkingacc=nullptr;
std::shared_ptr<CreditAccount> creditacc=nullptr;
std::shared_ptr<SavingAccount> savingacc=nullptr;




   std::shared_ptr<Account> createCheckAccount (pqxx::connection &conn,std::shared_ptr<CheckingAccount> account,int number) {
    if(!account) {
    return nullptr;
    }
    return account->createAccount(conn,account,number);
}

   std::shared_ptr<Account> createCreditAccount (pqxx::connection &conn,std::shared_ptr<CreditAccount> account,int number) {
    if(!account) {
    return nullptr;
    }
    return account->createAccount(conn,account,number);
}

   std::shared_ptr<Account> createSavingkAccount (pqxx::connection &conn,std::shared_ptr<SavingAccount> account,int number) {
    if(!account) {
    return nullptr;
    }
    return account->createAccount(conn,account,number);
}
 static  std::vector<std::shared_ptr<Account>> searchAccount (pqxx::connection &conn,int personalID) {
    return Manager::checkAccountNum(conn,personalID);
}
    double deposit(pqxx::connection &conn,double amount,int accountNumber) {
    auto account = Manager::getAccount(conn,accountNumber);
    if(!account) return -1;
    return account->deposit(conn,amount,accountNumber);
}
   double withdraw(pqxx::connection &conn,double amount,int accountNumber) {
    auto account = Manager::getAccount(conn,accountNumber);
    if(!account) return -1;
    return account->withdraw(conn,amount,accountNumber);
}

};
#endif