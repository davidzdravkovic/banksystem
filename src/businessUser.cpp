#include "../include/businessUser.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/CheckingAccount.h"
#include "../include/Account.h"
#include <fstream>
#include <regex>
#include <iostream>


bool businessUser::createUser(pqxx::connection &conn,std::shared_ptr<User> user) 
{  
   auto bUser=std::dynamic_pointer_cast<businessUser>(user);
   if (!bUser) {
    std::cerr << "Error: User is not a BusinessUser!" << std::endl;
    return false;
}
   std::string fullName;
   long long personalID;
   std::string password;
   std::string address;
   std::string path;
   int contact;

  fullName=bUser->fullName;
while (true) {
   personalID=bUser->personalID;
   pqxx::work txn(conn);
   pqxx::result r=txn.exec("Select personal_id from business_users where personal_id=" +txn.quote(personalID) +";");
   
   if(!r.empty()) {
   
                return false;
  
}

else {
  break;
}
}
    try {
    pqxx::work txn(conn);
    pqxx::result r=txn.exec("INSERT into users (personal_id,user_type,full_name) VALUES ("+txn.quote(bUser->personalID)+","+txn.quote("Business_User")+","+txn.quote(fullName)+");");
    pqxx::result r1=txn.exec("INSERT into business_users (personal_id,full_name,user_type, password,business_contact,business_address) VALUES "
    "("+txn.quote(bUser->personalID)+","+txn.quote(fullName)+","+txn.quote("Business_User")+","+txn.quote(bUser->password)+","+txn.quote(bUser->businessContact)+","
    +txn.quote(bUser->businessAddress)+");");
    txn.commit();
    }
    catch (const pqxx::sql_error &e) {
      std::cerr << "SQL error: "<<e.what()<<std::endl;
      std::cerr << "Query error: "<<e.query()<<std::endl;
      return false;

    }
    catch (const std::exception &e) {
      std::cerr <<"Error: "<<e.what()<<std::endl;
      return false;
    }
    return true;

}
void businessUser::printUsers(pqxx::connection &conn) const {
  std::cout<<"PRINT PROFILE"<<std::endl;
  std::cout<<"PERSONAL ID: "<<this->getPersonalID()<<std::endl;
       try {
       pqxx::work txn(conn);
       pqxx::result r=txn.exec("SELECT full_name,password,personal_id,business_address,business_contact,register_number "
                               "FROM business_users WHERE personal_id="+ txn.quote(this->getPersonalID())+";");
          if(r.empty()) {
            std::cout<<"The table is empty!"<<std::endl;
            return;
          }
        for(int i=0; i<r.size(); i++) {
          std::cout<<"Full name: "<<r[i]["full_name"].c_str()<<std::endl;
          std::cout<<"Personal ID: "<<r[i]["personal_id"].as<long long>()<<std::endl;
          std::cout<<"Contact: "<<r[i]["business_contact"].as<long long>()<<std::endl;
          std::cout<<"Address: "<<r[i]["business_address"].c_str()<<std::endl; 
          std::cout<<std::endl;
                  std::cout<<"1.Create Account"<<std::endl;
                  std::cout<<"2.Search for account"<<"        ";
                  std::cout<<"3.Log Out"<<std::endl;
         }
         txn.commit();
       }
       catch(pqxx::sql_error &e){
        std::cerr<<"SQL error: "<<e.what()<<std::endl;
        std::cerr<<"Querie error: "<<e.query()<<std::endl;
        return;
       }
       catch(std::exception &e) {
        std::cerr<<"Error: "<<e.what()<<std::endl;
        return;
       }
       
    }
  void businessUser::printAccounts(pqxx::connection &conn) const {
    try{
      pqxx::work txn(conn);
      pqxx::result r=txn.exec("SELECT account_number,account_type FROM ONLY accounts WHERE personal_id=$1",this->getPersonalID());
      if(r.empty()) {
        std::cout<<"No accounts created!"<<std::endl;
        return;
      }
      for(int i=0; i<r.size(); i++) {
       int accountNumber=r[i]["account_number"].as<int>();
       std::string type=r[i]["account_type"].as<std::string>();
       std::cout<<i+1<<"."<<" Account type: "<<type<<"."<<"Account number: "<<accountNumber<<std::endl;
    }
    
  }
  catch(pqxx::sql_error &e) {
    std::cerr<<"SQL error: "<<e.what()<<std::endl;
    std::cerr<<"Query error: "<<e.query()<<std::endl; 
  }
  catch(std::exception &e) {
    std::cerr<<"Error: "<<e.what()<<std::endl;
    return;
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
    std::cout<<acc.getAccountTime()<<std::endl;
    std::cout<<acc.getBalance()<<std::endl;
   }
