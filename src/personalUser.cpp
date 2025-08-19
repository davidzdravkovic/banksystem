#include "../include/personalUser.h"
#include "../include/functions.h"
#include <iostream>


bool personalUser::createUser(std::vector<User*> &users)
{
     
      fullName=inputVal("Enter your full name: ");
      int temp=digitVal("Enter your personal user's personalID: ");
      if(uniqueUser(users,temp)) {
      personalID=temp;
      password=digstrVal("Enter your password: ");
      contact=digitVal("Enter your contact number: ");
      address=digstrVal("Enter your address: ");
      return true;
      }
      else {
        std::cout<<"Not unique personalID!"<<std::endl;
        return false;
      }
    }
void personalUser::printUsers() const{
        std::cout << "Full name: " << getFullName() << "\n"
                  << "Personal ID: " << getPersonalID() << "\n"
                  << "Contact: " << getContact() << "\n"
                  << "Address: " << getAddress() << std::endl;
                  std::cout<<std::endl;
                  std::cout<<"1.Create Account"<<std::endl;
                  std::cout<<"2.Search for account"<<"        ";
                  std::cout<<"3.Log Out"<<std::endl;
    }
  void personalUser :: printAccounts(User *user) const {
    for(int i=0; i<user->getAccounts().size(); i++) {
      std::cout<<user->getAccounts()[i]->getAccountType()<<" "<<i+1<<".";
      std::cout<<user->getAccounts()[i]->getAccountNumber()<<std::endl;
    }
  }   
