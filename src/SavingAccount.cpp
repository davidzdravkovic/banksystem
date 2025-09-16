#include "../include/User.h"
#include "../include/Account.h"   // full definition now available
#include "../include/Manager.h"
#include "../include/functions.h"
#include "../include/SavingAccount.h"
#include <iostream>


  class User;
   double SavingAccount::deposit(pqxx::connection &conn,double amount,int accountNumber) {
    if(amount<0) {
      return -1;
    }
    try{
      pqxx::work txn(conn);
      pqxx::result r = txn.exec_params(
            "SELECT balance, total_deposit FROM saving_accounts WHERE account_number = $1",
           accountNumber
        );
      double receivedB=r[0]["balance"].as<double>();
      double depositSUm=r[0]["total_deposit"].as<double>();
      double newBalance=receivedB+amount;
      double newDepositSum=depositSUm+1;
      txn.exec_params(
            "UPDATE saving_accounts "
            "SET balance = $1, total_deposit = $2 "
            "WHERE account_number = $3",
            newBalance, newDepositSum, accountNumber
        );
       txn.exec_params("UPDATE accounts SET balance = $1 WHERE account_number=$2",newBalance,accountNumber); 
      txn.commit();
        return newBalance;

    }
    catch(pqxx::sql_error &e) {
      std::cerr<<"SQL error: "<<e.what()<<std::endl;
      std::cerr<<"Query error: "<<e.query()<<std::endl;
   return -1;
    }
    catch(std::exception &e) {

      std::cerr<<"Error: "<<e.what()<<std::endl;
      return -1;
    }
return -1;
  }
   
double SavingAccount :: withdraw(pqxx::connection &conn,double amount,int accountNumber) {
  
   if(amount<0) {
      std::cout<<"Withdraw must be positive amount!"<<std::endl;
      return -1;
    }
    try{

         pqxx::work txn(conn);
         pqxx::result r1 = txn.exec_params(
            "SELECT  balance,total_withdraw FROM saving_accounts WHERE account_number = $1",
            accountNumber
        );
      double receivedB=r1[0]["balance"].as<double>();
      int withdrawSUm=r1[0]["total_withdraw"].as<double>();
      if(receivedB>=amount) {
      double newBalance=receivedB-amount;
      int newWithdrawSum=withdrawSUm+1;
      txn.exec_params(
            "UPDATE saving_accounts "
            "SET balance = $1, total_withdraw = $2 "
            "WHERE account_number = $3",
            newBalance, newWithdrawSum, accountNumber
        );
        txn.exec_params("UPDATE accounts SET balance = $1 WHERE account_number=$2",newBalance,accountNumber); 
        txn.commit();
        return newBalance;
      }
      else {
        std::cout<<"Not enough money!"<<std::endl;
        return -1;
      }
      
      
    }
    catch(pqxx::sql_error &e) {
      std::cerr<<"SQL error: "<<e.what()<<std::endl;
      std::cerr<<"Query error: "<<e.query()<<std::endl;
 
    }
    catch(std::exception &e) {
      std::cerr<<"Error: "<<e.what()<<std::endl;
    }
return -1;
  }
 
   std::shared_ptr<Account> SavingAccount :: createAccount (pqxx::connection &conn,std::shared_ptr<Account> account,int number) {
   auto cAccount=std::dynamic_pointer_cast<SavingAccount>(account);
   if(!cAccount) {
    std::cout<<"Account not exist!"<<std::endl;
    return nullptr;
   }
  
      
try {
  pqxx::work txn(conn);
       pqxx::result r=txn.exec("SELECT account_type FROM ONLY accounts WHERE personal_id=$1",number);
      pqxx::result r1=txn.exec("SELECT  account_number FROM ONLY accounts "
                             "WHERE account_number=$1",cAccount->getAccountNumber());
bool hasThisType = false;
for (int i=0; i<r.size(); i++) {
    if (!r[i]["account_type"].is_null()) {
        std::string existingType = r[i]["account_type"].as<std::string>();
        if (existingType == cAccount->getAccountType()) {
            hasThisType = true;
            break;
        }
    }
}

if (hasThisType) {
  std::cout<<"I AM HERE123"<<std::endl;
    return nullptr;
}
       if(!r1.empty()) {
          std::cout<<"I AM HERE12333"<<std::endl;
          return nullptr;
      }
    


 std::string query = "INSERT INTO accounts (personal_id,account_number,account_type,full_name) VALUES "
    "($1,$2,$3,$4)";
  txn.exec_params(query,number,cAccount->getAccountNumber(),cAccount->getAccountType(),cAccount->getOwnerName());
   std::string query1 = "INSERT INTO saving_accounts (personal_id,account_number,account_type,full_name) VALUES "
    "($1,$2,$3,$4)";
     txn.exec_params(query1,number,cAccount->getAccountNumber(),cAccount->getAccountType(),cAccount->getOwnerName());
     pqxx::result r2=txn.exec_params("Select * FROM ONLY saving_accounts WHERE account_number=$1",cAccount->getAccountNumber());
     txn.commit();

     if (!r2.empty()) {
    pqxx::row row = r2[0];
   int accNumber = row["account_number"].as<int>();
   std::string accType = row["account_type"].as<std::string>();
   double balance = row["balance"].as<double>();
   int personalID = row["personal_id"].as<int>();
   double totalDeposit = row["total_deposit"].as<double>();
   double totalWithdraw = row["total_withdraw"].as<double>();
   int transactionMade = row["transaction_made"].as<int>();
cAccount->setAccountNumber(accNumber);
cAccount->SetAccountType(accType);
cAccount->setBalance(balance);
cAccount->setTotalDeposite(totalDeposit);
cAccount->setTotalWithdraw(totalWithdraw);
cAccount->setTransactionsMade(transactionMade);
return cAccount;
}
     
}
catch(pqxx::sql_error &e) {
 std::cerr<<"SQL error: "<<e.what()<<std::endl;
 std::cerr<<"Querie error: "<<e.query()<<std::endl;
 std::cout<<"HERE 1"<<std::endl;
 return nullptr;
}
catch(std::exception &e) {
  std::cerr<<"Error: "<<e.what()<<std::endl;
  std::cout<<"HEREEEE"<<std::endl;
  return nullptr;
}
  std::cout<<"AM i HERE yes"<<std::endl;
return nullptr;

 }
 