#include "../include/Transactions.h"
#include "../include/Account.h"
#include "../include/User.h"
#include "../include/Manager.h"
#include "../include/functions.h"
#include <iostream>


void Transactions :: creatTrans(User *user,int personalID,int accountNumber, int sum,Manager &manager) {
    
    for(int i=0; i<manager.getUsers().size(); i++) {
        if(manager.getUsers()[i]->getPersonalID()==personalID)
        for(int j=0; j<manager.getUsers()[i]->getAccounts().size(); j++) {
            if(manager.getUsers()[i]->getAccounts()[j]->getAccountNumber()==accountNumber) {
                 Transactions *transact=new Transactions();
                  transact->sender=user->getFullName();
                  transact->amount=sum;
                  manager.getUsers()[i]->getAccounts()[j]->trans.push_back(transact);
            }
        }

    }

}
void Transactions ::history(User *user) {
  
    for(int i=0; i<user->getAccounts().size(); i++) {
        for(int j=0; j<user->getAccounts()[i]->trans.size(); j++){
        Transactions* t =user->getAccounts()[i]->trans[j];
        std::cout << "Sender: " << t->sender << ", Amount: " << t->amount << std::endl;
        }
    }
   }


void Transactions ::decide(User *user) {
    
    for(int i=0; i<user->getAccounts().size(); i++) {
        for(int j=0; j<user->getAccounts()[i]->trans.size(); j++){
        Transactions* t=user->getAccounts()[i]->trans[j];
        double amount=t->amount;
        user->getAccounts()[j]->setBalanceDepo(amount);
        std::cout<<"New balance: "<<user->getAccounts()[j]->getBalance()<<std::endl;
        }
    }
   }
