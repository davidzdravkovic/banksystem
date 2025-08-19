#include "../include/CheckingAccount.h"
#include "../include/functions.h"
#include "../include/Manager.h"
#include <iostream> 
#include <vector>

  class User;
   void CheckingAccount::deposit(double amount) {
    if (amount >= 0) balance += amount;
}
 void CheckingAccount ::withdraw(double amount) {
    if (amount > 0 && amount <= balance)
    balance -= amount;
 }
  bool CheckingAccount :: createAccount (std::vector<User*>&users, int personalID) {
     bool make=false;
     int temp = digitVal("Enter your account number: ");
     make=unique(users,personalID,temp);
     if(make) {
     accountNumber=temp;
     owner=inputVal("Enter the name of the owner: ");
     balance=digitVal("Enter your balance: ");
     accountTime=getCurrentTime();
     return true;
     }
     else{
        std::cout<<"Account number not unique!"<<std::endl;
        return false;
     }

   


 }
 void CheckingAccount :: printAccount()  {}

