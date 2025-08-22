#include "../include/Transactions.h"
#include "../include/Manager.h"
#include <iostream>
#include "../include/functions.h"
#include "../include/Account.h"



Transactions* Transactions :: createTrans(Manager &manager,Account *acc, User *user)  {
    int personalID=digitVal("Enter user's personal ID: ");
    int  accountNumber=digitVal("Enter user's account number: ");
    int transNumber=digitVal("Enter transaction number: ");
    int transType=digitVal("For sending money enter 1 for asking 2: ");
    double sum=digitVal("Enter your amount: ");
    for(int i=0; i<manager.getUsers().size(); i++ ) {
        if(manager.getUsers()[i]->getPersonalID()==personalID) {                                              
            for(int j=0; j<manager.getUsers()[i]->getAccounts().size(); j++) {
                if(manager.getUsers()[i]->getAccounts()[j]->getAccountNumber()==accountNumber) {
                           Transactions *transact=new Transactions();
                            if(acc->getBalance()>=sum) {
                            transact->amount=sum;
                            }
                            else {
                                std::cout<<"Not enough sum!"<<std::endl;
                                return nullptr;
                            }
                            transact->accountNumber=acc->getAccountNumber();
                            transact->indetification=user->getPersonalID();
                            transact->transactionType=transType;
                            transact->transactionNumber=transNumber;
                            transact->sender=acc->getOwnerName();
                            transact->transStatus="Pending";
                            manager.getUsers()[i]->getAccounts()[j]->transInbox.push_back(transact);
                            Transactions *transact1=new Transactions();
                             transact1->receiver=manager.getUsers()[i]->getFullName();
                             transact1->indetification=manager.getUsers()[i]->getPersonalID();
                             transact1->accountNumber=manager.getUsers()[i]->getAccounts()[j]->getAccountNumber();
                             transact1->amount=sum;
                             if(transType==2) {
                                transact1->transactionType=1;
                             }
                             if(transType==1) {
                                transact1->transactionType=2;
                             }
                             std::cout<<transact1->transactionType<<std::endl;
                             transact1->transactionNumber=transact->transactionNumber;
                             transact1->transStatus="Pending";
                             acc->transSent.push_back(transact1);
                             return transact;
                       
                          
            
                    }
             

            }
                
    }
     
}
}

 
 void Transactions :: printSent(Account *acc) {

    if(acc->transSent.empty()) {
        std::cout<<"Transaction history is empty!"<<std::endl;
        return;
    }
    for(int i=0; i<acc->transSent.size(); i++) {
    if(acc->transSent[i]->receiver.empty()) {
   std::cout<<"No received transaction!"<<std::endl;
    return;
    }    
    std::cout<<i+1<<"."<<"Name: "<<acc->transSent[i]->receiver<<"."<<"Amount: "<<acc->transSent[i]->amount<<std::endl;
    }   
}

 void  Transactions :: printInbox(Account *acc) {
  if(acc->transInbox.empty()) {
        std::cout<<"Transaction history is empty!"<<std::endl;
        return;
    }
    for(int i=0; i<acc->transInbox.size(); i++) {
     std::cout<<i+1<<"."<<"Name: "<<acc->transInbox[i]->sender<<"."<<"Amount: "<<acc->transInbox[i]->amount<<std::endl;
    }   
   
 }
void Transactions :: decision(Manager &manager, Account *acc,Transactions* trans) {

    for(int i=0; i<manager.getUsers().size(); i++) {
        if(manager.getUsers()[i]->getPersonalID()==trans->indetification){
           for(int j=0; j<manager.getUsers()[i]->getAccounts().size(); j++)
           if(manager.getUsers()[i]->getAccounts()[j]->getAccountNumber()==trans->accountNumber) {                
            if(trans->transactionType==1) {
            manager.getUsers()[i]->getAccounts()[j]->setBalanceWith(trans->amount);
            acc->setBalanceDepo(trans->amount);
            delete trans;
            }
             if(trans->transactionType==2) {
                 manager.getUsers()[i]->getAccounts()[j]->setBalanceDepo(trans->amount);
                 acc->setBalanceWith(trans->amount);
 
            }
           }
        }
    }

   }

 