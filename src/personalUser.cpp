#include "../include/personalUser.h"
#include "../include/inputHandler.h"
#include <iostream>


void personalUser::createUser()
{
   
      fullName=inputVal("Enter your full name: ");
      personalID=digitVal("Enter your personal ID: " );
      contact=digitVal("Enter your contact number: ");
      address=digstrVal("Enter your address: ");
    }
void personalUser::print() const{
        std::cout << "Full name: " << fullName << "\n"
                  << "Personal ID: " << personalID << "\n"
                  << "Contact: " << contact << "\n"
                  << "Address: " << address << std::endl;
    }
   
