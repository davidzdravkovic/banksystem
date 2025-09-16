#include "../include/Transactions.h"
#include "../include/Manager.h"
#include <iostream>
#include "../include/functions.h"
#include "../include/Account.h"
#include "../include/User.h"
#include <vector>
#include <algorithm>
#include <pqxx/pqxx>

extern Manager manager;

   bool Transactions :: createTrans(pqxx::connection &conn,const int senderNumber,int receiverNumber, int transactionType,double amount)  {
   std::string status="Pending";

   try{
    pqxx::work txn(conn);
    pqxx::result r1=txn.exec_params("INSERT INTO transactions (from_account,to_account,amount,transaction_type,status) VALUES "
    "($1,$2,$3,$4,$5)",
    senderNumber,receiverNumber,amount,transactionType,status);
    txn.commit();
    return true;
}
     catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return false ;
  }
return false;
   }

std::vector<Transactions> Transactions :: printSent(pqxx::connection &conn,int accountNumber) {
   std::vector<Transactions> trans;
    try{
        pqxx::work txn(conn);
        pqxx::result r=txn.exec_params("SELECT distinct  transaction_id,amount,transaction_type, receiver.full_name as receiver_name FROM transactions t INNER "
      " JOIN accounts receiver ON t.to_account = receiver.account_number  WHERE  from_account=$1 AND active=true",accountNumber);

    if(r.empty()) {
        
        return trans;
    }
   for(int i=0; i<r.size(); i++) {
        Transactions transact;
        transact.receiver=r[i]["receiver_name"].as<std::string>();
        transact.transactionNumber=r[i]["transaction_id"].as<int>();
        transact.amount=r[i]["amount"].as<double>();
        transact.transactionType=r[i]["transaction_type"].as<std::string>();
        trans.push_back(transact);
   }
 return trans;
        
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return trans;
  }
  return trans;
    
}

std::vector<Transactions>  Transactions :: printInbox(pqxx::connection &conn,int accountNumber) {
  std::vector<Transactions> trans;
    try{
        pqxx::work txn(conn);
        pqxx::result r=txn.exec_params("SELECT distinct  transaction_id,amount,transaction_type, sender.full_name as sender_name FROM transactions t INNER "
      " JOIN accounts sender ON t.from_account = sender.account_number  WHERE to_account=$1  AND active=true",accountNumber);

    if(r.empty()) {
        std::cout<<"Empty inbox!"<<std::endl;
        return trans;
    }
   for(int i=0; i<r.size(); i++) {
        Transactions transact;
        transact.sender=r[i]["sender_name"].as<std::string>();
        transact.transactionNumber=r[i]["transaction_id"].as<int>();
         transact.amount=r[i]["amount"].as<double>();
         transact.transactionType=r[i]["transaction_type"].as<std::string>();
        trans.push_back(transact);
   }
   return trans;

        
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return trans;
  }
  return trans;
    

   
 }
double Transactions :: acceptence(pqxx::connection &conn,int transactionID) {
  
    try{
      
        pqxx::work txn(conn);
        pqxx::result r=txn.exec_params("SELECT amount,transaction_type,from_account,active,to_account FROM transactions WHERE transaction_id=$1 AND active"
        ,transactionID);

          if (r.empty()) {
            std::cout << "Empty inbox!" << std::endl;
            return -1;
        }

        double amount=r[0]["amount"].as<double>();
        int transactionType=r[0]["transaction_type"].as<int>();
        int accountSender=r[0]["from_account"].as<int>();
        int accountReceiver=r[0]["to_account"].as<int>();
        bool isActive=r[0]["active"].as<bool>();

       
         pqxx::result r1=txn.exec("SELECT balance,account_type FROM ONLY accounts WHERE account_number=$1",accountSender);
         double balanceSender=r1[0]["balance"].as<double>();
         std::string accTypeS=r1[0]["account_type"].as<std::string>();

         pqxx::result r2=txn.exec("SELECT balance,account_type FROM ONLY accounts WHERE account_number=$1",accountReceiver);
         double balanceReceiver=r2[0]["balance"].as<double>();
         std::string accTypeR=r2[0]["account_type"].as<std::string>();
        


         if(accountSender==accountReceiver) {
          return -1;
         }
      
        
   
        if(transactionType==1&&balanceSender>=amount) {

        balanceReceiver += amount;
        balanceSender -= amount;

    if(isActive) {
    txn.exec_params("UPDATE transactions SET status=$1, active=$2 WHERE transaction_id=$3 AND active=true"
    ,"Accepted",false,transactionID);
    
    std::string query1= "UPDATE accounts SET balance=$1  WHERE account_number=$2";
    txn.exec_params(query1, balanceReceiver, accountReceiver);

    std::string queryR = "UPDATE " + accTypeR + " SET balance=$1  WHERE account_number=$2";
    txn.exec_params(queryR, balanceReceiver,accountReceiver);

    std::string query2= "UPDATE accounts SET balance=$1  WHERE account_number=$2";
    txn.exec_params(query2, balanceSender, accountSender);

    std::string queryS = "UPDATE " + accTypeS + " SET balance=$1  WHERE account_number=$2";
    txn.exec_params(queryS, balanceSender,accountSender);

    txn.commit();
    return balanceReceiver;
        }
      }
    else if (transactionType == 2 &&balanceReceiver>=amount) {
    
    balanceReceiver -= amount;
    balanceSender += amount;
     if(isActive) {
    txn.exec_params("UPDATE transactions SET status=$1, active=$2 WHERE transaction_id=$3 AND active=true"
    ,"Accepted",false,transactionID);

    std::string query1= "UPDATE accounts SET balance=$1  WHERE account_number=$2";
    txn.exec_params(query1, balanceReceiver, accountReceiver);

    std::string queryR = "UPDATE " + accTypeR + " SET balance=$1  WHERE account_number=$2";
    txn.exec_params(queryR, balanceReceiver, accountReceiver);

    std::string query2= "UPDATE accounts SET balance=$1  WHERE account_number=$2";
    txn.exec_params(query2, balanceSender, accountSender);

    std::string queryS = "UPDATE " + accTypeS + " SET balance=$1  WHERE account_number=$2";
    txn.exec_params(queryS, balanceSender,accountSender);

    txn.commit();
    return balanceReceiver;
}

    }
           
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
    return -1;
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
   return -1;
  }
 
    return -1;
    
 }
      
     

