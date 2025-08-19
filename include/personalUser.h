#ifndef PERSONALUSER_H
#define PERSONALUSER_H
#include "User.h"

class personalUser:public User {

   public:
   bool createUser(std::vector<User*> &users ) override ;
   virtual void printUsers() const override ;
   virtual void printAccounts(User *user) const override;
      

};

#endif