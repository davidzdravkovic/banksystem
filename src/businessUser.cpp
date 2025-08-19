#include "../include/businessUser.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/Account.h"
#include <fstream>
#include <regex>
#include <iostream>


bool businessUser::createUser(std::vector<User*> &users) 
{     std :: string path;
      int temp;
      bool unique=false;
      fullName=inputVal("Enter your full name: ");
      while (true) {
      temp=digitVal("Enter your personalID: ");
      unique=uniqueUser(users,temp);
    
      if (!unique) {
        std::cout<<"Not unique personalID!"<<std::endl;
        int option=digitVal("Enter 0 to exit 1 to retry: ");
        if(option==0) {
          std::cout<<"User not created!"<<std::endl;
          return false;
        }
        else if(option==1) {
          continue;
        }
      }
     if(unique) {
        break;
      }
      
    }
  
  
      
      personalID=temp;
      password=digstrVal("Enter your password: ");
      businessContact=digitVal("Enter company contact: ");
      businessAddress=digstrVal("Enter company address: ");
      path=digstrVal("Enter your file path for register number: ");
      importLicenceFromFile(path);
      return true;
      
  }
        //std::cout<<"Not unique personalID!"<<std::endl;
       // return false;

  

void businessUser::printUsers() const {
        std::cout << "Full name: " << fullName << "  "
                  << "Personal ID: " << personalID << "  "
                  << "Contact: " << businessAddress << "  "
                  << "Address: " << businessContact << std::endl; 
                  std::cout<<std::endl;
                  std::cout<<"1.Create Account"<<std::endl;
                  std::cout<<"2.Search for account"<<"        ";
                  std::cout<<"3.Log Out"<<std::endl;
            
               
    }
  void businessUser::printAccounts(User *user) const {
    for(int i=0; i<user->getAccounts().size();i++)
    std::cout<<user->getAccounts()[i]->getAccountNumber()<<std::endl;
  }


    
void businessUser::importLicenceFromFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    std::string line;
    std::regex businessLicense("[A-Z]{2}-[0-9]+"); // e.g., MK-123456
    std::smatch match;

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, businessLicense)) {
            registrationNumber = match.str(); // store in member variable
            std::cout << "License number imported: " << registrationNumber << "\n";
            return; // stop after first match
        }
    }

    std::cout << "No license number found in the file.\n";
}
   void businessUser :: printAccount(Account& acc) {
    std::cout<<acc.getAccountNumber()<<std::endl;
    std::cout<<acc.getOwnerName()<<std::endl;
    std::cout<<acc.getAccountTime()<<std::endl;
    std::cout<<acc.getBalance()<<std::endl;
   }
