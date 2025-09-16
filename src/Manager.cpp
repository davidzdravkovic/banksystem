#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/CreditAccount.h"
#include "../include/SavingAccount.h"
#include "../include/Account.h"
#include "../include/personalUser.h"
#include "../include/studentUser.h"
#include "../include/businessUser.h"
#include "../include/functions.h"
#include "../include/Transactions.h"
#include <iostream>
#include <ctime>





Manager manager;
CheckingAccount cAccount;




void Manager::removeUser() {
    for(int i=0; i<users.size(); i++) {

    }

}
void Manager::printProfiles() {
  std :: cout<< "1.Personal user profile."<< std :: endl;
  std :: cout<< "2.Business user profile."<< std :: endl;
  std :: cout<< "3.Student user profile."<< std :: endl;
  std :: cout<<"                         4.Exit."<<std::endl;
}
User* Manager::getTheLastUser() {
    if(!users.empty()) {
        return users.back();
    }
    return nullptr;
}
void Manager :: promt() {
  std :: cout<<"1.Loggin as User "<< std :: endl;
  std :: cout<<"2.Loggin as Admin"<<std :: endl;
  std :: cout<<"3.Exit"<<std::endl;
}
void Manager :: typeAccounts() {
    
    std:: cout<<"1.Checking account."<< std :: endl;
    std:: cout<<"2.Credit account."<< std :: endl;
    std:: cout<<"3.Saving account."<< std :: endl;
    std:: cout<<"4.Exit."<<std :: endl;
}


User* Manager :: checkPass (pqxx::connection &conn,const int personalID,const std::string password,int userOption) {
    User * user=nullptr;
    std::string userType;
    std::string tableName;
    if(userOption==1) {
        userType="Personal_User";
        tableName="personal_users";
        user=new personalUser();
    }  
    else if(userOption==2) {
        userType="Business_User";
        user=new businessUser();
         tableName="business_users";
    }
    else if(userOption==3) {
        userType="Student_User";
        user=new studentUser();
         tableName="student_users";
    }
    else if (userOption==4) {
       delete user;    
       return nullptr;
    }
    else {
        std::cout<<"Invalid type!"<<std::endl;
        delete user;
        return nullptr;
    }
 try{
    pqxx::work txn(conn);
    pqxx::result r=txn.exec("SELECT personal_id,password,full_name " 
                            "FROM  "+tableName+
                             " WHERE personal_id="+txn.quote(personalID)+
                             " AND password = " +txn.quote(password)+";");
   
   std:: string userName=r[0]["full_name"].as<std::string>();    
   if(r.empty()) {
            std::cout << "ID or password incorrect!" << std::endl;
            delete user;  // free memory to avoid leak
            return nullptr;
        }
    user->setUserType(userType);
    user->setPersonalID(personalID);
    user->setFullName(userName);

 }
 catch(pqxx::sql_error &e) {
    std::cerr <<"SQL error: "<<e.what()<<std::endl;
    std::cerr <<"QUERIE error: "<<e.query()<<std::endl;
    delete user;
    return nullptr;
 }
 catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what()<<std::endl;
    delete user;
    return nullptr;
 }
 return user;
}
 std::vector<std::shared_ptr<Account>> Manager :: checkAccountNum(pqxx::connection &conn,int personalID) {
    Account *acc=nullptr;
      std::vector<std::shared_ptr<Account>> accounts;
   try{
      pqxx::work txn(conn);
      pqxx::result r=txn.exec_params("SELECT account_number,account_type,balance FROM ONLY accounts WHERE personal_id=$1",personalID);
      if(r.empty()) {
    return accounts;
      }
   
      for(int i=0; i<r.size(); i++) {
       int accNumber=r[i]["account_number"].as<int>();
       std::string type=r[i]["account_type"].as<std::string>();
       double balance=r[i]["balance"].as<double>();


            if(type=="checking_accounts") {
        auto cacc=std::make_shared<CheckingAccount>();
         cacc->setAccountNumber(accNumber);
         cacc->SetAccountType(type);
         cacc->setBalance(balance);
         accounts.push_back(cacc);
       }
        if(type=="credit_accounts") {
        auto creditAcc=std::make_shared<CreditAccount>();
         creditAcc->setAccountNumber(accNumber);
         creditAcc->SetAccountType(type);
         creditAcc->setBalance(balance);
         accounts.push_back(creditAcc);
       }
       if(type=="saving_accounts") {
        auto savingAcc=std::make_shared<SavingAccount>();
         savingAcc->setAccountNumber(accNumber);
         savingAcc->SetAccountType(type);
         savingAcc->setBalance(balance);
         accounts.push_back(savingAcc);
       }
      }
    if(!acc) {
      return accounts;
    }
    
  }
  catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what()<<std::endl;
    std::cerr<<"Query error: "<<e.query()<<std::endl; 
 
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what()<<std::endl;
    
  }
    return accounts;

}
void Manager :: userPromt() {
    std::cout<<"Press 1 to log in on existing profile. " <<std::endl;
    std::cout<<"Press 2 to create a profile. " <<std::endl;
    std::cout<<"                                3.Exit."<<std::endl;
}
void Manager :: printTrans() {
    std::cout<<"1.Create transaction."<<std::endl;
    std::cout<<"2.View transactions."<<std::endl;
    std::cout<<"3.Exit."<<std::endl;

}
void Manager :: transOption() {
    std::cout<<"1.Inbox. "<<std::endl;
    std::cout<<"2.Sent. "<<std::endl;
    std::cout<<"3.Exit."<<std::endl;
    

}
 int Manager :: transactionProfile( Account *acc,pqxx::connection &conn,bool listInbox,bool listSent) {
    int transNumber=digitVal("Enter transaction number or 0 to exit: ");
    if(transNumber==0) {
        return 0;
    }
    try{
        pqxx::work txn(conn);
        pqxx::result r=txn.exec_params("SELECT amount,transaction_type,from_account FROM transactions WHERE to_account=$1 AND active=true "
             "AND transaction_id=$2",acc->getAccountNumber(),transNumber);

       
        if(listInbox){
      if(r.empty()) {
        std::cout<<"Wrong transaction number!"<<std::endl;
        return 0;
      }
    }
      pqxx::result r1=txn.exec_params("SELECT amount,transaction_type,to_account FROM transactions WHERE from_account=$1 AND active=true "
             "AND transaction_id=$2",acc->getAccountNumber(),transNumber);
     if(listSent) {
       if(r1.empty()) {
        std::cout<<"Wrong transaction number!"<<std::endl;
        return 0;
      }

    }
      
    if(listInbox) {
         int transType=r[0]["transaction_type"].as<int>();
     double amount=r[0]["amount"].as<double>();
     int senderAccNumber=r[0]["from_account"].as<int>();
     if(transType==1) {
        std::cout<<"Account number: "<<senderAccNumber<<".Is sending amount: "<<amount<<std::endl;
        return transNumber;
     }
  if(transType==2) {
        std::cout<<"Account number: "<<senderAccNumber<<".Is asking for amount: "<<amount<<std::endl;
        return transNumber;
     }
    }
        
    if(listSent) {
     int transType=r1[0]["transaction_type"].as<int>();
     double amount=r1[0]["amount"].as<double>();
     int receiverAccount=r1[0]["to_account"].as<int>();
     if(transType==1) {
     std::cout<<"You are sendign money to: "<<receiverAccount<<" amount: "<<amount<<std::endl;
        return transNumber;
     }
  if(transType==2) {
       std::cout<<"You are asking money from: "<<receiverAccount<<" amount: "<<amount<<std::endl;
        return transNumber;
     }
    }
    }
    catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return 0 ;
  }
  return 0;
   
    

}
void Manager :: decisionPrint(bool listInbox,bool listSent) {
    if(listInbox) {
    std::cout<<"Press 1 to accept."<<std::endl;
    std::cout<<"Press 2 to decline."<<std::endl;
    std::cout<<"Press 3 to exit."<<std::endl;
    }
    else if(listSent) {

    std::cout<<"Press 1 to decline."<<std::endl;
    std::cout<<"Press 2 to exit."<<std::endl;

    }

}


