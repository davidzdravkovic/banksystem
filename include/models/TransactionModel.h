#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H
#include "Manager.h"  
#include "Transactions.h"




class TransactionModel {
public:


static  bool validationTrans(pqxx::connection &conn,int receiverNumber,int senderNumber,int transactionType,double amount) {
    return Manager::transValidation(conn,receiverNumber,senderNumber,transactionType,amount);
  }
static bool createTransaction(pqxx::connection &conn,const int senderNumber,int receiverNumber, int transactionType,double amount) {
    return Transactions::createTrans(conn,senderNumber,receiverNumber,transactionType,amount);
 }
 static std::vector<Transactions> inbox(pqxx::connection &conn,int accountNumber) {
  return Transactions::printInbox(conn,accountNumber);
 }
  static std::vector<Transactions> sent(pqxx::connection &conn,int accountNumber) {
  return Transactions::printSent(conn,accountNumber);
 }
static double acceptTrans(pqxx::connection &conn,int transactionID) {
  return Transactions::acceptence(conn,transactionID);
 }
 static bool declineTrans(pqxx::connection &conn,int transactionID) {
  return Transactions::decline(conn,transactionID);
 }
static std::vector<Transactions> history(pqxx::connection &conn,int accountNumber) {
  return Transactions::printHistory(conn,accountNumber);
}
 static bool disabling(pqxx::connection &conn,int transactionID,int accountNumber) {
  return Transactions::disabler(conn,transactionID,accountNumber);
 }
  
    

};
#endif