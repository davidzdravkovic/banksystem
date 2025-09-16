#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
#include <pqxx/pqxx>

class Transactions;
class User;
class Account {
   protected:
    std :: string owner;
    double balance;
    int accountNumber;
    double totalWitdraw;
    double totalDeposit;
    int transactionsMade;
    std :: string accountType;
    std :: string accountTime;
    public:
     double transAmount;
    
    std::vector<Transactions*> transHistory;
    std::vector<Transactions*> transInbox;
    std::vector<Transactions*> transSent;
    void setTotalWithdraw(double withdrawTotal) {totalWitdraw=withdrawTotal;}
    double getTotalWithdraw(){return totalWitdraw;}

    void setTotalDeposite(double depositeTotal) {totalDeposit=depositeTotal;}
    double getTotalDeposite(){return totalDeposit;}

    void setTransactionsMade(int transMade) {transactionsMade=transMade;}
    int getTransactionsMade() {return transactionsMade;}

    std::string getAccountType() {return accountType;}
    void SetAccountType(std::string accType) {accountType=accType;}

    int getAccountNumber() {return accountNumber;}
    void setAccountNumber(int number) {accountNumber=number;}

    std::string getAccountTime() {return accountTime;}
    void setAccountTime(std::string Atime) {accountTime=Atime;}

    std :: string getOwnerName() {return owner;}
    void setOwnerName(std::string name) {owner=name;}

    int getBalance(){return balance;}
    void setBalance(double amount) {balance=amount;}

    void setBalanceDepo(double amount) {if (amount > 0) balance+=amount;}
    void setBalanceWith(double amount) { if (amount > 0 && amount <= balance)balance-=amount;}

    virtual  std::shared_ptr<Account> createAccount(pqxx::connection &conn,std::shared_ptr<Account> account,int number)=0;
    virtual  double deposit (pqxx::connection &conn,double amount,int accountNumber)= 0;
    virtual  double withdraw (pqxx::connection &conn,double amount,int accountNumber)=0;
    


};
#endif