bool Manager ::transValidation(pqxx::connection &conn,const int senderNumber,int receiverNumber, int transactionType,double amount) {
  try {  std::cout<<"TRANS validation"<<std::endl;
    pqxx::work txn(conn);
    pqxx::result r=txn.exec("SELECT  account_number FROM ONLY accounts WHERE account_number=$1",receiverNumber);
    pqxx::result r1=txn.exec("SELECT balance FROM ONLY accounts WHERE account_number=$1",senderNumber);
   if(r.empty()) {
    std::cout<<"Wrong account number!"<<std::endl;
    return false;
   } 
   double balance=r1[0]["balance"].as<double>();
   std::cout<<"Balance: "<<balance<<std::endl;
    if((transactionType==1 && balance>=amount) ||transactionType==2) {

        return true;
    }
  }
  catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return false;
  }
  return false;
} 
std::shared_ptr<Account> Manager :: getAccount (pqxx::connection &conn,int accountNumber) {
  std::shared_ptr<Account> account=nullptr;
  try {
    pqxx::work txn(conn);
    pqxx::result r=txn.exec_params("SELECT account_type FROM accounts WHERE account_number=$1",accountNumber);
     if(r.empty()) {
      return nullptr;
    }
    std::string typeAccount=r[0]["account_type"].as<std::string>();
   
    if(typeAccount=="checking_accounts") {
      account=std::make_shared<CheckingAccount>();
      return account;
    }
     if(typeAccount=="credit_accounts") {
      account=std::make_shared<CreditAccount>();
      return account;
    }
     if(typeAccount=="saving_accounts") {
      account=std::make_shared<SavingAccount>();
      return account;
    }
    
    
  }
  catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what();
    std::cerr<<"Query error: "<<e.query();
   return nullptr;
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what();
    return nullptr;
  }
  
}
