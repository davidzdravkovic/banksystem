#include "../include/CheckingAccount.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include <iostream> 
#include <vector>

  class User;
   void CheckingAccount::deposit(User *user,int accountNumber,double amount) {
    if (amount >= 0) {
      for(int i=0; i<user->getAccounts().size(); i++) {
         if(user->getAccounts()[i]->getAccountNumber()==accountNumber) {
        user->getAccounts()[i]->setBalanceDepo(amount);
          
         } 
      }
   
}
   }
 void CheckingAccount ::withdraw(User *user,int accountNumber,double amount) {
    if (amount > 0 && amount <= balance)
    for(int i=0; i<user->getAccounts().size(); i++) {
         if(user->getAccounts()[i]->getAccountNumber()==accountNumber) {
        user->getAccounts()[i]->setBalanceWith(amount);
          
         } 
      }
 }
  bool CheckingAccount :: createAccount (std::vector<User*>&users, int personalID) {
     bool make=false;
     int temp = digitVal("Enter your account number: ");
     make=uniqueAccount(users,personalID,temp);
     if(make) {
     accountNumber=temp;
     for(int i=0; i<users.size(); i++ ) {
       if(users[i]->getPersonalID()==personalID) {
         owner=users[i]->getFullName();
       }
     }
    
    while(true) {
    std :: string approval=inputVal("If you want to deploy balance input Y if not input N:");
    if(approval=="Y" || approval=="y") {
      balance=digitVal("Enter your balance: ");
      break;
    }
    else if(approval=="N" || approval == "n") {
      balance=0;
      break;
    }
    else{
      std::cout<<"Wrong input try again!"<<std::endl;
      continue;
    }
   }
    std::string accTime=getCurrentTime();
     setAccountTime(accTime);
     return true;
     }
     else{
        std::cout<<"Account number not unique!"<<std::endl;
        return false;
     }

   


 }
 void CheckingAccount :: printAccount(User *user, int accountNumber)  {
     for(int i=0; i<user->getAccounts().size(); i++) {
      if(user->getAccounts()[i]->getAccountNumber()==accountNumber) {
            std::cout<<"Account type: "<<user->getAccounts()[i]->getAccountType()<<"       "<<"1.Deposit"<<std::endl;
            std::cout<<"Owner name: "<<user->getAccounts()[i]->getOwnerName()<<"                    "<<"2.Withdraw"<<std::endl;
            std::cout<<std::endl;                                
            std::cout<<"Balance: "<<user->getAccounts()[i]->getBalance()<<"   "<<"3.Transactions"<<std::endl;
            std::cout<<"Date of creation:"<<user->getAccounts()[i]->getAccountTime()<<"   "<<"4.Exit"<<std::endl;
     }
     else {
      //std :: cout<<"Wrong account number!"<<std :: endl;
     }
 }
}


