#include "../include/studentUser.h"
#include "../include/functions.h"
#include <iostream>


bool studentUser::createUser(std::vector<User*> &users)
{     
      fullName=inputVal("Enter your full name: ");
      int temp=digitVal("Enter your personalID: ");
      if(uniqueUser(users,temp)) {
      personalID=temp;
      password=digstrVal("Enter your password: ");
      age=digitVal("Enter your age: ");
      studentID=digitVal("Enter your student's ID " );
      typeEducation=inputVal("Enter your education: ");
      contact=digitVal("Enter your contact number: ");
      address=digstrVal("Enter your address: ");
      return true;
      }
      else {
        std::cout<<"No unique personalID!"<<std::endl;
        return false;
      }
}  
void studentUser::printUsers() const{
        std::cout << "Full name: " << fullName << "\n"
                  << "Student indentification: " <<studentID<< "\n"
                  << "Contact: " << getContact() << "\n"
                  << "Address: " << getAddress() << std::endl;
                  std::cout<<"1.Create Account"<<std::endl;
                  std::cout<<"2.Search for account"<<"        ";
                  std::cout<<"3.Log Out"<<std::endl;
    }

   void studentUser :: printAccounts(User *user) const {
    for(int i=0; i<user->getAccounts().size(); i++) {
      std::cout<<user->getAccounts()[i]->getAccountNumber()<<std::endl;
    }
  }   

