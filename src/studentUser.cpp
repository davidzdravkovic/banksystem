#include "../include/studentUser.h"
#include "../include/inputHandler.h"
#include <iostream>


void studentUser::createUser()
{
   
      fullName=inputVal("Enter your full name: ");
      personalID=digitVal("Enter your personal ID: " );
      contact=digitVal("Enter your contact number: ");
      address=digstrVal("Enter your address: ");
    }
void studentUser::print() const{
        std::cout << "Full name: " << fullName << "\n"
                  << "Personal ID: " << personalID << "\n"
                  << "Contact: " << contact << "\n"
                  << "Address: " << address << std::endl;
    }
   
