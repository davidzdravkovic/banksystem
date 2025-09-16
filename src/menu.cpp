#include "../include/menu.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/businessUser.h"
#include "../include/personalUser.h"
#include "../include/CheckingAccount.h"
#include "../include/Transactions.h"
#include "../include/AdminUser.h"
#include <pqxx/pqxx>
#include <iostream>




 void mainMenu() {
  AdminUser aUser;
  personalUser pUser;
  businessUser bUser;
  Transactions trans;
  Transactions *transact=nullptr;
  Manager manager;
  User *userRef=nullptr;
  Account*account=nullptr;
  int option;
  bool bylog=false;
  bool bycreate=false;
  bool listSent=false;
  bool listInbox=false;
   
   std::cout << "Program started\n";    
  pqxx::connection conn("dbname=postgres user=postgres password=new_password host=localhost");
    
  while(true) {
  
 

  manager.promt();
  option=digitVal("Enter your choice: ");

  switch (option) {
  
  case 1: {
while (true) {
  int choice;
  manager.userPromt();
  int entry1=digitVal("Enter your option: ");
  ////USER LOG IN////
  if(entry1==1) {
 
   manager.printProfiles();
   int userOption=digitVal("Choose profile type: ");
   int personalID=digitVal("Enter your personal ID: ");
   std :: string password=digstrVal("Enter your password: ");
   User* userLog=manager.checkPass(conn,personalID,password,userOption);
   userRef=userLog;
   if(userRef==nullptr) 
   continue;
   
   
  }
  
/////USER CREATE//////
//  else if(entry1==2) {
//   manager.printProfiles();
//   choice=digitVal("Enter your choice for user creation: ");
//   if(choice==4) {
//     break;
//   }
//   //User* userCreat = manager.userCreate(choice,conn);
//   userRef=userCreat;
//  if(userRef==nullptr) {
//   continue;
//  }
//  }
  if(entry1==3) {
  break;
 }
 while(true) {
  /////PRINT USER//////
  userRef->printUsers(conn);
  int option1=digitVal("Enter your option: ");
 /////ACCOUNT CREATE//////
  if(option1==1) {
   
  //  account= manager.accountCreate(conn,userRef->getPersonalID());
   if(account==nullptr){
    continue;
   }
     bycreate=true;
  }
  /////ACCOUNT SEARCH//////
  else if(option1==2) {
   userRef->printAccounts(conn);
   std::cout<<"Enter 0 to exit "<<std :: endl;
   std::cout<<"Enter 1 to view account profile"<<std :: endl;
   int number=digitVal("Enter your option: ");
   
 if(number==0) {
    continue;
   }
   else if(number==1) {
   int accNum=digitVal("Enter account number: ");
  //  account=manager.checkAccountNum(conn,accNum,userRef->getPersonalID());
   if(account==nullptr) {
    continue;
   }
   else {
    bylog=true;
   }
  }
  else {
    std::cout<<"Wrong input!"<<std::endl;
    continue;
  }
}
else if(option1==3) {
  break;
}
else {
  std::cout<<"Invalid input!"<<std::endl;
  continue;
}
/////ACCOUNT INTERFACE//////
  if(bylog||bycreate) {
   while(true) {
  
  //  account->printAccount(conn);
    int choose=digitVal("Enter your chooice: ");
   
    if(choose==1) { 
      double deposit=digitVal("Enter your depoist sum: ");
  
      // account->deposit(conn,deposit);
    }
    else if(choose==2) {


      double withdraw=digitVal("Enter your withdraw sum: ");
      // account->withdraw(conn,withdraw);
    }
      if(choose==3) {
      manager.printTrans();
      int choose1=digitVal("Enter your option: ");
     if(choose1==1) {
     
      //  trans.createTrans(conn,account->getAccountNumber());
      }
      else if(choose1==2) {
         manager.transOption();
         int num=digitVal("Enter option: ");
         if(num==1) {
        //  listInbox=trans.printInbox(account,conn);
        if(listInbox==false) {
          continue;
        }
      }
        else if(num==2) {
        //  listSent=trans.printSent(account,conn);
        
        if(listSent==false) {
          continue;
        }
      }
       else if(num==3) {
          continue;
         }
       int transNumber= manager.transactionProfile(account,conn,listInbox,listSent); 
       if(transNumber==0) {
        continue;
       }
          manager.decisionPrint(listInbox,listSent);
          int numb=digitVal("Enter your option: ");
          if(listSent) {
            if(numb==1){
              numb=2;
            }
           else if(numb==2) {
              numb=3;
            }
            else {
              std::cout<<"Invalid input"<<std::endl;
              continue;
            }
          }
          if(numb==1&&listInbox) {
          //  trans.acceptence(conn,account,transNumber);
           std::cout<<"New balance: "<<account->getBalance()<<std::endl;
          }
         else if(numb==2) {
          //  trans.decline(conn,transNumber);
          }
         else if(numb==3) {
            continue;
          }
          else {
            std::cout<<"Invalid input!"<<std::endl;
            continue;
          }
        }
      
     else if(choose1==3) {
        continue;
      }
      else {
        std::cout<<"Invalid input!"<<std::endl;
        continue;
      }
      }
    else if(choose==4) {
    // trans.printHistory(conn,account,listInbox,listSent);
    }
    else if(choose==5) {

      break;
    }
    else {
      continue;
    }
    
  }

}
 }
  
 break;
}

  }
  break;
  case 2: {
    
      
      int chooice;
      std::string name=inputVal("Enter admin's name: ");
      std::string password=inputVal("Enter admin's password: ");
      if(password==aUser.getAdminPass()&&name==aUser.getAdminName()) {
        while(true) {
     aUser.adminProfile();
        
      chooice=digitVal("Enter your option: ");
     if(chooice==1) {
      aUser.listUser(manager);
     }
     else if(chooice==2) {
     aUser.viewAccounts(manager);
     }
     else if(chooice==3) {
     break;
     }
     else {
      std::cout<<"Invalid input!"<<std::endl;
      continue;
     }
    }
    }
    }

  
  
break;
  
  case 3: {
  return;
  }
  default: {
    std::cout<<"Invalid input!"<<std::endl;
    break;
  }

 }
  }

 
 }