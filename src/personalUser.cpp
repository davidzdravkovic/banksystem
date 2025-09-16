#include "../include/personalUser.h"
#include "../include/functions.h"
#include <iostream>



bool personalUser::createUser(pqxx::connection &conn,std::shared_ptr<User> user) {  
   auto pUser=std::dynamic_pointer_cast<personalUser>(user);
   if (!pUser) {
    std::cerr << "Error: User is not a BusinessUser!" << std::endl;
    return false;
}
while (true) {
   pqxx::work txn(conn);
   pqxx::result r=txn.exec("Select personal_id from personal_users where personal_id=" +txn.quote(pUser->getPersonalID()) +";");
   
   if(!r.empty()) {
   
                return false;
}

else {
  break;
}
}
    try {
    pqxx::work txn(conn);
    pqxx::result r=txn.exec("INSERT into users (personal_id,user_type,full_name) VALUES ("+txn.quote(pUser->getPersonalID())+","+txn.quote("Personal_User")+","+txn.quote(pUser->getFullName())+");");
    pqxx::result r1=txn.exec("INSERT into personal_users (personal_id,full_name,user_type, password) VALUES "
    "("+txn.quote(pUser->getPersonalID())+","+txn.quote(pUser->getFullName())+","+txn.quote("Personal_User")+","+txn.quote(pUser->getUsersPass())+");");
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
void personalUser::printUsers(pqxx::connection &conn) const{
        std::cout << "Full name: " << getFullName() << "\n"
                  << "Personal ID: " << getPersonalID() << "\n"
                  << "Contact: " << getContact() << "\n"
                  << "Address: " << getAddress() << std::endl;
                  std::cout<<std::endl;
                  std::cout<<"1.Create Account"<<std::endl;
                  std::cout<<"2.Search for account"<<"        ";
                  std::cout<<"3.Log Out"<<std::endl;
    }
  void personalUser :: printAccounts(pqxx::connection &conn) const {
  try{
      pqxx::work txn(conn);
      pqxx::result r=txn.exec("SELECT  account_number,account_type FROM ONLY accounts WHERE personal_id=$1",this->getPersonalID());
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
