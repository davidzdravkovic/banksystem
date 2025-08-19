#ifndef BUSINESSUSER_H
#define BUSINESSUSER_H
#include "User.h"

class businessUser:public User {
    private:
    std :: string businessAddress;
    int businessContact;
    int TAX;
    std :: string registrationNumber;

    public:
    bool createUser(std::vector<User*> &users) override ;
   virtual void printUsers() const override ;
   void methods(int option);
   void printAccount(Account& acc);
   void printAccounts(User *user)const override;
   void importLicenceFromFile(const std::string& filePath );  

};

#endif