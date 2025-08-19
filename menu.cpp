#include "../include/menu.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include "../include/businessUser.h"
#include <iostream>


 void mainMenu() {
  Manager manager;
  businessUser bUser;

  int option;

  while(true) {
  manager.promt();
   option=digitVal("Enter your choice: ");

  switch (option)
  {
  case 1: {
  int personalID;
  int choice;

  manager.printProfiles();
  choice=digitVal("Enter your choice for user creation: ");
  User& userRef = manager.userCreate(choice);

  if(choice==2) {

    while(true) {
    userRef.print();
    int number=digitVal("Enter your option: ");
    if(number==1){
      manager.accountCreate(userRef.getPersonalID());
    }
    else if(number==2) {
     bUser.listAccounts(manager.getUsers(), userRef.getPersonalID());
    }
    else if(number==3) {
      break;
    }

    }

  }
}
    break;
  case 2: {
  manager.listUser();
  break;
  }
  case 3: {
  return;
  }
  default: {
    break;
  }
  
  
  }
 }
}