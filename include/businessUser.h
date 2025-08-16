#ifndef BUSINESSUSER_H
#define BUSINESSUSER_H
#include "../include/User.h"

class businessUser:public User {
    private:
    std :: string businessAddress;
    int businessContact;
    int TAX;
    std :: string registrationNumber;
    public:
    void createUser() override ;
   virtual void print() const override ;
   void methods(int option);
   void printAccount(Account& acc);
   void listAccounts(std::vector<User*> &users, int number);
   void importLicenceFromFile(const std::string& filePath );  

};

#endif