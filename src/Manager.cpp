#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/Account.h"
#include "../include/personalUser.h"
#include "../include/studentUser.h"
#include "../include/businessUser.h"
#include "../include/functions.h"
#include <iostream>
#include <ctime>


Manager manager;
CheckingAccount cAccount;

 User* Manager::userCreate(int number)  {
     User* user = nullptr;
    std :: string uType;
    switch(number) {
        case 1:
            uType="Personal User";
            user = new personalUser();
            user->setUserType(uType);
            break;
        case 2:
            uType="Business User";
            user = new businessUser();
            user->setUserType(uType);
            break;
        case 3:
            uType="Student User";
            user = new studentUser();
            user->setUserType(uType);
            break;
        default:
            std::cout << "Invalid number!" << std::endl;
            throw std::runtime_error("Invalid user type");    }

    bool approved=false;
    approved=user->createUser(users);
    if(approved) {
    users.push_back(user);
    std::cout<<"User profile created successfully!"<<std::endl;
    return user;
    }
   
    return nullptr;
  
}



 Account* Manager::accountCreate(int number) {
    std :: string type;
    User* user=nullptr;
    bool exist=false;
for(int i=0; i<users.size(); i++) {
    if(users[i]->getPersonalID()==number) {
        user=users[i];
        exist=true;
     break;

    }
}


if(exist) { 
    typeAccounts();
    int option=digitVal("Choose account that you want to create: ");
  
    Account* acc=nullptr;
    switch (option) {
    
    case 1:
    type="Checking Account";
     acc=new CheckingAccount();
    acc->SetAccountType(type);
        
     
        break;
    
   case 2:
   type="Credit Account";
   acc=new CheckingAccount();
    acc->SetAccountType(type);
        break;
        
    case 3:
     type="Saving Account";
     acc=new CheckingAccount();
     acc->SetAccountType(type);

             
        break;

    default :
        break;
    }
    for(int i=0; i<users.size(); i++) {
        if(users[i]->getPersonalID()==number) {
            for(int j=0; j<users[i]->getAccounts().size(); j++) {
                if(users[i]->getAccounts()[j]->getAccountType()==type) {
                std::cout<<"You can only have one account per type!"<<std::endl;
                return nullptr;
            }
        }
    }
}
    bool approved=false;
    approved=acc->createAccount(users,number);
    if(approved) {
    user->getAccounts().push_back(acc);
    std :: cout<<"Account owner name: "<<acc->getOwnerName()<<std::endl;
    std::cout<<"Account created on: "<<getCurrentTime()<<std::endl;
    return acc;
    }
    else {
  return nullptr;
}
}
else {
    std::cout<<"User does not exist!"<<std::endl;
    return nullptr;
}



 
}
void Manager::listUser() {
    if(users.empty()) {
        std::cout<<"No user on the list!"<<std::endl;
        return;
    }
    for(int i = 0; i < users.size(); i++) {
        std::cout << "User type: " <<users[i]->getUserType() << std::endl;
        std::cout << "Full name: " << users[i]->getFullName() << std::endl;
        std::cout << "Personal ID: " << users[i]->getPersonalID() << std::endl;
        std::cout << "Contact: " << users[i]->getContact() << std::endl;
      
    }
}

void Manager::removeUser() {
    for(int i=0; i<users.size(); i++) {

    }

}
void Manager::printProfiles() {
  std :: cout<< "1.Personal user profile"<< std :: endl;
  std :: cout<< "2.Business user profile"<< std :: endl;
  std :: cout<< "3.Student user profile"<< std :: endl;
}
User* Manager::getTheLastUser() {
    if(!users.empty()) {
        return users.back();
    }
    return nullptr;
}
void Manager :: promt() {
  std :: cout<<"1. Loggin into existing account or sign up"<< std :: endl;
  std :: cout<<"2. See the list of users!"<< std :: endl;//Admin feauture
  std :: cout<<"3. Exit!"<<std :: endl;
}
void Manager :: typeAccounts() {
    std:: cout<<"1.Checking account"<< std :: endl;
    std:: cout<<"2.Credit account"<< std :: endl;
    std:: cout<<"3.Saving account"<< std :: endl;
}


User* Manager :: checkPass (std::string password, int personalID) {
  
    bool correctPass=false;
    for (int i=0; i<users.size();i++) {
    if(users[i]->getPersonalID()==personalID) {
        if(users[i]->getUsersPass()==password) {
           return users[i];
            
        }
    }
   

    }
    
     if(!correctPass) {
        std::cout<<"Incorrect ID or password! "<<std::endl;
        return nullptr;
    }
}
Account* Manager :: checkAccountNum(User *user, int accountNumber) {
    
    for(int i=0; i<user->getAccounts().size(); i++) {
        if(user->getAccounts()[i]->getAccountNumber()==accountNumber)
        {
            return user->getAccounts()[i];
        }
    }
  
    
  std::cout<<"Account with this number does not exist!"<<std::endl;
  return nullptr;
    

}
void Manager :: userPromt() {
    std::cout<<"Press 1 to log in on existing profile. " <<std::endl;
    std::cout<<"Press 2 to create a profile. " <<std::endl;
}
void Manager :: printTrans() {
    std::cout<<"1.Create transaction"<<std::endl;
    std::cout<<"2.View transactions"<<std::endl;

}
void Manager :: transOption() {
    std::cout<<"1.Inbox "<<std::endl;
    std::cout<<"2.sent "<<std::endl;
    

}
 void Manager :: transactionProfile( Account *acc) {
    int transNumber=digitVal("Enter transaction number: ");
    for(int i=0; i<acc->transInbox.size(); i++) {
        if(acc->transInbox[i]->transactionNumber==transNumber) {
         std :: cout<<"Sent request from user: "<< acc->transInbox[i]->sender<<"."<<std::endl;
         if (acc->transInbox[i]->transactionType==2) {
          std::cout<<"Asking for amount: "<<acc->transInbox[i]->amount<<std::endl;
        
          
            
         }
         if(acc->transInbox[i]->transactionType==1) {
               std::cout<<"sending a: "<<acc->transInbox[i]->amount<<std::endl;
              acc->transAmount=acc->transInbox[i]->amount;
          
         }
        }
    }
   
    

}