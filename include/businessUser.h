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
   void importLicenceFromFile(const std::string& filePath );  

};

#endif