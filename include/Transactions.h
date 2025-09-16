#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <string>
#include <pqxx/pqxx>
class User;
class Manager;
class Account;

class Transactions {
    public:
    std::string fullName;
    User *ptr=nullptr;
    int accountNumber;
    int indetification;
    std::string transactionType;
    std::string sender;
    std::string receiver;
    int transactionNumber;
    std::string date;
    double amount;
    int Htype;
    std::string transStatus;
    static bool createTrans(pqxx::connection &conn,const int senderNumber,int receiverNumber, int transactionType,double amount);
  static  std::vector<Transactions>  printSent(pqxx::connection &conn,int accountNumber);
  static  std::vector<Transactions>  printInbox(pqxx::connection &conn,int accountNumber);
  static  double acceptence(pqxx::connection &conn, int transactionID);
   static bool decline(pqxx::connection &conn,int transNumber);
   static std::vector<Transactions> printHistory(pqxx::connection &conn,int accountNumber);
  static bool disabler(pqxx::connection &conn, int transactionNumber,int accountNumber);
    
    
};
#endif