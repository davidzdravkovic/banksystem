#include <iostream>
using namespace std;
//Display account function it allows the user insing about his bank account condition.
//The user needs to go enter account number, if that account exist.
//He is required for password. 
//After correct password he can manage only then he can see the account data.
    void displayAccount () {
         int number;
         int choice;
         while(true) {
         number=TWO("Enter your account number: ");
         number=FIVE(users,number);
          if(number==-1) {
            continue;
            }
            bool check=checkPass(" ",users, number,index);
            if(check) {
                cout<<"Name: "<<users[index].accounts[number].name<<endl;
                cout<<"Number: "<<users[index].accounts[number].number<<endl;
                cout<<"Password: "<<users[index].accounts[number].password<<endl;
                cout<<"Balance: "<<users[index].accounts[number].balance<<endl;
                
            }
            while(true) {
             choice=TWO("Enter 1 to check again 0 to exit: ");
             if(choice==1) {
                break;
             }
             else if(choice==0) {
             return;
             }
             else {
                cout<<"Just 1 or 0 is allowed! "<<endl;
             }
        }
    }
        