bool Transactions :: decline(pqxx::connection &conn,int transNumber) {
    try{
        pqxx::work txn(conn);
       txn.exec_params("UPDATE transactions SET status=$1, active=$2 WHERE transaction_id=$3 ","Decline",false,transNumber);
       txn.commit();
       return true;
           
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   return false;
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
   return false;
  }
 
    
    
 }
      

std::vector<Transactions> Transactions :: printHistory(pqxx::connection &conn,int accountNumber) {
  std::vector<Transactions> transactions;
    try {
        pqxx::work txn(conn);
     pqxx::result r = txn.exec_params(
    "SELECT distinct status,transaction_type, transaction_id,amount, sender.full_name as sender_name, receiver.full_name as receiver_name FROM transactions t "
    " INNER JOIN accounts sender ON  t.from_account = sender.account_number "   
    "INNER JOIN accounts receiver ON t.to_account = receiver.account_number  WHERE active=false AND ((from_account=$1 AND visible_to_sender=true) "
    "   OR (to_account=$1 AND visible_to_receiver=true))", accountNumber);

      
        for(int i=0; i<r.size(); i++) {
          Transactions trans;
         trans.sender = r[i]["sender_name"].as<std::string>();
         trans.receiver = r[i]["receiver_name"].as<std::string>();
            trans.transStatus=r[i]["status"].as<std::string>();
            trans.transactionType=r[i]["transaction_type"].as<std::string>();
            trans.transactionNumber=r[i]["transaction_id"].as<int>();
            trans.amount=r[i]["amount"].as<double>();
           transactions.push_back(trans);
            
        }
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   return transactions;
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
   return transactions;
  }
  return transactions;

}
 

bool Transactions::disabler (pqxx::connection &conn,int transactionNumber,int accountNumber) {
  try {

    pqxx::work txn(conn);
     pqxx::result r = txn.exec_params("SELECT to_account,from_account FROM transactions WHERE active=false AND (to_account=$1 OR from_account=$1) AND "
     " transaction_id=$2",accountNumber,transactionNumber);

    int numberReceivere=r[0]["to_account"].as<int>();
    int numberSendere=r[0]["from_account"].as<int>();

    std::cout<<numberReceivere<<std::endl;
    std::cout<<numberSendere<<std::endl;

      if (r.empty()) {
        std::cout<<"Empty"<<std::endl;
            return false;
        }

    int numberReceiver=r[0]["to_account"].as<int>();
    int numberSender=r[0]["from_account"].as<int>();

       bool updated = false;

    std::cout<<numberReceiver<<std::endl;
    std::cout<<numberSender<<std::endl;

    std::cout<<accountNumber<<std::endl;

    if(numberSender==accountNumber) {
    pqxx::result r1 = txn.exec_params("UPDATE transactions SET visible_to_sender=$1 WHERE active=false AND from_account=$2 AND "
     "transaction_id=$3",false,accountNumber,transactionNumber);
    updated=true;
    }
     if(numberReceiver==accountNumber) {
      pqxx::result r2 = txn.exec_params("UPDATE transactions SET visible_to_receiver=$1 WHERE active=false AND to_account=$2 AND "
     "transaction_id=$3",false,accountNumber,transactionNumber);
     updated=true;
   
    }

if (updated) {
      txn.commit();
      return true;
    }



  }
  catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
  }
  return false;
}











