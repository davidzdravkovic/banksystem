#ifndef BUSINESSUSER_H
#define BUSINESSUSER_H
#include <pqxx/pqxx>
#include "User.h"

class businessUser:public User {
    private:
    std :: string businessAddress;
    int businessContact;
    std :: string registrationNumber;

    public:
    int getBusiContact() const {return businessContact;}
    void setBusiContact(int cont) {businessContact=cont;}
     std :: string getBusiAddress() const {return businessAddress;}
    void setBusiAddress(std::string add) {businessAddress=add;}
    bool createUser(pqxx::connection &conn,std::shared_ptr<User> user) override ;
   void printUsers(pqxx::connection &conn) const override ;
   void methods(int option);
   void printAccount(Account& acc);
   void printAccounts(pqxx::connection &conn)const override;
   void importLicenceFromFile(const std::string& filePath );  

};

#endif