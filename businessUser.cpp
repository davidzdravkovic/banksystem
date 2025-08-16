#include "../include/businessUser.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/Account.h"
#include <fstream>
#include <regex>
#include <iostream>


void businessUser::createUser() 
{      std :: string path;
      fullName=inputVal("Enter your full name: ");
      personalID=digitVal("Enter your personal ID: " );
      businessContact=digitVal("Enter company contact: ");
      businessAddress=digstrVal("Enter company address: ");
      path=digstrVal("Enter your file path for register number: ");
      importLicenceFromFile(path);

    }
void businessUser::print() const {
        std::cout << "Full name: " << fullName << "  "
                  << "Personal ID: " << personalID << "  "
                  << "Contact: " << businessAddress << "  "
                  << "Address: " << businessContact << std::endl; 
                  std::cout<<std::endl;
                  std::cout<<"Create Account"<<std::endl;
                  std::cout<<"Search for account"<<"        ";
                  std::cout<<"Log Out"<<std::endl;
            
               
    }
  void businessUser::listAccounts(std::vector<User*> &users,int personalID) {
    bool found=false;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getPersonalID()== personalID) {  
        found=true;
        auto& acc=users[i]->getAccounts();
           for(int j=0; j<acc.size(); j++) {
             std::cout<< j+1 <<"."<<acc[j]->getAccountNumber();
           } 
           break;
            } 
        }
          if(!found) {
            std::cout << "User not found!" << std::endl;
          }
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
    std::cout<<acc.accountTime<<std::endl;
    std::cout<<acc.getBalance()<<std::endl;
   }
