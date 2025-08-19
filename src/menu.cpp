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
  Manager manager;
  Transactions trans;
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
  if(entry1==1) {
   int personalID=digitVal("Enter your personal ID: ");
   std :: string password=digstrVal("Enter your password: ");
   User* userLog=manager.checkPass(password,personalID);
   userRef=userLog;
   if(userRef==nullptr) 
   continue;
   
   
  }

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
  userRef->printUsers();
  int option1=digitVal("Enter your option: ");
 
  if(option1==1) {
   
   account= manager.accountCreate(userRef->getPersonalID());
   if(account==nullptr){
    continue;
   }
   matea=true;
  }
  
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
   temp=manager.checkAccountNum(userRef,accNum);
  
  }

}
else if(option1==3) {
  break;
}

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
    else if(choose==3) {
      manager.printTrans();
      int digit=digitVal("Enter your option:");
      if(digit==1) {
        int personalID=digitVal("Enter user's personal ID: ");
        int accountNumber=digitVal("Enter user's account number: ");
        int sum=digitVal("Enter your sum: ");
        trans.creatTrans(userRef,personalID,accountNumber,sum,manager);
      }
      else if(digit==2) {
       trans.history(userRef);
       std::cout<<"Do you want to accept enter 1 to decline 0! "<<std::endl;
       int opt=digitVal("Enter your option: ");
       if(opt==0) {
        break;
       }
       if(opt==1) {
        trans.decide(userRef);
       }
      }
    }
    else if(choose==4) {
      break;
     }
    }
  }
}
  }
    break;
   
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
