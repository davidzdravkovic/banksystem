#include "../include/menu.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/businessUser.h"
#include "../include/personalUser.h"
#include "../include/CheckingAccount.h"
#include "../include/Transactions.h"
#include <iostream>



 void mainMenu() {
  
  personalUser pUser;
  businessUser bUser;
  Transactions trans;
  Transactions *transact=nullptr;
  Manager manager;
  User *userRef=nullptr;
  Account*account=nullptr;
  int option;
  bool temp=false;
  bool matea=false;

  while(true) {
  manager.promt();
  option=digitVal("Enter your choice: ");

  switch (option) {
  
  case 1: {

  int choice;
  manager.userPromt();
  int entry1=digitVal("Enter your option: ");
  ////USER LOG IN////
  if(entry1==1) {
   int personalID=digitVal("Enter your personal ID: ");
   std :: string password=digstrVal("Enter your password: ");
   User* userLog=manager.checkPass(password,personalID);
   userRef=userLog;
   if(userRef==nullptr) 
   continue;
   
   
  }
/////USER CREATE//////
else if(entry1==2) {
  manager.printProfiles();
  choice=digitVal("Enter your choice for user creation: ");
  User* userCreat = manager.userCreate(choice);
  userRef=userCreat;
  if(userRef==nullptr) {
    continue;
  }
 }
 while(true) {
  /////PRINT USER//////
  userRef->printUsers();
  int option1=digitVal("Enter your option: ");
 /////ACCOUNT CREATE//////
  if(option1==1) {
   
   account= manager.accountCreate(userRef->getPersonalID());
   if(account==nullptr){
    continue;
   }
   matea=true;
  }
  /////ACCOUNT SEARCH//////
  else if(option1==2) {
   userRef->printAccounts(userRef);
   std::cout<<"Enter 0 to exit "<<std :: endl;
   std::cout<<"Enter 1 to view account profile"<<std :: endl;
   int number=digitVal("Enter your option: ");
 if(number==0) {
    continue;
   }
   else if(number==1) {
   int accNum=digitVal("Enter account number: ");
   account=manager.checkAccountNum(userRef,accNum);
   if(account==nullptr) {
    continue;
   }
   else {
    temp=true;
   }
  }
}
else if(option1==3) {
  break;
}
/////ACCOUNT INTERFACE//////
  if(temp||matea) {
   while(true) {
  
   account->printAccount(userRef,account->getAccountNumber());
    int choose=digitVal("Enter your chooice: ");
   
    if(choose==1) { 
      double deposit=digitVal("Enter your depoist sum: ");
  
      account->deposit(userRef,account->getAccountNumber(),deposit);
    }
    else if(choose==2) {


      double withdraw=digitVal("Enter your withdraw sum: ");
      account->withdraw(userRef,account->getAccountNumber(),withdraw);
    }
      if(choose==3) {
      manager.printTrans();
      int choose1=digitVal("Enter your option: ");
     if(choose1==1) {
     
       transact=trans.createTrans(manager,account,userRef);
      }
      else if(choose1==2) {
         manager.transOption();
         int num=digitVal("Enter option: ");
         if(num==1) {
          trans.printInbox(account);
          manager.transactionProfile(account); 
          int numb=digitVal("If you want to proceed press 1: ");
          if(numb==1) {
           trans.decision(manager,account,transact);
           std::cout<<"New balance: "<<account->getBalance()<<std::endl;
          }
          
         }
         if(num==2) {
         trans.printSent(account);
         }
      }
    }
    else if(choose==4) {

      break;
    }
    
  }

}
 }
 break;
}
   
  case 2: {
  manager.listUser();
  break;
  }
  
  case 3: {
  return;
  }
  default: {
    break;
  }
}
 }
  }
