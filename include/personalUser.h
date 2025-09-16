#ifndef PERSONALUSER_H
#define PERSONALUSER_H
#include "User.h"
class User;

class personalUser:public User {

   public:
   bool createUser(pqxx::connection &conn,std::shared_ptr<User> user) override ;
   virtual void printUsers(pqxx::connection &conn) const override ;
   virtual void printAccounts(pqxx::connection &conn) const override;
      

};

#endif