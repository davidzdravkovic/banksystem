#include "../include/menu.h"
#include "../include/inputHandler.h"
#include "../include/Manager.h"
#include <iostream>


 void mainMenu() {
  manager manager;
  int option;
  while(true) {
  std :: cout<<"1. Sign up"<< std :: endl;
  std :: cout<<"2. See the list of users!"<< std :: endl;
  option=digitVal("Enter your choice: ");
  switch (option)
  {
  case 1:
  int choice;
  std :: cout<< "Personal user profile"<< std :: endl;
  std :: cout<< "Business user profile"<< std :: endl;
  std :: cout<< "Student user profile"<< std :: endl;
  choice=digitVal("Enter your choice for user creation: ");
  manager.userCreate(choice);

    break;
  case 2: 
  manager.listUser();
  break;
  case 3: 
  
  break;
  default:
    break;
  }
  
  
  }
 }